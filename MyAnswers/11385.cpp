//
// Created by june0 on 2024-01-21.
//
#include <bits/stdc++.h>
#pragma GCC optimize("fast-math")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

namespace Utils
{
    namespace Math {
        constexpr long long safe_mod(long long x, long long m) {
            x %= m;
            if (x < 0) x += m;
            return x;
        }

        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return {b, 0};

            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t) {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u;

                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            if (m0 < 0) m0 += b / s;
            return {s, m0};
        }

        constexpr unsigned pow_mod_constexpr(long long a, long long n, unsigned MOD) {
            if (MOD == 1) return 0;
            a = safe_mod(a, MOD);
            unsigned long long res = 1;
            while (n) {
                if (n & 1) res = (res * a) % MOD;
                n >>= 1;
                a = (a * a) % MOD;
            }
            return res;
        }

        // NOTE : m must be prime
        constexpr unsigned primitive_root_constexpr(unsigned m) {
            // some popular roots
            if (m == 2) return 1;
            if (m == 167'772'161) return 3;
            if (m == 469'762'049) return 3;
            if (m == 754'974'721) return 11;
            if (m == 998'244'353) return 3;

            // find divisors of m - 1
            unsigned divs[20] = {};
            divs[0] = 2;
            unsigned cnt = 1;
            unsigned x = (m - 1) / 2;
            while (x % 2 == 0) x /= 2;
            for (int i = 3; (long long) (i) * i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            // find the first g s.t. there exist some d in divs, g^(m - 1)/d == 1 mod m
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
        }

        template<unsigned m> constexpr unsigned primitive_root = primitive_root_constexpr(m);
    } // namespace Math

    namespace TypeTraits {
        template<typename T>
        using is_signed_int =
                typename std::conditional_t<std::is_integral_v<T> && std::is_signed_v<T>,
                        std::true_type,
                        std::false_type>;

        template<typename T>
        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

        template<typename T>
        using is_unsigned_int =
                typename std::conditional_t<std::is_integral_v<T> && std::is_unsigned_v<T>,
                        std::true_type,
                        std::false_type>;

        template<typename T>
        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

        struct modint_base {};

        template<typename T>
        using is_modint = std::is_base_of<modint_base, T>;
        template<typename T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;
    } // namespace TypeTraits

    namespace Modulo {
        using namespace TypeTraits;
        using namespace Math;

        /**
         * an Integer type that modular arithmetic is automatically applied
         * @tparam MOD the modulus that will be applied to the value
         */
        template<int MOD,
                enable_if_t<(MOD >= 1)> * = nullptr>
        class ModInt : modint_base {
            using mint = ModInt;

        private:
            unsigned _v;

            static constexpr unsigned _umod() { return MOD; }

        public:
            static constexpr unsigned mod() { return MOD; }

            [[nodiscard]]
            unsigned value() const { return _v; }

            [[nodiscard]]
            mint pow(long long n) const {
                mint base = *this, res = 1;
                while (n > 0) {
                    if (n & 1) res *= base;
                    base *= base;
                    n >>= 1;
                }
                return res;
            }

            [[nodiscard]]
            mint inv() const {
                return pow(_umod() - 2);
            }

            ////////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////////

            ModInt() : _v(0) {}

            ModInt(const mint &other) : _v(other._v) {}

            template<typename T,
                    is_signed_int_t<T> * = nullptr>
            /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
                long long x = value % _umod();
                if (x < 0) x += _umod();
                _v = x;
            }

            template<typename T,
                    is_unsigned_int_t<T> * = nullptr>
            /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
                _v = value % _umod();
            }

            ////////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////////

            /* Assignment operators */
            mint &operator=(const mint &other) {
                _v = other._v;
                return *this;
            }

            mint &operator+=(const mint &rhs) {
                _v += rhs._v;
                if (_v >= _umod()) _v -= _umod();
                return *this;
            }

            mint &operator-=(const mint &rhs) {
                _v -= rhs._v;
                if (_v >= _umod()) _v += _umod();
                return *this;
            }

            mint &operator*=(const mint &rhs) {
                unsigned long long tmp = _v;
                tmp *= rhs._v;
                _v = tmp % _umod();
                return *this;
            }

            mint &operator/=(const mint &rhs) {
                return *this = *this * rhs.inv();
            }


            /* Binary operators */
            friend mint operator+(const mint &lhs, const mint &rhs) {
                return mint(lhs) += rhs;
            }

            friend mint operator-(const mint &lhs, const mint &rhs) {
                return mint(lhs) -= rhs;
            }

            friend mint operator*(const mint &lhs, const mint &rhs) {
                return mint(lhs) *= rhs;
            }

            friend mint operator/(const mint &lhs, const mint &rhs) {
                return mint(lhs) /= rhs;
            }


            /* Unary operators */
            mint operator+() { return *this; }

            mint operator-() { return mint() - *this; }

            /* Increment/Decrement operators */
            mint &operator++() {
                _v++;
                if (_v == _umod()) _v = 0;
                return *this;
            }

            mint &operator--() {
                if (_v == 0) _v = _umod();
                _v--;
                return *this;
            }

            mint operator++(int) {
                mint res = *this;
                ++*this;
                return res;
            }

            mint operator--(int) {
                mint res = *this;
                --*this;
                return res;
            }

            /* Conditional operators */
            bool operator==(const mint &other) { return _v == other._v; }

            bool operator==(const long long &other) { return _v == other; }

            bool operator!=(const mint &other) { return _v != other._v; }

            bool operator!=(const long long &other) { return _v != other; }

            bool operator>(const mint &other) { return _v > other._v; }

            bool operator>(const long long &other) { return _v > other; }

            bool operator<(const mint &other) { return _v < other._v; }

            bool operator<(const long long &other) { return _v < other; }

            bool operator>=(const mint &other) { return _v >= other._v; }

            bool operator>=(const long long &other) { return _v >= other; }

            bool operator<=(const mint &other) { return _v <= other._v; }

            bool operator<=(const long long &other) { return _v <= other; }

            /* I/O operator */
            friend std::ostream &operator<<(std::ostream &out, const mint &m) {
                out << m._v;
                return out;
            }

            friend std::istream &operator>>(std::istream &in, mint &m) {
                in >> m._v;
                m._v %= _umod();
                return in;
            }
        };
    } // namespace Modulo

    namespace NTT
    {
        using namespace Math;
        using namespace Modulo;

        template<typename mint, is_modint_t<mint> * = nullptr,
                unsigned ROOT = primitive_root<mint::mod()>,
                unsigned MOD = mint::mod()>
        void _ntt(std::vector<mint> &_v, bool _is_inv) {
            int n = (int) _v.size();
            // bit-reversal
            for (int i = 1, j = 0; i < n; i++) {
                int _bit = n >> 1;
                while (!((j ^= _bit) & _bit)) _bit >>= 1;
                if (i < j) std::swap(_v[i], _v[j]);
            }

            for (int i = 1; i < n; i <<= 1) {
                mint w = mint(ROOT).pow(MOD / i >> 1);
                if (_is_inv) w = w.inv();
                for (int j = 0; j < n; j += i << 1) {
                    mint z = 1;
                    for (int k = 0; k < i; k++) {
                        mint tmp = _v[i + j + k] * z;
                        _v[i + j + k] = _v[j + k] - tmp;
                        _v[j + k] += tmp;

                        z *= w;
                    }
                }
            }
            if (_is_inv) {
                mint n_inv = mint(n).inv();
                for (auto &z: _v) z *= n_inv;
            }
        }

        template<typename mint, is_modint_t<mint> * = nullptr>
        void _naive_convolution(std::vector<mint> &_a,
                                const std::vector<mint> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            std::vector<mint> res(n + m - 1);
            if (n < m) {
                for (int j = 0; j < m; j++) {
                    for (int i = 0; i < n; i++) {
                        res[i + j] += _a[i] * _b[j];
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        res[i + j] += _a[i] * _b[j];
                    }
                }
            }
            _a = res;
        }

        template<typename mint, is_modint_t<mint> * = nullptr>
        void _ntt_convolution(std::vector<mint> &_a,
                              std::vector<mint> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            int len = 1;
            while (len < (n + m)) len <<= 1;
            len <<= 1;

            _a.resize(len);
            _ntt(_a, false);
            _b.resize(len);
            _ntt(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _ntt(_a, true);
        }

        template<typename mint, is_modint_t<mint> * = nullptr>
        void _convolution(std::vector<mint> &_a,
                          std::vector<mint> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
            return _ntt_convolution(_a, _b);
        }

        template<unsigned MOD = 998'244'353,
                typename T,
                std::enable_if_t<std::is_integral_v<T>> * = nullptr>
        std::vector<T> convolution(const std::vector<T> &a,
                                   const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            using mint = ModInt<MOD>;

            std::vector<mint> _a(n), _b(m);
            for (int i = 0; i < n; i++)
                _a[i] = mint(a[i]);
            for (int i = 0; i < m; i++)
                _b[i] = mint(b[i]);
            _convolution(_a, _b);

            std::vector<T> res(n + m - 1);
            for (int i = 0; i < n + m - 1; i++)
                res[i] = _a[i].value();

            return res;
        }

        // TODO: search for Chinese Remainder Theorem(CRT)
        std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                              const std::vector<long long>& b) {
            int n = int(a.size()), m = int(b.size());
            if (!n || !m) return {};

            static constexpr unsigned long long MOD1 = 754974721;  // 2^24
            static constexpr unsigned long long MOD2 = 167772161;  // 2^25
            static constexpr unsigned long long MOD3 = 469762049;  // 2^26
            static constexpr unsigned long long M2M3 = MOD2 * MOD3;
            static constexpr unsigned long long M1M3 = MOD1 * MOD3;
            static constexpr unsigned long long M1M2 = MOD1 * MOD2;
            static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

            static constexpr unsigned long long i1 =
                    inv_gcd(MOD2 * MOD3, MOD1).second;
            static constexpr unsigned long long i2 =
                    inv_gcd(MOD1 * MOD3, MOD2).second;
            static constexpr unsigned long long i3 =
                    inv_gcd(MOD1 * MOD2, MOD3).second;

            static constexpr int MAX_AB_BIT = 24;
            static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1, "MOD1 isn't enough to support an array length of 2^24.");
            static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1, "MOD2 isn't enough to support an array length of 2^24.");
            static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1, "MOD3 isn't enough to support an array length of 2^24.");
            assert(n + m - 1 <= (1 << MAX_AB_BIT));

            auto c1 = convolution<MOD1>(a, b);
            auto c2 = convolution<MOD2>(a, b);
            auto c3 = convolution<MOD3>(a, b);

            std::vector<long long> c(n + m - 1);
            for (int i = 0; i < n + m - 1; i++) {
                unsigned long long x = 0;
                x += (c1[i] * i1) % MOD1 * M2M3;
                x += (c2[i] * i2) % MOD2 * M1M3;
                x += (c3[i] * i3) % MOD3 * M1M2;
                // B = 2^63, -B <= x, r(real value) < B
                // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
                // r = c1[i] (mod MOD1)
                // focus on MOD1
                // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
                // r = x,
                //     x - M' + (0 or 2B),
                //     x - 2M' + (0, 2B or 4B),
                //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
                // (r - x) = 0, (0)
                //           - M' + (0 or 2B), (1)
                //           -2M' + (0 or 2B or 4B), (2)
                //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
                // we checked that
                //   ((1) mod MOD1) mod 5 = 2
                //   ((2) mod MOD1) mod 5 = 3
                //   ((3) mod MOD1) mod 5 = 4
                long long diff =
                        c1[i] - safe_mod((long long)(x), (long long)(MOD1));
                if (diff < 0) diff += MOD1;
                static constexpr unsigned long long offset[5] = {
                        0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
                x -= offset[diff % 5];
                c[i] = x;
            }

            return c;
        }
    } // namespace NTT using ModInt

} // namespace Utils

using namespace Utils::NTT;
using namespace Utils::Math;

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<ll> a(n + 1), b(m + 1);
    for (auto& e : a) cin >> e;
    for (auto& e : b) cin >> e;
    auto conv = convolution_ll(a, b);

    ll ans = 0;
    for (const auto& e : conv) ans ^= e;

    cout << ans;

    return 0;
}

#ifdef ANOTHER_SOLUTION
// This solution uses FFT not NTT, but for precision,
// it slices the given integers with 10 bits.

namespace Utils
{
    namespace FFT {
        using base = std::complex<long double>;
        const long double PI = M_PI;

        void _fft(std::vector<base> &_v, bool _is_inv) {
            int n = (int) _v.size();
            for (int i = 1, j = 0; i < n; i++) {
                int _bit = n >> 1;
                // while (j >= _bit){
                //     j -= _bit;
                //     _bit /= 2;
                // }
                while (!((j ^= _bit) & _bit)) _bit >>= 1;
                if (i < j) std::swap(_v[i], _v[j]);
            }
            for (int i = 1; i < n; i <<= 1) {
                long double x = _is_inv ? PI / i : -PI / i;
                base w = {cos(x), sin(x)};
                for (int j = 0; j < n; j += i << 1) {
                    base z = {1, 0};
                    for (int k = 0; k < i; k++) {
                        // base even = _v[j + k];
                        // base odd  = _v[i + j + k];
                        // _v[j + k] = even + z * odd;
                        // _v[i + j + k] = even - z * odd;

                        base tmp = _v[i + j + k] * z;
                        _v[i + j + k] = _v[j + k] - tmp;
                        _v[j + k] += tmp;

                        z *= w;
                    }
                }
            }
            if (_is_inv) {
                for (auto &z: _v) z /= n;
            }
        }
        void _naive_convolution(std::vector<base> &_a,
                                const std::vector<base> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            std::vector<base> res(n + m - 1);
            if (n < m) {
                for (int j = 0; j < m; j++) {
                    for (int i = 0; i < n; i++) {
                        res[i + j] += _a[i] * _b[j];
                    }
                }
            } else {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        res[i + j] += _a[i] * _b[j];
                    }
                }
            }
            _a = res;
        }

        void _fft_convolution(std::vector<base> &_a,
                              std::vector<base> &_b) {
            int n = (int) _a.size(), m = (int) _b.size();
            int len = 2;
            while (len < n + m) len <<= 1;

            _a.resize(len);
            _fft(_a, false);
            _b.resize(len);
            _fft(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fft(_a, true);
            _a.resize(n + m - 1);
        }

        void _convolution(std::vector<base> &_a,
                          std::vector<base> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) {
                _naive_convolution(_a, _b);
                return;
            }
            _fft_convolution(_a, _b);
        }

        template<typename T,
                std::enable_if_t<std::is_integral_v<T>> * = nullptr>
        std::vector<T> convolution(const std::vector<T> &a,
                                   const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            std::vector<base> _a(a.begin(), a.end()), _b(b.begin(), b.end());
            _convolution((_a), (_b)); // using std::move is slower somehow

            std::vector<T> res(n + m - 1);
            if (is_floating_point_v<T>) {
                for (int i = 0; i < n + m - 1; i++)
                    res[i] = _a[i].real();
            } else {
                for (int i = 0; i < n + m - 1; i++)
                    res[i] = std::round(_a[i].real());
            }

            return res;
        }
    } // namespace FFT

    namespace Math {

    } // namespace Math
} // namespace Utils

using namespace Utils::FFT;
using namespace Utils::Math;
using cpx = complex<double>;

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<ull> a(n + 1), b(m + 1);
    for (auto& e : a) cin >> e;
    for (auto& e : b) cin >> e;

    auto aa = a, bb = b;
    for (auto& e : aa) e &= ((1 << 10) - 1);
    for (auto& e : bb) e &= ((1 << 10) - 1);
    auto res22 = convolution(aa, bb);

    aa = a, bb = b;
    for (auto& e : aa) e >>= 10;
    for (auto& e : bb) e &= ((1 << 10) - 1);
    auto res12 = convolution(aa, bb);

    aa = a, bb = b;
    for (auto& e : aa) e &= ((1 << 10) - 1);
    for (auto& e : bb) e >>= 10;
    auto res21 = convolution(aa, bb);

    aa = a, bb = b;
    for (auto& e : aa) e >>= 10;
    for (auto& e : bb) e >>= 10;
    auto res11 = convolution(aa, bb);

    ll ans = 0;
    for (int i = 0; i < n + m + 1; i++)
        ans ^= (res11[i] << 20) + ((res12[i] + res21[i]) << 10) + res22[i];

    cout << ans;


    return 0;
}

#endif
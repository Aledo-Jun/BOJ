//
// Created by june0 on 2024-01-23.
// Similar to #17104
//
#include <bits/stdc++.h>
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

        // Structure for fast modular multiplication
        struct Barrett {
            unsigned MOD;
            unsigned long long inv_MOD;

            explicit Barrett(unsigned m) : MOD(m), inv_MOD((unsigned long long) (-1) / MOD + 1) {}

            [[nodiscard]]
            unsigned mod() const { return MOD; }

            [[nodiscard]]
            unsigned multiply(unsigned a, unsigned b) const {
                unsigned long long res1 = a;
                res1 *= b;
                unsigned long long res2 = ((unsigned __int128) (res1) * inv_MOD) >> 64;
                res2 *= MOD;
                return (res1 - res2 + (res1 < res2 ? MOD : 0));
            }
        };

        std::vector<int> prime_sieve(int n) {
            std::vector<bool> is_prime = std::vector<bool>(n + 1, true);
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i * i <= n; i++) {
                if (is_prime[i]) {
                    for (int j = i * i; j <= n; j += i) {
                        is_prime[j] = false;
                    }
                }
            }
            std::vector<int> sieve;
            for (int i = 3; i <= n; i++) {
                if (is_prime[i])
                    sieve.push_back(i);
            }
            return sieve;
        }
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
            virtual mint inv() const {
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

    namespace FFT {
        using base = std::complex<double>;
        const double PI = M_PI;

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
                base::value_type x = _is_inv ? PI / i : -PI / i;
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

        void fft(std::vector<base> &_v) {
            _fft(_v, false);
        }

        template<typename T,
                std::enable_if_t<std::is_integral_v<T>> * = nullptr>
        vector<base> fft(std::vector<T> &v) {
            std::vector<base> _v(v.begin(), v.end());
            _fft(_v, false);
            return _v;
        }

        void inv_fft(std::vector<base> &_v) {
            _fft(_v, true);
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
            int n = (int) _a.size();
            int m = (int) _b.size();
            int len = 1;
            while (len < n + m) len <<= 1;

            _a.resize(len);
            _fft(_a, false);
            _b.resize(len);
            _fft(_b, false);

            for (int i = 0; i < len; i++)
                _a[i] *= _b[i];

            _fft(_a, true);
        }

        void _fft_exp(std::vector<base> &_a, int m) {
            int n = (int) _a.size();
            int len = 2;
            while (len < n * 2) len <<= 1;

            _a.resize(len);
            _fft(_a, false);

            for (int i = 0; i < len; i++)
                _a[i] = pow(_a[i], m);

            _fft(_a, true);
        }

        void _convolution(std::vector<base> &&_a,
                          std::vector<base> &&_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
            return _fft_convolution(_a, _b);
        }

        void convolution(std::vector<base> &_a,
                         std::vector<base> &_b) {
            int n = (int) _a.size();
            int m = (int) _b.size();
            if (n == 0 || m == 0) return;
            if (std::min(n, m) <= 60) return _naive_convolution(_a, _b);
            return _fft_convolution(_a, _b);
        }

        template<typename T,
                std::enable_if_t<std::is_integral_v<T>> * = nullptr>
        std::vector<T> convolution(const std::vector<T> &a,
                                   const std::vector<T> &b) {
            int n = (int) a.size();
            int m = (int) b.size();
            if (n == 0 || m == 0) return {};

            std::vector<base> _a(a.begin(), a.end()), _b(b.begin(), b.end());
            _convolution(std::move(_a), std::move(_b));

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

} // namespace Utils

using namespace Utils::FFT;
using namespace Utils::Math;
using namespace Utils::Modulo;

using cpx = complex<double>;

const int MAX_N = 1'000'000;

void mul(vector<cpx> &p, vector<cpx> &p2){
    p.resize(1 << 21);
    _fft(p, false);
    p2.resize(1 << 21);
    _fft(p2,false);

    for (int i = 0; i < (1 << 21); i++){
        p2[i] *= p[i];
        p[i] *= p[i] * p[i];
    }

    _fft(p, true);
    _fft(p2,true);
}


int32_t main() {
    fastIO;
    int t;
    cin >> t;
    auto primes = prime_sieve(MAX_N); // except 2
    vector<cpx> p(MAX_N + 1, 0), p2(MAX_N * 2, 0);
    vector<bool> is_prime(MAX_N + 1, false);
    for (const auto &e : primes){
        p[(e - 1) / 2] += 1;
        p2[e - 1] += 1;
        is_prime[e] = true;
    }

    mul(p, p2);

    while (t--) {
        int n;
        cin >> n;

        ll ans = round(p[(n - 3) / 2].real());
        ll tmp = round(p2[(n - 3) / 2].real());
        if (n % 3 == 0 && is_prime[n / 3]){
            cout << (ans - 3 * tmp + 2) / 6 + tmp + (is_prime[n - 4] ? 1 : 0) << endl;
        } else {
            cout << (ans - 3 * tmp) / 6 + tmp + (is_prime[n - 4] ? 1 : 0) << endl;
        }
    }


    return 0;
}
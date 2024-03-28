//
// Created by june0 on 2024-03-28.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the _root_ of all evil."
 *  <sub> Donald Knuth </sub>
 */

#ifdef NONLINE_JUDGE
/**
 * Namespace for Fast I/O
 *
 * @class@b INPUT
 * class which can replace the cin
 *
 * @class@b OUTPUT
 * class which can replace the cout
 *
 * @Description
 * These classes use low-level i/o functions (@c fread() for input, @c fwrite() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char readBuffer[SZ];
        int read_idx, next_idx;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            if (read_idx == next_idx) {
                next_idx = (int)fread(readBuffer, sizeof(char), SZ, stdin);
                if (next_idx == 0) return 0;
                read_idx = 0;
            }
            return readBuffer[read_idx++];
        }

        char ReadChar() {
            char ret = _ReadChar();
            for (; IsBlank(ret); ret = _ReadChar());

            return ret;
        }

        template<class T>
        T ReadInt() {
            T ret = 0;
            char curr = _ReadChar();
            bool minus_flag = false;

            for (; IsBlank(curr); curr = _ReadChar());
            if (curr == '-') minus_flag = true, curr = _ReadChar();
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret = 10 * ret + (curr & 15);
            if (IsEnd(curr)) __END_FLAG__ = true;

            return minus_flag ? -ret : ret;
        }

        std::string ReadString() {
            std::string ret;
            char curr = _ReadChar();
            for (; IsBlank(curr); curr = _ReadChar());
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (IsEnd(curr)) __END_FLAG__ = true;

            return ret;
        }

        double ReadDouble() {
            std::string ret = ReadString();
            return std::stod(ret);
        }

        std::string getline() {
            std::string ret;
            char curr = _ReadChar();
            for (; curr != '\n' && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (__GET_LINE_FLAG__) __END_FLAG__ = true;
            if (IsEnd(curr)) __GET_LINE_FLAG__ = true;

            return ret;
        }

        friend INPUT &getline(INPUT &in, std::string &s) {
            s = in.getline();
            return in;
        }
    } _in;
    /* End of Class INPUT */

    /* Class OUTPUT */
    class OUTPUT {
    private:
        char writeBuffer[SZ];
        int write_idx;
    public:
        ~OUTPUT() { Flush(); }

        explicit operator bool() const { return true; }

        void Flush() {
            fwrite(writeBuffer, sizeof(char), write_idx, stdout);
            write_idx = 0;
        }

        void WriteChar(char c) {
            if (write_idx == SZ) Flush();
            writeBuffer[write_idx++] = c;
        }

        template<class T>
        void WriteInt(T n) {
            int sz = GetSize(n);
            if (write_idx + sz >= SZ) Flush();
            if (n < 0) writeBuffer[write_idx++] = '-', n = -n;
            for (int i = sz; i-- > 0; n /= 10)
                writeBuffer[write_idx + i] = n % 10 | 48;
            write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        void WriteDouble(double d) {
            WriteString(std::to_string(d));
        }

        template<class T>
        int GetSize(T n) {
            int ret = 1;
            for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;

            return ret;
        }
    } _out;
    /* End of Class OUTPUT */

    /* Operators */
    INPUT &operator>>(INPUT &in, char &i) {
        i = in.ReadChar();
        return in;
    }

    INPUT &operator>>(INPUT &in, std::string &i) {
        i = in.ReadString();
        return in;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    INPUT &operator>>(INPUT &in, T &i) {
        if constexpr (std::is_floating_point_v<T>) i = in.ReadDouble();
        else if constexpr (std::is_integral_v<T>) i = in.ReadInt<T>();
        return in;
    }

    OUTPUT &operator<<(OUTPUT &out, char i) {
        out.WriteChar(i);
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, const std::string &i) {
        out.WriteString(i);
        return out;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    OUTPUT &operator<<(OUTPUT &out, T i) {
        if constexpr (std::is_floating_point_v<T>) out.WriteDouble(i);
        else if constexpr (std::is_integral_v<T>) out.WriteInt(i);
        return out;
    }

    /* Macros for convenience */
    #undef fastIO
    #define fastIO 1
    #define cin _in
    #define cout _out
    #define istream INPUT
    #define ostream OUTPUT
};
using namespace FastIO;
#endif

// ref) https://restudycafe.tistory.com/563
//      https://tistory.joonhyung.xyz/6
//      https://www.acmicpc.net/source/share/da09a901e36d4f1b820d88128e09c1db
//

namespace Utils
{
    namespace Math {
        constexpr long long safe_mod(long long x, long long m) {
            x = (long long)(x % m);
            if (x < 0) x = (long long)(x + m);
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
            unsigned long long _a = safe_mod(a, MOD);
            unsigned long long res = 1;
            while (n) {
                if (n & 1) res = (res * _a) % MOD;
                n >>= 1;
                _a = (_a * _a) % MOD;
            }
            return res;
        }

        // NOTE : m must be prime
        constexpr unsigned primitive_root_constexpr(unsigned m) {
            // some popular roots
            if (m == 2) return 1;
            if (m == 786'433) return 10;
            if (m == 167'772'161) return 3;
            if (m == 469'762'049) return 3;
            if (m == 754'974'721) return 11;
            if (m == 998'244'353) return 3;
            if (m == 104'857'601) return 3;

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
            for (int i = 2; i <= n; i++) {
                if (is_prime[i])
                    sieve.push_back(i);
            }
            return sieve;
        }
    } // namespace Math
    namespace Modulo {
        struct modint_base { };

        template<typename T>
        using is_modint = std::is_base_of<modint_base, T>;
        template<typename T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;

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

            static constexpr int _umod() { return MOD; }

        public:
            static constexpr int mod() { return MOD; }

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
                int x = -MOD <= value && value < MOD ? value : value % MOD;
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
                unsigned __int128 tmp = _v;
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

            bool operator==(const unsigned long long &other) { return _v == other; }

            bool operator!=(const mint &other) { return _v != other._v; }

            bool operator!=(const unsigned long long &other) { return _v != other; }

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

        /**
         * a ModInt that modulus can be modified dynamically
         * @tparam id when multiple modulus' are used, each ModInt can be identified with the id.
         */
        template<int id>
        class DynamicModInt : modint_base {
            using mint = DynamicModInt;

        private :
            unsigned _v;

            static Utils::Math::Barrett bt;

            static unsigned _umod() { return bt.mod(); }

        public:
            static unsigned mod() { return bt.mod(); }

            static void set_mod(int m) {
                assert(1 <= m);
                bt = Utils::Math::Barrett(m);
            }

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
                auto eg = Utils::Math::inv_gcd(_v, _umod());
                assert(eg.first == 1);
                return eg.second;
            }

            ////////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////////

            DynamicModInt() : _v(0) {}

            DynamicModInt(const mint &other) : _v(other._v) {}

            template<typename T,
                    is_signed_int_t<T> * = nullptr>
            /* implicit */ DynamicModInt(T value) { // NOLINT(google-explicit-constructor)
                long long x = value % _umod();
                if (x < 0) x += _umod();
                _v = x;
            }

            template<typename T,
                    is_unsigned_int_t<T> * = nullptr>
            /* implicit */ DynamicModInt(T value) { // NOLINT(google-explicit-constructor)
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

            mint& operator*=(const mint& rhs) {
                _v = bt.multiply(_v, rhs._v);
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

            mint operator-() { return _umod() - *this; }

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

        }; // class DynamicModInt
        template<int id> Utils::Math::Barrett DynamicModInt<id>::bt(998244353);

        int pow_mod(int a, int pow, int MOD) {
            int base = a;
            int res = 1;
            while (pow > 0) {
                if (pow & 1) {
                    res = (int) (1ULL * res * base) % MOD;
                }
                base = (int) (1ULL * base * base) % MOD;
                pow >>= 1;
            }
            return res;
        }

        int factorial_mod(int n, int MOD) {
            int res = 1;
            for (int i = 1; i <= n; i++) {
                res = (int) (1ULL * res * i) % MOD;
            }
            return res;
        }

        int _binomial_coefficient(int n, int k, int MOD) {
            // Calculate n! / (k! * (n-k)!)
            int numerator = factorial_mod(n, MOD);
            int denominator = (int) (1ULL * factorial_mod(k, MOD) * factorial_mod(n - k, MOD)) % MOD;

            int denominator_inverse = pow_mod(denominator, MOD - 2, MOD);

            int result = (int) (1ULL * numerator * denominator_inverse) % MOD;
            return result;
        }

        // Calculate the binomial coefficient using Lucas' theorem
        int binomial_coefficient(int n, int k, int MOD) {
            int result = 1;
            while (n > 0 && k > 0) {
                int n_remain = n % MOD;
                int k_remain = k % MOD;
                n /= MOD;
                k /= MOD;
                if (n_remain < k_remain) {
                    result = 0;
                    break;
                }
                result = (result * _binomial_coefficient(n_remain, k_remain, MOD)) % MOD;
            }
            return result;
        }
    } // namespace Modulo
    namespace NTT
    {
        using namespace Math;
        using namespace Modulo;

        template<typename mint, is_modint_t<mint> * = nullptr,
                unsigned ROOT = primitive_root<mint::mod()>,
                unsigned MOD = mint::mod()>
        class NTT {
        private:
            vector<mint> roots;

            void _precompute_roots(int n) {
                if (roots.empty()) roots = {1, 1};
                for (int k = (int)roots.size(); k < n; k <<= 1) {
                    roots.resize(n, 1);
                    mint w = mint(ROOT).pow((MOD - 1) / (k << 1));
                    for (int i = k; i < k << 1; i++) {
                        roots[i] = i & 1 ? roots[i >> 1] * w : roots[i >> 1];
                    }
                }
            }

            void _ntt(std::vector<mint> &_v, bool _is_inv) {
                int n = (int) _v.size();
                // bit-reversal
                for (int i = 1, j = 0; i < n; i++) {
                    int _bit = n >> 1;
                    while (!((j ^= _bit) & _bit)) _bit >>= 1;
                    if (i < j) std::swap(_v[i], _v[j]);
                }

                _precompute_roots(n);
                for (int i = 1; i < n; i <<= 1) {
                    for (int j = 0; j < n; j += i << 1) {
                        for (int k = 0; k < i; k++) {
                            mint tmp = _v[i + j + k] * roots[i + k];
                            _v[i + j + k] = _v[j + k] - tmp;
                            _v[j + k] += tmp;
                        }
                    }
                }
                if (_is_inv) {
                    std::reverse(_v.begin() + 1, _v.end());
                    mint n_inv = mint(n).inv();
                    for (auto &z: _v) z *= n_inv;
                }
            }

        public:
            void ntt(std::vector<mint> &v) {
                _ntt(v, false);
            }

            template<typename T,
                    std::enable_if_t<std::is_integral_v<T>> * = nullptr>
            auto ntt(std::vector<T> &v) {
                vector<mint> _v(v.begin(), v.end());
                _ntt(_v, false);
                return _v;
            }

            void inv_ntt(std::vector<mint> &v) {
                _ntt(v, true);
            }

            template<typename T,
                    std::enable_if_t<std::is_integral_v<T>> * = nullptr>
            auto inv_ntt(std::vector<T> &v) {
                vector<mint> _v(v.begin(), v.end());
                _ntt(_v, true);
                return _v;
            }

        private:
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

            void _ntt_convolution(std::vector<mint> &_a,
                                  std::vector<mint> &_b) {
                int n = (int) _a.size();
                int m = (int) _b.size();
                int len = 1;
                while (len < (n + m)) len <<= 1;

                _a.resize(len);
                _ntt(_a, false);
                _b.resize(len);
                _ntt(_b, false);

                for (int i = 0; i < len; i++)
                    _a[i] *= _b[i];

                _ntt(_a, true);
            }

            void _convolution(std::vector<mint> &&_a,
                              std::vector<mint> &&_b) {
                int n = (int) _a.size();
                int m = (int) _b.size();
                if (n == 0 || m == 0) return;
                if (std::min(n, m) <= 50) return _naive_convolution(_a, _b);
                return _ntt_convolution(_a, _b);
            }

            void _convolution(std::vector<mint> &_a,
                              std::vector<mint> &_b) {
                int n = (int) _a.size();
                int m = (int) _b.size();
                if (n == 0 || m == 0) return;
                if (std::min(n, m) <= 50) return _naive_convolution(_a, _b);
                return _ntt_convolution(_a, _b);
            }

        public:
            template<typename T,
                    std::enable_if_t<std::is_integral_v<T>> * = nullptr>
            std::vector<T> convolution(const std::vector<T> &a,
                                       const std::vector<T> &b) {
                int n = (int) a.size();
                int m = (int) b.size();
                if (n == 0 || m == 0) return {};

                std::vector<mint> _a(a.begin(), a.end()), _b(b.begin(), b.end());
                _convolution(std::move(_a), std::move(_b));

                std::vector<T> res(n + m - 1);
                for (int i = 0; i < n + m - 1; i++)
                    res[i] = _a[i].value(); // NOLINT: variable used after it was moved(intended)

                return res;
            }

            /**
        * @brief Bostan-Mori Algorithm that finds n-th element of the sequence which is defined recursively as follow:
        * <p>
        *      {a_0, a_1, ..., a_k-1} = {a[0], a[1], ... , a[k-1]}, <br>
        *      {c_1, c_2, ..., c_k} = {c[0], c[1], ... , c[k-1]}, <br>
        *      a_i = c_1 * a_i-1 + c_2 * a_i-2 + ... + c_k * a_i-k
        * </p>
        * @tparam mint ModInt type
        * @param a Same as def
        * @param c Same as def
        * @param n Index of element you want to find
        * @return Value of n-th element of the sequence
        */
            template<typename T>
            T Bostan_Mori(const std::vector<T>& a, const std::vector<T>& c, ll n, ll mod){
                int k = (int) a.size();

                std::vector<T> C(k + 1, 1);
                for (int i = 1; i <= k; i++) C[i] = mod - c[i - 1];

                auto P = this->convolution(a, C);
                P.resize(k);
                for (auto& e : P) e %= mod;

                for (; n; n >>= 1) {
                    auto Q = C;
                    for (int i = 1; i <= k; i += 2) Q[i] = mod - C[i];
                    auto U = this->convolution(P, Q);
                    auto V = this->convolution(C, Q);
                    for (int i = 0; i < k; i++) P[i] = U[i * 2 + (n & 1)] % mod;
                    for (int i = 0; i <= k; i++) C[i] = V[i * 2] % mod;
                }
                return (P[0] % mod) * Utils::Math::pow_mod_constexpr(C[0] % mod, mod - 2, mod);
            }
        }; // class NTT

    } // namespace NTT using ModInt
} // namespace Utils

constexpr int MOD = 998'244'353;
using mint = Utils::Modulo::ModInt<MOD>;

int32_t main() {
    fastIO;
    ll k, m, mod;
    cin >> k >> m >> mod;

    vector<int> a{0, 1}, c(k, 1);
    for (int i = 2; i < k; i++) a.emplace_back((ll)a.back() * 2 % mod);

    Utils::NTT::NTT<mint> ntt;

    cout << ntt.Bostan_Mori(a, c, m + 1, mod);

    return 0;
}
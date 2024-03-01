//
// Created by june0 on 2024-03-01.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

//
/// "Premature optimization is the root of all evil." -- Donald Knuth
//
namespace Math {
    constexpr long long safe_mod(long long x, unsigned long long m) {
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

    constexpr unsigned pow_mod_constexpr(long long a, unsigned long long n, unsigned long long MOD) {
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
    constexpr unsigned primitive_root_constexpr(unsigned long long m) {
        // some popular roots
        if (m == 2) return 1;
        if (m == 786'433) return 10;
        if (m == 167'772'161) return 3;
        if (m == 469'762'049) return 3;
        if (m == 754'974'721) return 11;
        if (m == 998'244'353) return 3;
        if (m == 9'223'372'036'972'216'319ull) return 3;

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

    template<unsigned long long m> constexpr unsigned primitive_root = primitive_root_constexpr(m);

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

    template<typename T, typename = void>
    struct supports_arithmetic : public std::false_type { };

    template<typename T>
    struct supports_arithmetic<T,
            void_t<decltype(std::declval<T>() + std::declval<T>()),
                    decltype(std::declval<T>() - std::declval<T>()),
                    decltype(std::declval<T>() * std::declval<T>()),
                    decltype(std::declval<T>() / std::declval<T>())>>
            : public std::true_type { };

    template<typename T>
    using supports_arithmetic_v = typename supports_arithmetic<T>::value;

    struct modint_base { };

    template<typename T>
    using is_modint = std::is_base_of<modint_base, T>;
    template<typename T>
    using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    struct matrix_base { };

    template<typename T>
    using is_matrix = std::is_base_of<matrix_base, T>;

    template<typename T>
    using is_matrix_t = std::enable_if_t<is_matrix<T>::value>;

} // namespace TypeTraits

namespace Modulo {
    using namespace TypeTraits;
    using namespace Math;

    /**
     * an Integer type that modular arithmetic is automatically applied
     * @tparam MOD the modulus that will be applied to the value
     */
    template<unsigned long long MOD,
            enable_if_t<(MOD >= 1)> * = nullptr>
    class ModInt : modint_base {
        using mint = ModInt;

    private:
        unsigned long long _v;

        static constexpr unsigned long long _umod() { return MOD; }

    public:
        static constexpr unsigned long long mod() { return MOD; }

        [[nodiscard]]
        unsigned long long value() const { return _v; }

        [[nodiscard]]
        mint pow(unsigned long long n) const {
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
            __int128 x = value % _umod();
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
            unsigned __int128 tmp = _v;
            tmp += rhs._v;
            _v = tmp % _umod();
            return *this;
        }

        mint &operator-=(const mint &rhs) {
            __int128 tmp = _v;
            tmp -= rhs._v;
            if (tmp < 0) tmp += _umod();
            _v = tmp % _umod();
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

} // namespace Modulo

using mint = Modulo::ModInt<10'007>;

int32_t main() {
    fastIO;
    string s;
    cin >> s;
    int n = (int) s.size();

    matrix<mint> dp(n, vector<mint>(n));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int r = 1; r < n; r++){
        for (int i = 0; i < n - r; i++){
            int j = i + r;
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            if (s[i] == s[j]) dp[i][j] += 1 + dp[i + 1][j - 1];
        }
    }
    cout << dp[0][n - 1];

    return 0;
}
//
// Created by june0 on 2024-03-04.
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

using mint = Modulo::ModInt<1'000'000'007>;
int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v) cin >> e;
    sort(v.begin(), v.end());

    vector<mint> power_of_2(n, 1);
    for (int i = 1; i < n; i++) power_of_2[i] = power_of_2[i - 1] * 2;

    mint ans = 0;
    for (int i = 0; i < n; i++){
        ans += power_of_2[i] * v[i];
        ans -= power_of_2[n - i - 1] * v[i];
    }
    cout << ans;

    return 0;
}
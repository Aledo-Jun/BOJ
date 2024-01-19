//
// Created by june0 on 2024-01-16.
//

#ifndef BOJ_MODULO_HPP
#define BOJ_MODULO_HPP

#include "Math.hpp"
#include "TypeTraits.hpp"
#include <cassert>
#include <iostream>

namespace Utils
{
namespace TypeTraits {
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

        mint pow(long long n) const {
            mint base = *this, res = 1;
            while (n > 0) {
                if (n & 1) res *= base;
                base *= base;
                n >>= 1;
            }
            return res;
        }

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
            _v += _umod() - rhs._v;
            if (_v >= _umod()) _v -= _umod();
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
    };

    using mint = ModInt<998'244'353>;
} // namespace Modulo

namespace Math
{
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

} // namespace Utils

#endif //BOJ_MODULO_HPP
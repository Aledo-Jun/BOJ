//
// Created by june0 on 2024-01-16.
//

#ifndef BOJ_MODULO_HPP
#define BOJ_MODULO_HPP

#include "Math.hpp"
#include <cassert>

namespace Modulo {

    struct modint_base {}; // for type checking

    template<typename T>
    using is_modint = std::is_base_of<modint_base, T>;
    template<typename T>
    using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    /**
     * an Integer type that modular arithmetic is automatically applied
     * @tparam MOD the modulus that will be applied to the value
     */
    template<int MOD,
            enable_if_t<(MOD >= 1)> * = nullptr>
    class ModInt : arithmetic_interface<ModInt<MOD>>, modint_base {
        using mint = ModInt;

    private:
        unsigned _v;

        static constexpr unsigned _umod() { return MOD; }

    public:
        static constexpr unsigned mod() { return MOD; }

        [[nodiscard]]
        unsigned value() const { return _v; }

        mint pow(long long n) const {
            assert(n < 0);
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

        template<typename T,
                is_signed_int_t<T> * = nullptr>
        explicit ModInt(T value) {
            long long x = value % _umod();
            if (x < 0) x += _umod();
            _v = x;
        }

        template<typename T,
                is_unsigned_int_t<T> * = nullptr>
        explicit ModInt(T value) {
            _v = value % _umod();
        }

        ////////////////////////////////////////////////////////////////
        // Operators
        ////////////////////////////////////////////////////////////////

        /* Assignment operators */
        mint &operator=(const mint &other) { _v = other._v; }
        mint &operator=(mint &&other) noexcept { this = other; } // move constructor
        mint &operator=(const long long &other) { _v = other; }
        mint &operator=(long long &&other) { _v = other; }

        mint &operator+=(const mint &rhs) {
            _v += rhs._v;
            if (_v >= _umod()) _v -= _umod();
            return *this;
        }
        mint &operator+=(const long long &rhs) {
            _v += rhs;
            if (_v >= _umod()) _v -= _umod();
            return *this;
        }

        mint &operator-=(const mint &rhs) {
            _v += _umod() - rhs._v;
            if (_v >= _umod()) _v -= _umod();
            return *this;
        }
        mint &operator-=(const long long &rhs) {
            _v += _umod() - rhs;
            if (_v >= _umod()) _v -= _umod();
            return *this;
        }

        mint &operator*=(const mint &rhs) {
            unsigned long long tmp = _v;
            tmp *= rhs._v;
            _v = tmp % _umod();
            return *this;
        }
        mint &operator*=(const long long &rhs) {
            unsigned long long tmp = _v;
            tmp *= rhs;
            _v = tmp % _umod();
            return *this;
        }

        mint &operator/=(const mint &rhs) {
            return *this = *this * rhs.inv();
        }
        mint &operator/=(const long long &rhs) {
            return *this = *this * mint(rhs).inv();
        }

        /* Binary operators */
        mint operator+(const mint &rhs) {
            return *this += rhs;
        }
        mint operator+(const long long &rhs) {
            return *this += rhs;
        }

        mint operator-(const mint &rhs) {
            return *this - rhs;
        }
        mint operator-(const long long &rhs) {
            return *this - rhs;
        }

        mint operator*(const mint &rhs) {
            return *this * rhs;
        }
        mint operator*(const long long &rhs) {
            return *this * rhs;
        }

        mint operator/(const mint &rhs) {
            return *this / rhs;
        }
        mint operator/(const long long &rhs) {
            return *this / rhs;
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

        bool operator<(const long long& other) { return _v < other; }

        bool operator>=(const mint& other) { return _v >= other._v; }

        bool operator>=(const long long& other) { return _v >= other; }

        bool operator<=(const mint& other) { return _v <= other._v; }

        bool operator<=(const long long& other) { return _v <= other; }

    };
}

#endif //BOJ_MODULO_HPP
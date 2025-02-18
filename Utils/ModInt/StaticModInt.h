//
// Created by june0 on 2025-02-18.
//

#ifndef BOJ_STATICMODINT_H
#define BOJ_STATICMODINT_H

#include <iostream>
#include "../TypeTraits.hpp"
#include "../../Math/Modulo.h"

namespace Utils {
    namespace ModInt {
        using namespace TypeTraits;
        using namespace Math;

        /**
         * an Integer type that modular arithmetic is automatically applied
         * @tparam MOD the modulus that will be applied to the value
         */
        template<int MOD,
                std::enable_if_t<(MOD >= 1)> * = nullptr>
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
        }; // class ModInt
    }
}

#endif //BOJ_STATICMODINT_H

//
// Created by june0 on 2024-04-14.
//

#ifndef BOJ_BIGDECIMAL_HPP
#define BOJ_BIGDECIMAL_HPP

#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <cassert>

// Start Utils
static const std::string ONE("1");
static const std::string ZERO("0");
static const std::string TEN("10");

static bool is_num(const char c) { return '0' <= c && c <= '9'; }
static void CHECK_INVALID_CHAR(const char c, int stage) {
    switch (stage) {
        case 0:
            std::cerr << "Invalid character: ";
            assert(is_num(c) || c == '.' || c == '+' || c == '-');
        case 1:
            std::cerr << "Invalid character: ";
            assert(is_num(c) || c == '.');
        case 2:
            std::cerr << "Invalid character: ";
            assert(is_num(c));
    }
}

/**
 * Parse a string into a integer part and fractional part
 * @param num string to be parsed
 * @param sign  true if negative
 * @param integer beginning position of the integer part
 * @param dot  the position of the decimal point
 * @param fraction beginning position of the fractional part
 * @param precision the precision of the decimal point
 * @return the precision of the number if successful and -1 on error
 */
static int parse(const std::string& num, int& sign, int& integer, int& dot, int& fraction, int& precision) {
    int ptr = 0;
    CHECK_INVALID_CHAR(num[ptr], 0);

    sign = 1;
    if (num[ptr] == '-') {
        sign = -1;
        ptr++;
    } else if (num[ptr] == '+') {
        ptr++;
    }
    CHECK_INVALID_CHAR(num[ptr], 1);

    int len = (int) num.size();
    if (ptr >= len) return -1; // empty or only sign

    // basic parsing
    integer = ptr;
    while (ptr < len && is_num(num[ptr])) ptr++;
    if (ptr < len) CHECK_INVALID_CHAR(num[ptr], 1); // if not ended

    dot = ptr;

    precision = 0;
    if (ptr < len && num[ptr] == '.') {
        precision = len - dot - 1;
        ptr++;
        CHECK_INVALID_CHAR(num[ptr], 2);
    }

    fraction = ptr;

    while (ptr < len && is_num(num[ptr])) ptr++;

    if (ptr < len) return -1; // invalid end

    // adjusting
    while (integer + 1 < dot && num[integer] == '0') integer++; // erase leading zeros

    if (precision == 0 && fraction + 1 == dot) fraction--; // num ends with '.'

    if (sign < 0 && num[integer] == '0' && precision == 0) sign = 1; // if num == -0 make it positive

    return precision;
}


struct Rounding_Type {};
struct Round_Up : public Rounding_Type {};
struct Round_Down : public Rounding_Type {};
struct Round_Up_Even : public Rounding_Type {};

// End Utils

class BigDecimal
{
    using value_type = std::string;

private:
    value_type value;
    static int precision;
    static Rounding_Type rounding;

public:
    /* Constructors */
    BigDecimal() = default;
    BigDecimal(const BigDecimal& num) : value(num.value) {}
    BigDecimal(const std::string& num) : value(num) {}
    BigDecimal(const char* num) : value(num) {}
    template<typename Arithmetic_Type>
    BigDecimal(const Arithmetic_Type num) : value(std::to_string(num)) {}

    /* Operators */
    BigDecimal operator+(const BigDecimal& num) {
        return _add(value, num.value);
    }



private:
    static value_type _add(const value_type& lhs, const value_type& rhs) {

    }
    static value_type _subtract(const value_type& lhs, const value_type& rhs);
    static value_type _multiply(const value_type& lhs, const value_type& rhs);
    static value_type _divide(const value_type& lhs, const value_type& rhs);
    static value_type _pow(const value_type& lhs, const value_type& rhs);
    static value_type _modulus(const value_type& lhs, const value_type& rhs);
    static value_type _round(const value_type& lhs, int n_digits) {
        int sign, ipos, dot, frac, prec;
        parse(lhs, sign, ipos, dot, frac, prec);

        if (n_digits >= prec)
    }

    static int _compare(const value_type& lhs, const value_type& rhs);
    static value_type _log2(const value_type& lhs, const value_type& rhs);
    static value_type _log10(const value_type& lhs, const value_type& rhs);
    static value_type _ln(const value_type& lhs, const value_type& rhs);
    static value_type _sin(const value_type& x);
    static value_type _cos(const value_type& x);
    static value_type _tan(const value_type& x);

public:
    static value_type add(const value_type& lhs, const value_type& rhs) {
        return _add(lhs, rhs);
    }
    static value_type subtract(const value_type& lhs, const value_type& rhs) {
        return _subtract(lhs, rhs);
    }
    static value_type multiply(const value_type& lhs, const value_type& rhs) {
        return _multiply(lhs, rhs);
    }
    static value_type divide(const value_type& lhs, const value_type& rhs) {
        return _divide(lhs, rhs);
    }
    static value_type pow(const value_type& lhs, const value_type& rhs) {
        return _pow(lhs, rhs);
    }
    static value_type modulus(const value_type& lhs, const value_type& rhs) {
        return _modulus(lhs, rhs);
    }
    static value_type round(const value_type& lhs, int n_digits) {
        return _round(lhs, n_digits);
    }

    static int compare(const value_type& lhs, const value_type& rhs) {
        return _compare(lhs, rhs);
    }
    static value_type log2(const value_type& lhs, const value_type& rhs) {
        return _log2(lhs, rhs);
    }
    static value_type log10(const value_type& lhs, const value_type& rhs) {
        return _log10(lhs, rhs);
    }
    static value_type ln(const value_type& lhs, const value_type& rhs) {
        return _ln(lhs, rhs);
    }
    static value_type sin(const value_type& x) {
        return _sin(x);
    }
    static value_type cos(const value_type& x) {
        return _cos(x);
    }
    static value_type tan(const value_type& x) {
        return _tan(x);
    }
};


#endif //BOJ_BIGDECIMAL_HPP

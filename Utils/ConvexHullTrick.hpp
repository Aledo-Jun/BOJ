//
// Created by june0 on 2024-05-24.
//
#include <functional> // std::greater, std::less
#include <vector>

#ifndef BOJ_CONVEXHULLTRICK_HPP
#define BOJ_CONVEXHULLTRICK_HPP

#include "using_templates.hpp"

/**
 * Convex Hull Trick implementation
 * @tparam Comp default to be std::greater which means query gives minimum value
 */
template<typename Comp = std::greater<>>
class ConvexHullTrick {
    Comp comp;

    struct Fraction {
        // a / b
        ll a, b;
        Fraction(ll a, ll b) : a(a), b(b) {
            if (b < 0) a = -a, b = -b; // keeps b to be positive
        }
        Fraction(ll a) : a(a), b(1) {} // NOLINT(implicit conversion)
        bool operator< (const Fraction& other) const {
            return (lll) a * other.b < (lll) b * other.a;
        }
        bool operator> (const Fraction& other) const {
            return (lll) a * other.b > (lll) b * other.a;
        }
        bool operator<= (const Fraction& other) const {
            return (lll) a * other.b <= (lll) b * other.a;
        }
        bool operator>= (const Fraction& other) const {
            return (lll) a * other.b >= (lll) b * other.a;
        }
    };

    struct Line : public Fraction {
        // f(x) = ax + b
        Line(ll a, ll b) : Fraction(a, b) {}
    };


    [[nodiscard]] // return the value of f(x) = ax + b
    ll get_value(const Line& f, const ll x) const { return f.a * x + f.b; }

    [[nodiscard]] // return the x pos of the intersection of the two given lines
    Fraction get_cross_x(const Line& l1, const Line& l2) const {
        // a1 x + b1 = a2 x + b2 -> (a1 - a2)x = (b2 - b1)
        return {l2.b - l1.b, l1.a - l2.a};
    }

    [[nodiscard]] // return cross_x(l1, l2) > cross_x(l2, l3)
    bool compare_cross(const Line& l1, const Line& l2, const Line& l3) const {
        return get_cross_x(l1, l2) > get_cross_x(l2, l3);
    }

    std::vector<Line> lines; // maintain the hull

public:
    void insert(ll a, ll b) {
        Line newLine(a, b);
        for (int sz = (int)lines.size(); sz > 1; sz--) {
            if (compare_cross(lines[sz - 2], lines[sz - 1], newLine)) lines.pop_back();
            else break;
        }
        lines.emplace_back(newLine);
    }

    ll query(ll x) {
        int l = 0, r = lines.size();
        while (l + 1 < r) {
            int m = l + ((r - l) >> 1);
            if (comp(Fraction(x), get_cross_x(lines[m - 1], lines[m]))) l = m;
            else r = m;
        }
        return get_value(lines[l], x);
    }

    // only can be used when x is monotonically increasing
    int ptr = 0;
    ll query_monotonic(ll x) {
        while (ptr + 1 < lines.size() && comp(get_value(lines[ptr], x), get_value(lines[ptr + 1], x))) ptr++;
        return get_value(lines[ptr], x);
    }
};

#endif //BOJ_CONVEXHULLTRICK_HPP

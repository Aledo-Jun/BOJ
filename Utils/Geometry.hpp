#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

#include "TypeTraits.hpp"

using namespace std;
using ll = long long;
using lld = long double;
namespace Utils
{
namespace Geometry
{
    using namespace TypeTraits;

// Structure representing the position of the point
    template<typename T = int>
    struct Point_type {
        using value_type = T;
        T x{}, y{};

        Point_type() = default;

        Point_type(T x, T y) : x(x), y(y) {}

        Point_type operator-(const Point_type &other) const {
            Point_type res(x - other.x, y - other.y);
            return res;
        }

        bool operator==(const Point_type &other) const {
            return x == other.x && y == other.y;
        }

        bool operator<(const Point_type &other) const {
            return x < other.x || (x == other.x && y < other.y);
        }

        bool operator<=(const Point_type &other) const {
            return *this < other || *this == other;
        }

        bool operator>(const Point_type &other) const {
            return !(*this < other) && !(*this == other);
        }

        bool operator>=(const Point_type &other) const {
            return *this > other || *this == other;
        }

        friend ostream &operator<<(ostream &out, const Point_type p) {
            out << p.x << ' ' << p.y << ' ';
            return out;
        }
    };

    using Point = Point_type<lld>;

    template<typename T = Point::value_type, typename V = wider_t<T>>
    V dist_square(const Point &a, const Point &b) {
        return V(a.x - b.x) * (a.x - b.x) + V(a.y - b.y) * (a.y - b.y);
    }

// CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
// Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
    template<typename T = Point::value_type, typename V = wider_t<T>>
    int CCW(const Point &p1, const Point &p2, const Point &p3) {
        V tmp =  V(p1.x * p2.y) + V(p2.x * p3.y) + V(p3.x * p1.y)
                 - V(p1.y * p2.x) - V(p2.y * p3.x) - V(p3.y * p1.x);
        if (tmp == 0) return 0;
        else if (tmp > 0) return 1;
        else return -1;
    }

// Convex Hull algorithm that returns a stack of the indices of the points
// that forms the convex hull(clockwise from top to bottom of the stack).
    template<typename T = Point::value_type, typename V = wider_t<T>>
    deque<int> convexHull(vector<Point> &v) {
        int n = (int) v.size();
        if (n == 0) return {};
        if (n == 1) return {0};

        // Find the lowest point (leftmost, bottommost)
        int lowest = 0;
        for (int i = 1; i < n; i++) {
            if (v[i].y < v[lowest].y ||
                (v[i].y == v[lowest].y && v[i].x < v[lowest].x)) {
                lowest = i;
            }
        }

        // Swap the lowest point to the first position
        swap(v[0], v[lowest]);

        // Sort the points by polar angle from the lowest point
        auto cmp = [&](const Point &p1, const Point &p2) {
            auto diff1 = p1 - v[0];
            auto diff2 = p2 - v[0];
            V cross = (V) diff1.x * diff2.y - (V) diff1.y * diff2.x;

            if (cross == 0) {
                // If two points have the same polar angle, choose the one closer to the origin
                return dist_square(p1, v[0]) < dist_square(p2, v[0]);
            }

            return cross > 0;
        };

        sort(v.begin() + 1, v.end(), cmp);

        deque<int> s;
        s.emplace_back(0);
        s.emplace_back(1);

        int next = 2;

        while (next < n) {
            while (s.size() >= 2) {
                int first, second;
                second = s.back();
                s.pop_back();
                first = s.back();

                if (CCW(v[first], v[second], v[next]) > 0) {
                    s.emplace_back(second);
                    break;
                }
            }
            s.emplace_back(next++);
        }
        return s;
    }

    struct PointPair {
        Point p1, p2;
    };

// Find two points that represent the diameter of the convex hull of the given set of points.
// (the distance between the two points is maximal of the distances between the points in the given set)
    template<typename T = Point::value_type, typename V = wider_t<T>>
    PointPair diameterOfConvexHull(vector<Point> v) {
        // deque of indices of points that form the convex hull.
        auto convex = convexHull(v);

        auto left = convex.begin(), right = convex.begin();
        for (auto it = convex.begin(); it != convex.end(); it++) {
            if (v[*it].y > v[*right].y ||
                (v[*it].y == v[*right].y && v[*it].x > v[*right].x))
                right = it;
        }
        // left : bottommost, leftmost
        // right : topmost, rightmost

        PointPair res;
        V mx = -1;

        // Rotating Calipers algorithm
        while (true) {
            auto l_diff = v[*left] - v[(left + 1 == convex.end()) ? (convex[0]) : *(left + 1)];
            auto r_diff = v[*right] - v[(right + 1 == convex.end()) ? (convex[0]) : *(right + 1)];

            V cross = (V) l_diff.x * r_diff.y - (V) l_diff.y * r_diff.x;
            if (cross < 0) {
                left++;
                if (left == convex.end()) break;
            } else if (cross > 0) {
                right++;
                if (right == convex.end()) right = convex.begin();
            } else {
                left++;
                right++;
                if (left == convex.end()) break;
                if (right == convex.end()) right = convex.begin();
            }

            auto d = dist_square(v[*left], v[*right]);
            if (d > mx) {
                mx = d;
                res.p1 = v[*left];
                res.p2 = v[*right];
            }
        }
        return res;
    }
} // namespace Geometry
} // namespace Utils
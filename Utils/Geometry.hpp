#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;
using ll = long long;
using lld = long double;
namespace Utils
{
namespace Geometry
{
    // Structure representing the position of the point
    template<typename T = int>
    struct Point_type {
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

    using Point = Point_type<>;

    ll dist(const Point &a, const Point &b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }

    lld area(const Point &a, const Point &b, const Point &c) {
        lld s = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
        return abs(s) / 2;
    }


    // CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
    // Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
    int CCW(const Point &p1, const Point &p2, const Point &p3) {
        ll tmp = (ll) (p1.x * p2.y + p2.x * p3.y + p3.x * p1.y
                       - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x);
        if (tmp == 0) return 0;
        else if (tmp > 0) return 1;
        else return -1;
    }

    // Identify whether the two lines(p1->p2, p3->p4) intersect or not using CCW.
    bool doesIntersect(Point p1, Point p2, Point p3, Point p4) {
        auto res1 = CCW(p1, p2, p3) * CCW(p1, p2, p4);
        auto res2 = CCW(p3, p4, p1) * CCW(p3, p4, p2);

        if (res1 == 0 && res2 == 0) {
            if (p1 > p2) swap(p1, p2);
            if (p3 > p4) swap(p3, p4);

            return (p3 <= p2 && p1 <= p4);
        } else if (res1 <= 0 && res2 <= 0)
            return true;
        else
            return false;
    }

    // Convex Hull algorithm that returns a stack of the indices of the points
    // that forms the convex hull(clockwise from top to bottom of the stack).
    deque<int> convexHull(vector<Point> &v) {
        int n = v.size();
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
            ll cross = (ll) diff1.x * diff2.y - (ll) diff1.y * diff2.x;

            if (cross == 0) {
                // If two points have the same polar angle, choose the one closer to the origin
                return dist(p1, v[0]) < dist(p2, v[0]);
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
        ll mx = -1;

        // Rotating Calipers algorithm
        while (true) {
            auto l_diff = v[*left] - v[(left + 1 == convex.end()) ? (convex[0]) : *(left + 1)];
            auto r_diff = v[*right] - v[(right + 1 == convex.end()) ? (convex[0]) : *(right + 1)];

            ll cross = (ll) l_diff.x * r_diff.y - (ll) l_diff.y * r_diff.x;
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

            ll d = dist(v[*left], v[*right]);
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
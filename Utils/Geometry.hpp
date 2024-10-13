#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

#include "TypeTraits.hpp"
#include "using_templates.hpp"

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

    using Point = Point_type<double>;

    template<typename T = Point::value_type, typename V = wider_t<T>>
    V dist_square(const Point &a, const Point &b) {
        return V(a.x - b.x) * (a.x - b.x) + V(a.y - b.y) * (a.y - b.y);
    }

// CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
// Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
    template<typename T = Point::value_type, typename V = wider_t<T>>
    int CCW(const Point &p1, const Point &p2, const Point &p3) {
        V tmp =  V(p1.x) * p2.y + V(p2.x) * p3.y + V(p3.x) * p1.y
                 - V(p1.y) * p2.x - V(p2.y) * p3.x - V(p3.y) * p1.x;
        if (tmp == 0) return 0;
        else if (tmp > 0) return 1;
        else return -1;
    }

// Convex Hull algorithm that returns a deque of the indices of the points
// that forms the convex hull(clockwise from top to bottom of the deque).
    template<typename T = Point::value_type, typename V = wider_t<T>>
    deque<int> convexHull(vector<Point> &v) {
        int n = (int) v.size();
        if (n <= 1) return {};

        sort(all(v));
        deque<int> hull;

        // Lower hull
        for (int i = 0; i < n; i++) {
            while (hull.size() >= 2 && CCW(v[hull[hull.size() - 2]], v[hull.back()], v[i]) <= 0)
                hull.pop_back();
            hull.push_back(i);
        }

        // Upper hull
        int t = (int) hull.size() + 1;
        for (int i = n - 2; i >= 0; i--) {
            while (hull.size() >= t && CCW(v[hull[hull.size() - 2]], v[hull.back()], v[i]) <= 0)
                hull.pop_back();
            hull.push_back(i);
        }

        hull.pop_back(); // Remove the duplicate point
        return hull;
    }

// Find two points that represent the diameter of the convex hull of the given set of points.
// (the distance between the two points is maximal of the distances between the points in the given set)
    template<typename T = Point::value_type, typename V = wider_t<T>,
             typename Dist_func = function<V(Point,Point)>>
    pair<Point,Point> diameterOfConvexHull(vector<Point> &v, Dist_func dist = dist_square) {
        // deque of indices of points that form the convex hull.
        auto convex = convexHull(v);
        int m = (int) convex.size();

        int k = 1;
        pair<Point, Point> best_pair;
        V max_dist = 0;

        // Rotating calipers algorithm
        for (int i = 0; i < m; i++) {
            while (true) {
                V curr_dist = dist(v[convex[i]], v[convex[k]]);
                V next_dist = dist(v[convex[i]], v[convex[(k + 1) % m]]);
                if (next_dist > curr_dist) k = (k + 1) % m;
                else break;
            }
            V d = dist(v[convex[i]], v[convex[k]]);
            if (d > max_dist) {
                max_dist = d;
                best_pair = {v[convex[i]], v[convex[k]]};
            }
        }

        return best_pair;
    }

// Find the closest pair of points among the given set of points
    template<typename T = Point::value_type, typename V = wider_t<T>,
             typename Dist_func = function<V(Point,Point)>>
    pair<Point,Point> closestPointPair(vector<Point> &v, Dist_func dist = dist_square) {
        sort(all(v));

        auto dnc = [&](auto &&self, int l, int r) -> pair<Point,Point> {
            if (r - l <= 3) {
                pair<Point,Point> res;
                V mx = numeric_limits<V>::max();
                for (int i = l; i <= r; i++) {
                    for (int j = i + 1; j <= r; j++) {
                        V d = dist(v[i], v[j]);
                        if (d < mx) {
                            mx = d;
                            res = {v[i], v[j]};
                        }
                    }
                }
                return res;
            }

            int m = (l + r) >> 1;
            auto midPoint = v[m];

            auto [l1, l2] = self(self, l, m);
            V dl = dist(l1, l2);
            auto [r1, r2] = self(self, m+1, r);
            V dr = dist(r1, r2);

            V d = min(dist(l1, l2), dist(r1, r2));
            auto best = (dl < dr) ? make_pair(l1, l2) : make_pair(r1, r2);

            // Create a strip of points near the dividing line within distance d
            vector<Point> strip; strip.reserve(r-l+1);
            for (int i = l; i <= r; i++) {
                if (abs(dist(v[i], {midPoint.x, v[i].y})) < d) {
                    strip.push_back(v[i]);
                }
            }
            // Sort the strip by y-coordinate for better efficiency
            sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) { return a.y < b.y; });

            // Check for the closest pair in the strip
            V minStripDist = d;
            for (int i = 0; i < (int)strip.size(); i++) {
                for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < minStripDist; j++) {
                    V dStrip = dist(strip[i], strip[j]);
                    if (dStrip < minStripDist) {
                        minStripDist = dStrip;
                        best = {strip[i], strip[j]};
                    }
                }
            }
            return best;
        };

        return dnc(dnc, 0, v.size() - 1);
    }

    // Find the radius of the smallest circle that encloses all given points
    // It uses a kind of gradient descent, so that the hyper-param adjustment might be needed
    template<typename T = Point::value_type, typename V = wider<T>>
    T enclosing_circle(const vector<Point> &v) {
        int n = (int) v.size();
        Point c{0, 0};
        for (auto &[x, y]: v) {
            c.x += x, c.y += y;
        }
        c.x /= n, c.y /= n;

        double w = 0.1;
        int epoch = 10'000;

        V mx;
        for (int i = 0; i < epoch; i++) {
            mx = 0;
            Point mxPoint;
            for (const auto &e: v) {
                auto d = dist_square(c, e);
                if (mx < d) {
                    mxPoint = e;
                    mx = d;
                }
            }

            c.x += (mxPoint.x - c.x) * w;
            c.y += (mxPoint.y - c.y) * w;
            w *= 0.995;
        }
        return sqrt(mx);
    }
} // namespace Geometry
} // namespace Utils
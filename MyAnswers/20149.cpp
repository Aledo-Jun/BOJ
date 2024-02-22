//
// Created by june0 on 2024-02-22.
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

namespace Utils
{
    namespace Geometry
    {
        // Structure representing the position of the point
        struct Point {
            int x{}, y{};

            Point() = default;

            Point(int x, int y) : x(x), y(y) {}

            Point operator-(const Point &other) const {
                Point res(x - other.x, y - other.y);
                return res;
            }

            bool operator==(const Point &other) const {
                return x == other.x && y == other.y;
            }

            bool operator<(const Point &other) const {
                return x < other.x || (x == other.x && y < other.y);
            }

            bool operator<=(const Point &other) const {
                return *this < other || *this == other;
            }

            bool operator>(const Point &other) const {
                return !(*this < other) && !(*this == other);
            }

            bool operator>=(const Point &other) const {
                return *this > other || *this == other;
            }

            friend ostream &operator<<(ostream &out, const Point p) {
                out << p.x << ' ' << p.y << ' ';
                return out;
            }
        };

        ll dist(const Point &a, const Point &b) {
            return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
        }

        // CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
        // Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
        int CCW(const Point &p1, const Point &p2, const Point &p3) {
            ll tmp = (ll)p1.x * p2.y + (ll)p2.x * p3.y + (ll)p3.x * p1.y
                     - (ll)p1.y * p2.x - (ll)p2.y * p3.x - (ll)p3.y * p1.x;
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
    } // namespace Geometry
} // namespace Utils

int32_t main() {
    fastIO;
    Utils::Geometry::Point p1, p2, p3, p4;
    cin >> p1.x >> p1.y >> p2.x >> p2.y;
    if (p1 > p2) swap(p1, p2);
    cin >> p3.x >> p3.y >> p4.x >> p4.y;
    if (p3 > p4) swap(p3, p4);

    if (Utils::Geometry::doesIntersect(p1,p2,p3,p4)){
        cout << 1 << endl;
        cout << fixed << setprecision(10);
        if (Utils::Geometry::CCW(p1,p2,p3) == 0 && Utils::Geometry::CCW(p1,p2,p4) == 0){
            if (p2 == p3) return cout << p2.x << ' ' << p2.y, 0;
            if (p1 == p4) return cout << p1.x << ' ' << p1.y, 0;
            return 0;
        }
        lld x, y;
        if (p1.x == p2.x){
            lld slope2 = (lld)(p4.y - p3.y) / (p4.x - p3.x);
            lld intercept2 = (lld)p3.y - slope2 * p3.x;

            x = p1.x;
            y = slope2 * x + intercept2;
        } else if (p3.x == p4.x){
            lld slope1 = (lld)(p2.y - p1.y) / (p2.x - p1.x);
            lld intercept1 = (lld)p1.y - slope1 * p1.x;

            x = p3.x;
            y = slope1 * x + intercept1;
        } else {
            lld slope1 = (lld) (p2.y - p1.y) / (p2.x - p1.x);
            lld intercept1 = (lld)p1.y - slope1 * p1.x;
            lld slope2 = (lld) (p4.y - p3.y) / (p4.x - p3.x);
            lld intercept2 = (lld)p3.y - slope2 * p3.x;

            x = (intercept2 - intercept1) / (slope1 - slope2);
            y = slope1 * x + intercept1;
        }

        cout << x << ' ' << y;
    } else cout << 0;

    return 0;
}
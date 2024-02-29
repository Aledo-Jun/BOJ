//
// Created by june0 on 2024-02-29.
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

// Convex Hull algorithm that returns a stack of the indices of the points
// that forms the convex hull(clockwise from top to bottom of the stack).
deque<int> convexHull(vector<Point> &v) {
    int n = (int) v.size();

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

lld distance_line(const Point& l1, const Point& l2, const Point& p){
    lld a = (l2.y - l1.y);
    lld b = -(l2.x - l1.x);
    lld c = -(b * l1.y + a * l1.x);

    return abs(a * p.x + b * p.y + c) / sqrt(a * a + b * b);
}

int32_t main() {
    fastIO;
    int n;
    int tc = 1;
    while (cin >> n){
        if (n == 0) break;

        vector<Point> v(n);
        for (auto& p : v) cin >> p.x >> p.y;

        auto convex = convexHull(v);

        auto it1 = convex.begin();
        auto it2 = convex.begin() + 1;
        lld ans = numeric_limits<lld>::max();

        while (it1 != convex.end()){
            lld tmp = 0;
            for (auto it = (it2 + 1 == convex.end() ? convex.begin() : it2 + 1); it != it1; (it == convex.end() - 1) ? it = convex.begin() : it++){
                tmp = max(tmp, distance_line(v[*it1], v[*it2], v[*it]));
            }
            it1++;
            it2++;
            if (it2 == convex.end()) it2 = convex.begin();
            ans = min(ans, tmp);
        }

        ans = ceilf(ans * 100);
        cout << fixed << setprecision(2);
        cout << "Case " << tc++ << ": " << ans / 100 << endl;
    }

    return 0;
}
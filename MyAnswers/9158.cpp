//
// Created by june0 on 2024-09-26.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

// Primary template: Not defined for unsupported types
template<typename T>
struct wider;

// Specialization for int
template<>
struct wider<int32_t> {
    using type = int64_t;
};

// Specialization for double
template<>
struct wider<double_t> {
    using type = long double;
};

template<>
struct wider<long double> {
    using type = long double;
};

// Helper type alias for easier use
template<typename T>
using wider_t = typename wider<T>::type;

// Structure representing the position of the point
template<typename T = int>
struct Point_type {
    using value_type = T;
    T x{}, y{}, z{};

    Point_type() = default;

    Point_type(T x, T y, T z) : x(x), y(y), z(z) {}

    Point_type operator-(const Point_type &other) const {
        Point_type res(x - other.x, y - other.y, z - other.z);
        return res;
    }

    bool operator==(const Point_type &other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

using Point = Point_type<double>;

template<typename T = Point::value_type, typename V = wider_t<T>>
V dist_square(const Point &a, const Point &b) {
    return V(a.x - b.x) * (a.x - b.x)
           + V(a.y - b.y) * (a.y - b.y)
           + V(a.z - b.z) * (a.z - b.z);
}

int32_t main() {
    fastIO;
    int n;
    while (cin >> n) {
        if (n == 0) break;

        vector<Point> v(n);
        Point c{0, 0, 0};
        for (auto &[x, y, z]: v) {
            cin >> x >> y >> z;
            c.x += x, c.y += y, c.z += z;
        }
        c.x /= n, c.y /= n, c.z /= n;

        double w = 0.1;
        double mx;
        for (int i = 0; i < 3000; i++) {
            // get Radius
            mx = 0;
            Point mxPoint;
            for (const auto &e: v) {
                auto d = dist_square(c, e);
                if (mx < d) {
                    mxPoint = e;
                    mx = d;
                }
            }

            // set center
            c.x += (mxPoint.x - c.x) * w;
            c.y += (mxPoint.y - c.y) * w;
            c.z += (mxPoint.z - c.z) * w;
            w *= 0.995;
        }

        cout << fixed << setprecision(5);
        cout << sqrt(mx) << endl;
    }
    return 0;
}

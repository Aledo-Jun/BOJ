//
// Created by june0 on 2024-02-26.
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

/**
 * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
 *
 * @tparam T ValueType
 * @param g The given graph
 * @param g_r The inverse of the given graph
 * @return std::vector that indicates which scc the vertex is belonging
 */
template<typename T>
vector<int> scc(const graph<T> &g, const graph<T> &g_r) {
    std::vector<bool> visited(g.size(), false);
    std::stack<int> finishing_time;

    std::function<void(int)> dfs_scc = [&](int u) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &[v, w]: g[u]) {
            dfs_scc(v);
        }
        finishing_time.emplace(u);
    };

    for (int i = 0; i < g.size(); i++) {
        if (visited[i]) continue;
        dfs_scc(i);
    }

    visited.assign(g.size(), false);
    vector<int> res(g.size(), -1);

    std::function<void(int,int)> inv_dfs_scc = [&](int u, int idx) {
        for (const auto& [v, w]: g_r[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            inv_dfs_scc(v, idx);
        }
        res[u] = idx;
    };

    int idx = 0;
    while (!finishing_time.empty()) {
        int u = finishing_time.top();
        finishing_time.pop();
        if (visited[u]) continue;
        visited[u] = true;
        inv_dfs_scc(u, idx++);
    }

    return res;
}

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

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    n *= 3;
    vector<pair<Point,Point>> sticks(1);
    graph<int> g(n * 2 + 1), g_r(n * 2 + 1);
    for (int i = 1; i <= n; i++) {
        Point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        for (int j = 1; j < sticks.size(); j++){
            if (!doesIntersect(a, b, sticks[j].first, sticks[j].second)) continue;
            g[i + n].emplace_back(-j + n, 1);
            g[j + n].emplace_back(-i + n, 1);
            g_r[-i + n].emplace_back(j + n, 1);
            g_r[-j + n].emplace_back(i + n, 1);
        }
        sticks.emplace_back(a, b);
        if (i % 3 == 0){
            g[-(i - 2) + n].emplace_back(i - 1 + n, 1);
            g[-(i - 1) + n].emplace_back(i + n, 1);
            g[-i + n].emplace_back(i - 2 + n, 1);

            g[-(i - 2) + n].emplace_back(i + n, 1);
            g[-(i - 1) + n].emplace_back(i - 2 + n, 1);
            g[-i + n].emplace_back(i - 1 + n, 1);

            g_r[i - 1 + n].emplace_back(-(i - 2) + n, 1);
            g_r[i + n].emplace_back(-(i - 1) + n, 1);
            g_r[i - 2 + n].emplace_back(-i + n, 1);

            g_r[i - 1 + n].emplace_back(-i + n, 1);
            g_r[i + n].emplace_back(-(i - 2) + n, 1);
            g_r[i - 2 + n].emplace_back(-(i - 1) + n, 1);
        }
    }

    auto res = scc(g, g_r);
    bool flag = true;

    for (int i = 1; i <= n; i++) {
        if (res[i + n] == res[-i + n]) {
            flag = false;
            break;
        }
    }

    if (flag){
        vector<int> ans;
        for (int i = 1; i <= n; i++) {
            if (res[i + n] < res[-i + n]) ans.emplace_back(i);
        }
        cout << ans.size() << endl;
        for (const auto& e : ans)
            cout << e << ' ';
    } else {
        cout << -1;
    }

    return 0;
}
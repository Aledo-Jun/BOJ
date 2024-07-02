//
// Created by june0 on 2024-07-03.
//
#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using lld = double;

template<typename T = int>
struct Point {
    T x{}, y{};

    Point() = default;

    Point(T x, T y) : x(x), y(y) {}
};
using point = Point<lld>;

lld dist(const point &a, const point &b) {
    return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

lld area(const point &a, const point &b, const point &c) {
    lld s = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
    return abs(s) / 2;
}

const lld eps = 1e-9;
int n;
vector<point> v;
lld L; // circumference

point get_point(int idx, lld t) {
    return {v[idx].x * (1 - t) + v[idx + 1].x * t,
            v[idx].y * (1 - t) + v[idx + 1].y * t};
}

pair<int,lld> get_point_by_arc(lld len) {
    while (len >= L) len -= L;
    int idx = 0;
    while (len - dist(v[idx], v[idx + 1]) > eps) {
        len -= dist(v[idx], v[idx + 1]);
        idx++;
    }
    if (abs(len) < eps) return {idx, 0};
    lld t = len / dist(v[idx], v[idx + 1]);
    return {idx, t};
}

lld area_diff(int idx1, int idx2, lld t1, lld t2) {
    auto p1 = get_point(idx1, t1);
    auto p2 = get_point(idx2, t2);
    lld s1 = area(p1, p2, v[idx1 + 1]);
    for (int i = idx1 + 1; i < idx2; i++)
        s1 += area(p2, v[i], v[i + 1]);

    lld s2 = area(p1, p2, v[idx2 + 1]);
    for (int i = idx2 + 1; i < n; i++)
        s2 += area(p1, v[i], v[i + 1]);
    for (int i = 0; i < idx1; i++)
        s2 += area(p1, v[i], v[i + 1]);

    //cout << s1 << ' ' << s2 << endl;

    return s1 - s2;
}

int check(lld start) {
    auto [i1, t1] = get_point_by_arc(start);
    auto [i2, t2] = get_point_by_arc(start + L / 2);
    if (i1 > i2) swap(i1, i2), swap(t1, t2);
    lld diff = area_diff(i1, i2, t1, t2);
    return abs(diff) < eps ? 0 : (diff > 0) - (diff < 0);
}

int32_t main() {
    fastIO;
    cin >> n;
    v.resize(n);
    for (auto &[x, y]: v) cin >> x >> y;
    L = dist(v[0], v[n - 1]);
    for (int i = 0; i < n - 1; i++) {
        L += dist(v[i], v[i + 1]);
    }
    v.emplace_back(v[0]);

    int epoch = 50;
    lld l = 0, r = L / 2;
    int st = check(0);
    while (epoch--) {
        lld m = (l + r) / 2;
        int chk = check(m);
        if (chk == 0) {
            l = m;
            break;
        }
        if (chk == st) l = m;
        else r = m;
    }

    cout << fixed << setprecision(10);
    cout << "YES" << endl;
    auto [i1, t1] = get_point_by_arc(l);
    auto [i2, t2] = get_point_by_arc(l + L / 2);
    cout << i1 + 1 << ' ' << t1 << endl << i2 + 1 << ' ' << t2 << endl;


    return 0;
}
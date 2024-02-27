//
// Created by june0 on 2024-02-27.
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

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        // 1 ~ n: horizontal line, n + 1 ~ n + m: vertical line
        graph<int> g((n + m) * 2 + 1), g_r((n + m) * 2 + 1);
        for (int i = 0; i < k; i++){
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            if (a == c && b == d) continue;
            b += n, d += n;
            if (a < c && d < b) {
                a = -a, c = -c;
                b = -b, d = -d;
            } else if (a < c) {
                b = -b, d = -d;
            } else if (d < b) {
                a = -a, c = -c;
            }

            if (a == c){
                g[-a + n + m].emplace_back(c + n + m, 1);
                g[-c + n + m].emplace_back(a + n + m, 1);

                g_r[c + n + m].emplace_back(-a + n + m, 1);
                g_r[a + n + m].emplace_back(-c + n + m, 1);
            } else if (b == d){
                g[-b + n + m].emplace_back(d + n + m, 1);
                g[-d + n + m].emplace_back(b + n + m, 1);

                g_r[d + n + m].emplace_back(-b + n + m, 1);
                g_r[b + n + m].emplace_back(-d + n + m, 1);
            } else {
                g[-a + n + m].emplace_back(b + n + m, 1);
                g[-b + n + m].emplace_back(a + n + m, 1);
                g[-a + n + m].emplace_back(c + n + m, 1);
                g[-c + n + m].emplace_back(a + n + m, 1);
                g[-b + n + m].emplace_back(d + n + m, 1);
                g[-d + n + m].emplace_back(b + n + m, 1);
                g[-d + n + m].emplace_back(c + n + m, 1);
                g[-c + n + m].emplace_back(d + n + m, 1);

                g_r[b + n + m].emplace_back(-a + n + m, 1);
                g_r[a + n + m].emplace_back(-b + n + m, 1);
                g_r[c + n + m].emplace_back(-a + n + m, 1);
                g_r[a + n + m].emplace_back(-c + n + m, 1);
                g_r[d + n + m].emplace_back(-b + n + m, 1);
                g_r[b + n + m].emplace_back(-d + n + m, 1);
                g_r[c + n + m].emplace_back(-d + n + m, 1);
                g_r[d + n + m].emplace_back(-c + n + m, 1);
            }
        }

        auto res = scc(g, g_r);
        bool flag = true;

        for (int i = 1; i <= n + m; i++) {
            if (res[i + n + m] == res[-i + n + m]) {
                flag = false;
                break;
            }
        }

        if (flag) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}
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

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n * 2 + 1), g_r(n * 2 + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[-u + n].emplace_back(v + n, 1);
        g[-v + n].emplace_back(u + n, 1);
        g_r[v + n].emplace_back(-u + n, 1);
        g_r[u + n].emplace_back(-v + n, 1);
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
        cout << 1 << endl;
        for (int i = 1; i <= n; i++)
            cout << (res[i + n] > res[-i + n]) << ' ';
    } else {
        cout << 0 << endl;
    }

    return 0;
}
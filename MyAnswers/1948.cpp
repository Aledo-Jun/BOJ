//
// Created by june0 on 2024-02-23.
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

namespace Graph {
    // Assumes that graph is 1-indexed //
    const size_t INF = LLONG_MAX;
#pragma ide diagnostic push
#pragma ide diagnostic ignored "UnusedParameter"
    // because of unusual bug(it seems to be)
    // that ide warns that the functions parameter with template syntax is never used.

    template<typename T>
    void dfs_for_topological_order(graph<T> &g, int u, std::vector<bool> &visited, std::vector<int> &order) {
        if (visited[u]) return;
        visited[u] = true;

        for (const auto &[v, w]: g[u]) {
            dfs_for_topological_order(g, v, visited, order);
        }

        order.emplace_back(u);
    }

    template<typename T>
    std::vector<int> topological_order_dfs(const graph<T> &g) {
        int n = (int) g.size() - 1;
        std::vector<bool> visited(n + 1, false);
        std::vector<int> result;

        for (int i = 1; i <= n; i++)
            dfs_for_topological_order(g, i, visited, result);

        std::reverse(result.begin(), result.end());
        return result;
    }

    template<typename T>
    std::vector<int> topological_order_degree(const graph<T> &g) {
        int n = (int) g.size() - 1;
        std::vector<int> in_degree(g.size(), 0);
        std::vector<int> result;
        std::queue<int> q;
        for (int u = 1; u <= n; u++){
            for (const auto&[v, w] : g[u])
                in_degree[v]++;
        }
        for (int u = 1; u <= n; u++){
            if (in_degree[u] == 0) q.emplace(u);
        }

        while (!q.empty()){
            int u = q.front(); q.pop();
            result.emplace_back(u);

            for (const auto&[v, w] : g[u]){
                in_degree[v]--;
                if (in_degree[v] == 0) q.emplace(v);
            }
        }

        return result;
    }

#pragma ide diagnostic pop
} // namespace Graph

using namespace Graph;

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1), g_rev(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g_rev[v].emplace_back(u, w);
    }

    int start, end;
    cin >> start >> end;

    vector<ll> dist(n + 1, -INT_MAX);
    dist[start] = 0;
    auto topological_order = topological_order_degree(g);

    for (const auto& u : topological_order){
        if (dist[u] == -INT_MAX) continue;
        for (const auto& [v, w]: g[u]){
            if (dist[v] < dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }

    int cnt = 0;
    queue<int> q;
    q.emplace(end);
    vector<bool> visited(n + 1, false);
    visited[end] = true;
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (const auto& [v, w]: g_rev[u]){
            if (dist[v] + w == dist[u]) {
                cnt++;
                if (!visited[v]) {
                    visited[v] = true;
                    q.emplace(v);
                }
            }
        }
    }

    cout << dist[end] << endl << cnt;

    return 0;
}
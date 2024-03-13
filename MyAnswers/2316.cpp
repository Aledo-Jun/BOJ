//
// Created by june0 on 2024-03-13.
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
     * Dinic's algorithm to find the maximum flow of the given network graph.
     */
class Dinic {
private:
    struct Edge {
        int u, v, cap, rev;
        Edge(int u, int v, int cap, int rev) : u(u), v(v), cap(cap), rev(rev) {}
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> level, ptr;

    bool bfs(int s, int t) {
        level.assign(n, -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (const Edge &e: g[u]) {
                if (e.cap > 0 && level[e.v] == -1) {
                    level[e.v] = level[u] + 1;
                    q.push(e.v);
                }
            }
        }

        return level[t] != -1;
    }

    int dfs(int u, int t, int flow) {
        if (u == t)
            return flow;

        for (; ptr[u] < g[u].size(); ptr[u]++) {
            Edge &e = g[u][ptr[u]];

            if (e.cap > 0 && level[e.v] == level[u] + 1) {
                int bottleneck = dfs(e.v, t, min(flow, e.cap));

                if (bottleneck > 0) {
                    e.cap -= bottleneck;
                    g[e.v][e.rev].cap += bottleneck;
                    return bottleneck;
                }
            }
        }
        return 0;
    }

public:
    explicit Dinic(int n) : n(n), g(n), level(n), ptr(n) {}

    void addEdge(int u, int v, int cap) {
        g[u].emplace_back(u, v, cap, g[v].size());
        g[v].emplace_back(v, u, 0, g[u].size() - 1);
    }

    int maxFlow(int s, int t) {
        int flow = 0;

        while (bfs(s, t)) {
            ptr.assign(n, 0);
            flow += dfs(s, t, INT_MAX);
        }

        return flow;
    }
};

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;

    Dinic dinic(2 * n + 1); // 1 ~ n : out-flow, n + 1 ~ 2n : in-flow
    for (int i = 1; i <= n; i++){
        if (i == 2) dinic.addEdge(i + n, i, INT_MAX);
        else dinic.addEdge(i + n, i, 1);
    }
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        dinic.addEdge(u, v + n, 1);
        dinic.addEdge(v, u + n, 1);
    }

    cout << dinic.maxFlow(1, 2);

    return 0;
}
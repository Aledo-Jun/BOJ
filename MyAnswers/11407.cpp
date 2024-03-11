//
// Created by june0 on 2024-03-11.
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

class MinCostMaxFlow {
    const int INF = 1e9;
    struct Edge {
        int u, v, cap, rev, cost;
        Edge(int u, int v, int cap, int rev, int cost) : u(u), v(v), cap(cap), rev(rev), cost(cost) {}
    };
private:
    int n;
    vector<vector<Edge>> g;
    vector<int> dist;
    vector<Edge*> prev;
    bool bellmanFord(int s, int t) {
        dist.assign(n, INF);
        queue<int> q;
        vector<bool> is_in_q(n, false);

        dist[s] = 0;
        q.emplace(s);
        is_in_q[s] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            is_in_q[u] = false;
            for (auto &e: g[u]) {
                if (e.cap > 0 && dist[e.v] > dist[u] + e.cost) {
                    dist[e.v] = dist[u] + e.cost;
                    prev[e.v] = &e;
                    if (!is_in_q[e.v]) {
                        is_in_q[e.v] = true;
                        q.emplace(e.v);
                    }
                }
            }
        }
        return dist[t] != INF;
    }

public:
    explicit MinCostMaxFlow(int n) : n(n), g(n), dist(n), prev(n) {}
    void addEdge(int u, int v, int cap, int cost) {
        g[u].emplace_back(u, v, cap, g[v].size(), cost);
        g[v].emplace_back(v, u, 0, g[u].size() - 1, -cost);
    }
    pair<int, int> minCostMaxFlow(int s, int t) {
        int flow = 0, cost = 0;
        while (bellmanFord(s, t)) {
            // find minimum flow
            int curr = INF;
            for (auto e = prev[t]; e; e = prev[e->u]){
                curr = min(curr, e->cap);
            }
            flow += curr;

            for (auto e = prev[t]; e; e = prev[e->u]){
                cost += curr * e->cost;

                // reverse direction
                e->cap -= curr;
                g[e->v][e->rev].cap += curr;
            }
        }
        return {flow, cost};
    }
};

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;

    int S = n + m, T = n + m + 1;
    MinCostMaxFlow minCostMaxFlow(n + m + 2);

    for (int i = m; i < n + m; i++){
        int x; cin >> x;
        minCostMaxFlow.addEdge(i, T, x, 0);
    }
    for (int i = 0; i < m; i++){
        int x; cin >> x;
        minCostMaxFlow.addEdge(S, i, x, 0);
    }
    matrix<int> capacity(m, vector<int>(n));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            cin >> capacity[i][j];
        }
    }
    for (int i = 0; i < m; i++){
        for (int j = m; j < n + m; j++){
            int x; cin >> x;
            minCostMaxFlow.addEdge(i, j, capacity[i][j - m], x);
        }
    }

    const auto& [ans1, ans2] = minCostMaxFlow.minCostMaxFlow(S, T);
    cout << ans1 << endl << ans2;

    return 0;
}
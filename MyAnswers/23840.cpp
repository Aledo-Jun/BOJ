//
// Created by june0 on 2024-02-06.
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

#define int ll

const int INF = 1LL << 40;


int _tsp(const matrix<int>& g, matrix<int>& dp, int node, int visited) {
    if (visited == (1 << g.size()) - 1) {
        return g[node].back();
    }

    if (dp[node][visited] != -1) return dp[node][visited];

    dp[node][visited] = INF;

    for (int i = 0; i < g.size(); i++){
        if (g[node][i] == INF) continue;
        if (visited & (1 << i)) continue;

        dp[node][visited] = min(dp[node][visited],
                                g[node][i] + _tsp(g, dp, i, visited | (1 << i)));
    }
    return dp[node][visited];
}

int tsp(const matrix<int>& g){
    int n = (int) g.size();
    matrix<int> dp(n, vector<int>(1 << n, -1));

    return _tsp(g, dp, 0, 1);
}

vector<int> dijkstra(const graph<int> &g, int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<int> dist(g.size(), INF);
    pq.emplace(0, start);
    dist[start] = 0;
    while (!pq.empty()) {
        auto [distance, u] = pq.top();
        pq.pop();

        if (distance > dist[u]) continue;

        for (const auto &[v, w]: g[u]) {
            if (distance + w < dist[v]) {
                dist[v] = distance + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    int start, end, p;
    cin >> start >> end >> p;

    vector<int> P(p + 1);
    P[0] = start;
    for (int i = 1; i <= p; i++) cin >> P[i];

    matrix<int> dist(p + 1);
    for (int i = 0; i <= p; i++)
        dist[i] = dijkstra(g, P[i]);

    matrix<int> dist_p(p + 1);
    for (int i = 0; i <= p; i++){
        for (int j = 0; j <= p; j++){
            dist_p[i].emplace_back(dist[i][P[j]]);
        }
        dist_p[i].emplace_back(dist[i][end]);
    }

    int ans = tsp(dist_p);
    cout << (ans == INF ? -1 : ans);

    return 0;
}


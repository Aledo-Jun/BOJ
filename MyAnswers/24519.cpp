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
const int INF = 0x3f3f3f3f3f3f3f3f;

void path_tsp(const matrix<int>& g, const matrix<int>& dp, vector<int>& path, int node, int visited) {
    path.emplace_back(node);

    if (visited == (1 << g.size()) - 1) return;

    pair<int, int> next(INF, -1);
    for (int i = 1; i < g.size(); i++) {
        if (g[node][i] == INF) continue;
        if (visited & (1 << i)) continue;

        if (max(g[node][i], dp[i][visited | (1 << i)]) < next.first) {
            next.first = max(g[node][i], dp[i][visited | (1 << i)]);
            next.second = i;
        }
    }
    if (next.second == -1) return;

    path_tsp(g, dp, path, next.second, visited | (1 << next.second));
}

int _tsp(const matrix<int>& g, matrix<int>& dp, int node, int visited) {
    if (visited == (1 << g.size()) - 1) {
        return g[node][0];
    }

    if (dp[node][visited] != -1) return dp[node][visited];

    dp[node][visited] = INF;

    for (int i = 0; i < g.size(); i++){
        if (g[node][i] == INF) continue;
        if (visited & (1 << i)) continue;

        dp[node][visited] = min(dp[node][visited],
                                max(g[node][i], _tsp(g, dp, i, visited | (1 << i))));
    }
    return dp[node][visited];
}

auto tsp(const matrix<int>& g){
    int n = (int) g.size();
    matrix<int> dp(n, vector<int>(1 << n, -1));

    auto val = _tsp(g, dp, 0, 1);

    vector<int> path;
    path_tsp(g, dp, path, 0, 1);

    return make_pair(val, path);
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    matrix<int> g(n, vector<int>(n, INF));
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u - 1][v - 1] = w;
    }

    auto ans = tsp(g);

    if (ans.first == INF) cout << -1;
    else {
        cout << ans.first << endl;
        for (const auto& e : ans.second)
            cout << e + 1 << ' ';
    }

    return 0;
}

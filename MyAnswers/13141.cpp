//
// Created by june0 on 2024-03-05.
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

const size_t INF = INT_MAX;

template<typename T>
matrix<std::size_t> floydWarshall(const graph<T> &g) {
    int n = (int) g.size() - 1;
    matrix<std::size_t> res(n + 1, std::vector<std::size_t>(n + 1, INF));
    for (int i = 1; i <= n; i++) res[i][i] = 0;
    for (int u = 1; u <= n; u++) {
        for (const auto &[v, w]: g[u]) {
            res[u][v] = min(res[u][v], (size_t)w);
        }
    }
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                res[i][j] = std::min(res[i][j], res[i][k] + res[k][j]);
            }
        }
    }
    return res;
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1);
    matrix<int> mx(n + 1, vector<int>(n + 1, -1));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
        mx[u][v] = max(mx[u][v], w);
        mx[v][u] = max(mx[v][u], w);
    }
    auto dist = floydWarshall(g);

    lld ans = numeric_limits<lld>::max();
    for (int k = 1; k <= n; k++) {
        lld tmp = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                tmp = max(tmp, (lld)dist[k][i] + dist[k][j] + mx[i][j]);
            }
        }
        ans = min(ans, tmp);
    }
    cout << fixed << setprecision(1) << ans / 2 << endl;

    return 0;
}
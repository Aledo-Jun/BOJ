//
// Created by june0 on 2024-03-02.
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

const int INF = 1E9;

template<typename T>
matrix<int> dijkstra(const graph<T> &g, int start) {
    int n = (int) g.size() - 1;
    std::priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, std::greater<>> pq;
    matrix<int> dist(n + 1, vector<int>(n + 1, INF));
    pq.emplace(0, start, 0);
    dist[start][0] = 0;

    while (!pq.empty()) {
        const auto [distance, u, cnt] = pq.top();
        pq.pop();

        // cnt >= n is needed to use matrix, not for int[][]
        if (cnt >= n || distance > dist[u][cnt]) continue;

        for (const auto &[v, w]: g[u]) {
            if (distance + w < dist[v][cnt + 1]) {
                dist[v][cnt + 1] = distance + w ;
                pq.emplace(dist[v][cnt + 1], v, cnt + 1);
            }
        }
    }
    return dist;
}

int32_t main() {
    fastIO;
    int n, m, k;
    cin >> n >> m >> k;
    int start, end;
    cin >> start >> end;

    graph<int> g(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    vector<int> K(k + 1, 0);
    for (int i = 1; i <= k; i++){
        cin >> K[i];
    }

    matrix<int> res = dijkstra(g, start);

    for (int i = 0; i <= k; i++){
        for (int j = 0; j <= n; j++) {
            res[end][j] += K[i] * j;
        }
        cout << *min_element(res[end].begin(), res[end].end()) << endl;
    }

    return 0;
}
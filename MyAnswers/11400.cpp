//
// Created by june0 on 2024-02-25.
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

template<typename T>
int dfs_articulation_bridges(const graph<T>& g, int u, int p, vector<int>& mark, int& cnt, set<pair<int,int>>& res) {
    mark[u] = cnt++;
    int ret = mark[u];

    for (const auto &[v, w]: g[u]) {
        if (v == p) continue;
        if (mark[v] == 0) {
            int lowest = dfs_articulation_bridges(g, v, u, mark, cnt, res);
            if (lowest > mark[u]) {
                res.emplace(min(u, v), max(u, v));
            }
            ret = min(ret, lowest);
        } else {
            ret = min(ret, mark[v]);
        }
    }

    return ret;
}

/**
 * Find articulation bridges(a.k.a. cut-edges) of the given graph.
 * @param g The graph (assumed to be 1-indexed)
 * @return std::set of the articulation bridges
 */
template<typename T>
std::set<pair<int,int>> articulation_bridges(const graph<T>& g){
    int n = (int) g.size() - 1;
    std::set<pair<int,int>> res;
    vector<int> mark(n + 1, 0);
    int cnt = 1;

    dfs_articulation_bridges(g, 1, 0, mark, cnt, res);

    return res;
}


int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }

    auto ans = articulation_bridges(g);

    cout << ans.size() << endl;
    for (const auto& e : ans) cout << e.first << ' ' << e.second << endl;

    return 0;
}
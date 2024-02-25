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

set<int> ans;

graph<int> g;
vector<int> mark;
int cnt = 1;

int dfs_articulation_points(int u, bool is_root){
    mark[u] = cnt++;
    int ret = mark[u];

    int child = 0;
    for (const auto& [v, w]: g[u]){
        if (mark[v] == 0){
            child++;
            int lowest = dfs_articulation_points(v, false);
            if (!is_root && lowest >= mark[u]){
                ans.emplace(u);
            }
            ret = min(ret, lowest);
        } else {
            ret = min(ret, mark[v]);
        }
    }

    if (is_root && child >= 2)
        ans.emplace(u);

    return ret;
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    g.resize(n + 1);
    mark.resize(n + 1, 0);
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }

    for (int i = 1; i <= n; i++){
        if (mark[i] == 0) dfs_articulation_points(i, true);
    }

    cout << ans.size() << endl;
    for (const auto& e : ans) cout << e << ' ';

    return 0;
}
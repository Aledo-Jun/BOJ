//
// Created by june0 on 2024-02-20.
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

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    graph<int> g(n + 1);
    for (int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }
    vector<bool> visited(n + 1, false), erased(n + 1, false);
    queue<int> leaves;
    for (int i = 1; i <= n; i++)
        if (g[i].size() == 1) leaves.emplace(i);

    while (!leaves.empty()){
        int u = leaves.front(); leaves.pop();
        if (erased[u]) continue;
        erased[u] = true;
        for (const auto& [p, _]: g[u]){
            if (visited[p] || erased[p]) continue;
            visited[p] = erased[p] = true;
            for (const auto& [v, __]: g[p]){
                if (erased[v]) continue;
                int cnt = 0;
                for (const auto& [w, ___]: g[v]){
                    if (!erased[w]) cnt++;
                }
                if (cnt == 1) leaves.emplace(v);
            }
        }
    }

    cout << count(visited.begin(), visited.end(), true);

    return 0;
}
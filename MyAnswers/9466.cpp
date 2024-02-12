//
// Created by june0 on 2024-02-12.
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

vector<int> g, memo;

void dfs(int u, int start) {
    int v = g[u];
    if (memo[v] == start) {
        while (memo[v] != -1){
            memo[v] = -1;
            v = g[v];
        }
        return;
    } else if (memo[v] != 0) {
        return;
    }
    memo[v] = start;

    dfs(v, start);
}

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        g = vector<int>(n + 1);
        memo = vector<int>(n + 1, 0);

        for (int u = 1; u <= n; u++){
            cin >> g[u];
        }

        for (int i = 1; i <= n; i++){
            if (memo[i] == 0) dfs(i, i);
        }

        int ans = 0;
        for (const auto& e : memo) if (e != -1) ans++;
        cout << ans - 1 << endl;
    }

    return 0;
}
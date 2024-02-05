//
// Created by june0 on 2024-02-05.
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

constexpr int INF = 1 << 18;

double dfs_for_tsp(const matrix<double>& g, matrix<double>& dp, int node, int visited) {
    if (visited == (1 << g.size()) - 1) {
        return g[node][0] == 0 ? INF : g[node][0];
    }

    if (dp[node][visited] != -1) return dp[node][visited];

    dp[node][visited] = INF;

    for (int i = 1; i < g.size(); i++){
        if (g[node][i] == 0) continue;
        if (visited & (1 << i)) continue;

        dp[node][visited] = min(dp[node][visited], g[node][i] + dfs_for_tsp(g, dp, i, visited | (1 << i)));
    }
    return dp[node][visited];
}

double tsp(const matrix<double>& g){
    int n = (int) g.size();
    matrix<double> dp(n, vector<double>(1 << n, -1));

    return dfs_for_tsp(g, dp, 0, 1);
}

double dist(const pair<int,int>& a, const pair<int,int>& b){
    return sqrt((a.first - b.first) * (a.first - b.first)
                + (a.second - b.second) * (a.second - b.second));
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (auto& e : v) cin >> e.first >> e.second;
    matrix<double> g(n, vector<double>(n));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            g[i][j] = dist(v[i], v[j]);
        }
    }

    cout << fixed << setprecision(12);
    cout << tsp(g);

    return 0;
}
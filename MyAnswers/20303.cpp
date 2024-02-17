//
// Created by june0 on 2024-02-17.
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

int n, m, k;
graph<int> g;
vector<int> candies;
vector<bool> visited;

void init() {
    cin >> n >> m >> k;
    g.resize(n + 1);
    candies.resize(n);
    visited.resize(n + 1, false);
    for (auto& e : candies) cin >> e;
    for (int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 1);
    }
}

vector<pair<int,int>> clusters;
void bfs(int start){
    queue<int> q;
    q.emplace(start);
    visited[start] = true;
    int cnt = 1, sum = 0;
    sum += candies[start - 1];
    while (!q.empty()){
        int u = q.front(); q.pop();
        for (const auto& [v, w] : g[u]){
            if (!visited[v]){
                visited[v] = true;
                q.emplace(v);
                sum += candies[v - 1];
                cnt++;
            }
        }
    }
    if (cnt >= k) return;
    clusters.emplace_back(cnt, sum);
}

int32_t main() {
    fastIO;
    init();
    for (int i = 1; i <= n; i++){
        if (!visited[i])
            bfs(i);
    }

    vector<int> dp(k, 0);
    for (const auto& [cnt, sum]: clusters){
        for (int i = k - 1; i >= cnt; i--)
            dp[i] = max(dp[i], dp[i - cnt] + sum);
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
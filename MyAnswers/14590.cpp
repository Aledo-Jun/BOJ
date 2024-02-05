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

// Implementation of the max-TSP, I think.
void path_tsp(const matrix<int>& g, const matrix<int>& dp, vector<int>& path, int node, int visited) {
    path.emplace_back(node);

    if (visited == (1 << g.size()) - 1) return;

    pair<int, int> next(-1, -1);
    for (int i = 1; i < g.size(); i++) {
        if (g[node][i] == 0) continue;
        if (visited & (1 << i)) continue;

        if (g[node][i] + dp[i][visited | (1 << i)] > next.first) {
            next.first = g[node][i] + dp[i][visited | (1 << i)];
            next.second = i;
        }
    }
    if (next.second == -1) return;

    path_tsp(g, dp, path, next.second, visited | (1 << next.second));
}

int dfs_for_tsp(const matrix<int>& g, matrix<int>& dp, int node, int visited) {
    if (visited == (1 << g.size()) - 1) return 0;

    if (dp[node][visited] != -1) return dp[node][visited];

    for (int i = 0; i < g.size(); i++){
        if (g[node][i] == 0) continue;
        if (visited & (1 << i)) continue;

        dp[node][visited] = max(dp[node][visited],
                                g[node][i] + dfs_for_tsp(g, dp, i, visited | (1 << i)));
    }
    return dp[node][visited] == -1 ? 0 : dp[node][visited];
}

auto tsp(const matrix<int>& g){
    int n = (int) g.size();
    matrix<int> dp(n, vector<int>(1 << n, -1));
    vector<int> path;

    dfs_for_tsp(g, dp, 0, 1);

    path_tsp(g, dp, path, 0, 1);

    return path;
}


int32_t main() {
    fastIO;
    int n;
    cin >> n;
    matrix<int> g(n, vector<int>(n));
    for (auto& r : g){
        for (auto& e : r) cin >> e;
    }

    auto path = tsp(g);

    cout << path.size() << endl;
    for (const auto& e : path)
        cout << e + 1 << ' ';

    return 0;
}

#ifdef ANOTHER_SOLUTION

// Actually, this one is significantly faster than the above one.

void dfs(const matrix<int>& g, vector<int>& path, int curr, vector<bool>& visited) {
    visited[curr] = true;

    for (int i = 1; i < g.size(); i++){
        if (visited[i]) continue;
        if (g[curr][i] == 0) continue;

        dfs(g, path, i, visited);
    }
    path.emplace_back(curr);
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    matrix<int> g(n, vector<int>(n));
    for (auto& r : g)
        for (auto& e : r) cin >> e;

    vector<bool> visited(n, false);
    vector<int> path;
    dfs(g, path, 0, visited);

    cout << path.size() << endl;
    reverse(path.begin(), path.end());
    for (const auto& e : path)
        cout << e + 1 << ' ';

    return 0;
}

#endif
//
// Created by june0 on 2024-02-15.
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

const int INF = 1e9;

int cost[5][5] =
        {
                {0, 2, 2, 2, 2},
                {2, 1, 3, 4, 3},
                {2, 3, 1, 3, 4},
                {2, 4, 3, 1, 3},
                {2, 3, 4, 3, 1}
        };

int32_t main() {
    fastIO;
    vector<int> v;
    while (true){
        int x; cin >> x;
        if (x == 0) break;
        v.emplace_back(x);
    }
    int n = (int) v.size();

    vector<matrix<int>> dp(n + 1, matrix<int>(5, vector<int>(5, INF)));
    dp[0][0][0] = 0;
    for (int i = 0; i < n; i++){
        for (int l = 0; l <= 4; l++) {
            for (int r = 0; r <= 4; r++) {
                dp[i + 1][v[i]][r] = min(dp[i + 1][v[i]][r], dp[i][l][r] + cost[l][v[i]]);
                dp[i + 1][l][v[i]] = min(dp[i + 1][l][v[i]], dp[i][l][r] + cost[r][v[i]]);
            }
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            ans = min(ans, dp[n][i][j]);
    cout << ans;
    return 0;
}
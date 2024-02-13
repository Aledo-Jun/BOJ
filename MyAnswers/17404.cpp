//
// Created by june0 on 2024-02-13.
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
enum RGB {R, G, B};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    matrix<int> v(n, vector<int>(3));
    for (auto& r : v)
        for (auto& c : r) cin >> c;

    int ans = INT_MAX;
    matrix<int> dp(n + 1, vector<int>(3, INT_MAX >> 1));

    dp[0][R] = v[0][R];
    for (int i = 1; i < n; i++){
        dp[i][R] = min(dp[i - 1][G], dp[i - 1][B]) + v[i][R];
        dp[i][G] = min(dp[i - 1][R], dp[i - 1][B]) + v[i][G];
        dp[i][B] = min(dp[i - 1][R], dp[i - 1][G]) + v[i][B];
    }
    ans = min({ans, dp[n - 1][G], dp[n - 1][B]});

    dp[0][G] = v[0][G];
    dp[0][R] = dp[0][B] = INT_MAX >> 1;
    for (int i = 1; i < n; i++){
        dp[i][R] = min(dp[i - 1][G], dp[i - 1][B]) + v[i][R];
        dp[i][G] = min(dp[i - 1][R], dp[i - 1][B]) + v[i][G];
        dp[i][B] = min(dp[i - 1][R], dp[i - 1][G]) + v[i][B];
    }
    ans = min({ans, dp[n - 1][R], dp[n - 1][B]});

    dp[0][B] = v[0][B];
    dp[0][R] = dp[0][G] = INT_MAX >> 1;
    for (int i = 1; i < n; i++){
        dp[i][R] = min(dp[i - 1][G], dp[i - 1][B]) + v[i][R];
        dp[i][G] = min(dp[i - 1][R], dp[i - 1][B]) + v[i][G];
        dp[i][B] = min(dp[i - 1][R], dp[i - 1][G]) + v[i][B];
    }
    ans = min({ans, dp[n - 1][R], dp[n - 1][G]});

    cout << ans;
    return 0;
}
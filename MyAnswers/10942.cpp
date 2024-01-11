//
// Created by june0 on 2024-01-11.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

#define int ll

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v)
        cin >> e;

    matrix<bool> dp(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) dp[i][i] = true;
    for (int i = 0; i < n - 1; i++)
        if (v[i] == v[i + 1]) dp[i][i + 1] = true;

    for (int i = n - 1; i >= 0; i--){
        for (int j = i + 2; j < n; j++){
            if (v[i] == v[j] && dp[i + 1][j - 1])
                dp[i][j] = true;
        }
    }

    int m;
    cin >> m;
    while (m--){
        int a, b;
        cin >> a >> b;
        cout << dp[a - 1][b - 1] << '\n';
    }

    return 0;
}
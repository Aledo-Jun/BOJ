//
// Created by june0 on 2024-03-06.
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

int32_t main() {
    fastIO;
    int n, w;
    cin >> w >> n;
    vector<int> v(n);
    for (auto &e: v) cin >> e;
    sort(v.begin(), v.end());

    vector<int> dp(800'000, 0);
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int tmp = v[i] + v[j];
            if (w - tmp < 0) continue;
            if (dp[w - tmp] && dp[w - tmp] < i) return cout << "YES", 0;
            dp[tmp] = (dp[tmp] ? min(dp[tmp], j) : j);
        }
    }

    cout << "NO";
    return 0;
}
//
// Created by june0 on 2024-03-05.
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
    int n, d;
    cin >> n >> d;
    vector<int> v(n);
    for (auto& e : v) cin >> e;

    vector<ll> dp(n);
    deque<pair<int,ll>> q;
    for (int i = 0; i < n; i++){
        dp[i] = v[i];
        if (!q.empty() && q.front().first < i - d) q.pop_front();
        if (!q.empty())
            dp[i] = max(dp[i], q.front().second + v[i]);
        while (!q.empty() && q.back().second < dp[i]) q.pop_back();
        q.emplace_back(i, dp[i]);
    }

    cout << *max_element(dp.begin(), dp.end());

    return 0;
}
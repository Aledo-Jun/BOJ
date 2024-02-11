//
// Created by june0 on 2024-02-11.
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
    int n, m, total_cost = 0;
    cin >> n >> m;
    vector<pair<int,int>> v(n); // <cost, memory>
    for (auto& p : v) cin >> p.second;
    for (auto& p : v) cin >> p.first, total_cost += p.first;

    vector<int> dp(total_cost + 1, 0);
    for (const auto& [cost, mem] : v){
        for (int i = total_cost; i >= cost; i--){
            dp[i] = max(dp[i], dp[i - cost] + mem);
        }
    }

    for (int i = 0; i <= total_cost; i++)
        if (dp[i] >= m) return cout << i, 0;

    return 0;
}
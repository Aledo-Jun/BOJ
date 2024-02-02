//
// Created by june0 on 2024-02-02.
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
    int n, dummy;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (auto& e : v)
        cin >> dummy >> e.first >> e.second;
    sort(v.begin(), v.end(), [&](const auto& a, const auto& b){
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<int> dp;
    for (const auto& [x, y] : v) {
        auto it = upper_bound(dp.begin(), dp.end(), y, greater<>());
        if (it == dp.end()) dp.emplace_back(y);
        else *it = y;
    }
    cout << dp.size();
    return 0;
}

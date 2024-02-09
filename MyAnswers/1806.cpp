//
// Created by june0 on 2024-02-09.
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
    int n, x;
    cin >> n >> x;
    vector<int> v(n);
    for (auto& e : v) cin >> e;

    vector<int> sum(n + 1, 0);
    for (int i = 0; i < n; i++) sum[i + 1] = sum[i] + v[i];

    if (sum.back() < x) return cout << 0, 0;

    int ans = INT_MAX;
    for (int i = 0; i < n; i++){
        auto it = lower_bound(sum.begin() + i, sum.end(), x + sum[i]);
        if (it != sum.end())
            ans = min(ans, (int)(it - sum.begin() - i));
    }

    cout << ans;

    return 0;
}
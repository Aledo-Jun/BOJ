//
// Created by june0 on 2024-01-26.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

int32_t main() {
    fastIO;
    int d, a, b;
    cin >> d >> a >> b;
    if (a < b) swap(a, b);

    ll aa = d / a + (d % a ? 1 : 0);
    ll ans = aa * a;
    if (aa > b) aa = b;

    for (; aa >= 0; aa--) {
        if (d - aa * a <= 0) continue;
        ll bb = (d - aa * a) / b + ((d - aa * a) % b ? 1 : 0);
        ans = min(ans, aa * a + bb * b);
    }

    cout << ans;

    return 0;
}
//
// Created by june0 on 2024-02-03.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;

ll n, k;

ll cnt(ll x) {
    ll res = 0;
    for (int i = 1; i <= min(x, n); i++){
        res += min(x / i, n);
    }
    return res;
}

int32_t main() {
    fastIO;
    cin >> n >> k;

    ll l = 1, r = n * n, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (cnt(mid) < k) l = mid + 1;
        else r = mid - 1;
    }
    cout << l;
    return 0;
}

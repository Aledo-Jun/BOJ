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

#define int ll // IDK where the fxxk integer overflow occurred

struct elem {
    ll a, mx, d;
};

int n;
vector<elem> v;

// returns the number of elements that is less than or equal to k.
ull count_num(ll k) {
    ull cnt = 0;
    for (const auto& [a, mx, d] : v) {
        if (k < a) continue;
        cnt += (min(mx, k) - a) / d + 1;
    }
    return cnt;
}

int32_t main() {
    fastIO;
    cin >> n;
    v.resize(n);
    for (auto& e : v) {
        cin >> e.a >> e.mx >> e.d;
    }

    int target = -1;
    int l = 1, r = INT_MAX, mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (count_num(mid) & 1) target = mid, r = mid - 1;
        else l = mid + 1;
    }

    if (target == -1) cout << "NOTHING";
    else {
        cout << target << ' ' << count_num(target) - count_num(target - 1) << ' ';
    }

    return 0;
}

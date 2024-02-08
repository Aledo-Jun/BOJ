//
// Created by june0 on 2024-02-08.
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
    int n, s;
    cin >> n >> s;
    vector<int> v(n);
    for (auto& e : v) cin >> e;

    vector<int> a, b;
    for (int i = 0; i < n; i++){
        if (i & 1) {
            int sz = (int) a.size();
            for (int j = 0; j < sz; j++) a.emplace_back(a[j] + v[i]);
            a.emplace_back(v[i]);
        } else {
            int sz = (int) b.size();
            for (int j = 0; j < sz; j++) b.emplace_back(b[j] + v[i]);
            b.emplace_back(v[i]);
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    ll cnt = 0;
    for (const auto& e : a){
        auto it1 = lower_bound(b.begin(), b.end(), s - e);
        auto it2 = upper_bound(b.begin(), b.end(), s - e);
        cnt += (it2 - it1);
    }
    auto it1 = lower_bound(a.begin(), a.end(), s);
    auto it2 = upper_bound(a.begin(), a.end(), s);
    cnt += (it2 - it1);

    it1 = lower_bound(b.begin(), b.end(), s);
    it2 = upper_bound(b.begin(), b.end(), s);
    cnt += (it2 - it1);

    cout << cnt;

    return 0;
}
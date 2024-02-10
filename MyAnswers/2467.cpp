//
// Created by june0 on 2024-02-10.
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
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v) cin >> e;

    int mn = INT_MAX;
    int a, b;
    for (int i = 0; i < n - 1; i++){
        auto it = lower_bound(v.begin() + i + 1, v.end(), -v[i]);
        if (it == v.end()) it--;
        if (abs(*it + v[i]) < mn){
            mn = abs(*it + v[i]);
            a = v[i];
            b = *it;
        }
        if (prev(it) != v.begin() + i) {
            it--;
            if (abs(*it + v[i]) < mn) {
                mn = abs(*it + v[i]);
                a = v[i];
                b = *it;
            }
        }
    }
    cout << a << " " << b;
    return 0;
}
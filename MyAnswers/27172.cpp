//
// Created by june0 on 2024-02-16.
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

const int MAX = 1'000'000;

int32_t main() {
    fastIO;
    int n, mx = -1;
    cin >> n;
    vector<int> v(n), w(MAX + 1, 0);
    for (auto& e : v) {
        cin >> e;
        w[e] = 1;
    }

    vector<int> ans(MAX + 1, 0);
    for (const auto& e : v){
        for (int i = 2; e * i <= MAX; i++){
            if (w[e * i]){
                ans[e]++;
                ans[e * i]--;
            }
        }
    }

    for (const auto& e : v)
        cout << ans[e] << ' ';

    return 0;
}
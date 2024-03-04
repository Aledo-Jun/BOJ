//
// Created by june0 on 2024-03-04.
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
    int n;
    cin >> n;
    vector<pair<int,int>> v(n);
    for (auto& e : v) {
        cin >> e.first >> e.second;
        if (e.first > e.second) swap(e.first, e.second);
    }
    int d;
    cin >> d;
    vector<int> a, b;
    for (const auto& e : v){
        if (e.second - e.first <= d){
            a.emplace_back(e.first);
            b.emplace_back(e.second);
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int ans = 0, curr = -1;
    for (int i = 0; i < a.size(); i++){
        if (a[i] == curr) continue;
        curr = a[i];
        auto it1 = lower_bound(a.begin(), a.end(), curr);
        auto it2 = upper_bound(b.begin(), b.end(), curr + d);
        int tmp = distance(it1, a.end()) + distance(b.begin(), it2) - a.size();
        ans = max(ans, tmp);
    }
    cout << ans;

    return 0;
}
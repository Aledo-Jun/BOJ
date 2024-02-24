//
// Created by june0 on 2024-02-24.
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

    ll ans = 0;
    stack<pair<ll,ll>> s;
    while (n--){
        int x; cin >> x;
        while (!s.empty() && s.top().first < x){
            ans += s.top().second;
            s.pop();
        }

        if (s.empty()) s.emplace(x, 1);
        else if (x < s.top().first){
            ans++;
            s.emplace(x, 1);
        }
        else if (x == s.top().first){
            ll tmp = s.top().second;
            s.pop();
            if (s.empty()) ans += tmp;
            else ans += tmp + 1;

            s.emplace(x, tmp + 1);
        }
    }
    cout << ans;

    return 0;
}
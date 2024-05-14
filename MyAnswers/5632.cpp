//
// Created by june0 on 2024-05-14.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    int d = 0;
    crope v[50'001];
    int ver = 0;
    while (t--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int p;
            string str;
            cin >> p >> str;
            p -= d;
            v[ver + 1] = v[ver];
            v[++ver].insert(p, str.data());
        } else if (cmd == 2) {
            int p, c;
            cin >> p >> c;
            p -= d, c -= d;
            v[ver + 1] = v[ver];
            v[++ver].erase(p - 1, c);
        } else {
            int id, p, c;
            cin >> id >> p >> c;
            id -= d, p -= d, c -= d;
            auto rp = v[id].substr(p - 1, c);
            d += std::count(rp.begin(), rp.end(), 'c');
            for (const auto& e : rp) cout << e;
            cout << endl;
        }
    }

    return 0;
}
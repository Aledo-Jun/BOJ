//
// Created by june0 on 2024-02-23.
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

int dist(const pair<int,int>& a, const pair<int,int>& b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> v(m + 1);
    for (int i = 1; i <= m; i++) cin >> v[i].first >> v[i].second;

    matrix<int> dp(m + 1, vector<int>(m + 1, 0));
    for (int i = m - 1; i >= 0; i--){
        for (int j = m - 1; j >= 0; j--){
            int k = max(i, j) + 1; // next idx
            dp[i][j] = min(dp[i][k] + dist(v[k], j == 0 ? make_pair(n,n) : v[j]),
                           dp[k][j] + dist(v[k], i == 0 ? make_pair(1,1) : v[i]));
        }
    }

    cout << dp[0][0] << endl;

    int i = 0, j = 0;
    for (int k = 1; k <= m; k++){
        if (dp[i][k] + dist(v[k], j == 0 ? make_pair(n,n) : v[j]) < dp[k][j] + dist(v[k], i == 0 ? make_pair(1,1) : v[i])){
            cout << 2 << endl;
            j = k;
        } else {
            cout << 1 << endl;
            i = k;
        }
    }

    return 0;
}
//
// Created by june0 on 2024-02-18.
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

enum {SS, SL, LS, LL, VV};
const int INF = 1E5;

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--){
        int n, k;
        cin >> n >> k;
        matrix<int> v(2, vector<int>(n));
        for (auto& e : v[0]) cin >> e;
        for (auto& e : v[1]) cin >> e;

        int ans = INT_MAX;
        for (int start = 0; start < 5; start++) {
            int dp[10000][5];
            dp[0][SS] = 2;
            if (v[0][0] + v[1][0] <= k)
                dp[0][VV] = 1;
            else dp[0][VV] = INF;
            if (v[0][0] + v[0][n - 1] <= k) {
                if (v[1][0] + v[1][n - 1] <= k) {
                    dp[0][LL] = 2;
                    dp[0][LS] = 2;
                    dp[0][SL] = 2;
                } else {
                    dp[0][LL] = INF;
                    dp[0][LS] = 2;
                    dp[0][SL] = INF;
                }
            } else {
                dp[0][LL] = INF;
                dp[0][LS] = INF;
                if (v[1][0] + v[1][n - 1] <= k) {
                    dp[0][SL] = 2;
                } else dp[0][SL] = INF;
            }
            for (int i = 0; i < 5; i++){
                if (i != start) {
                    dp[0][i] = INF;
                }
            }
            for (int i = 1; i < n; i++) {
                dp[i][SS] = *min_element(&dp[i - 1][0], &dp[i - 1][5]) + 2;
                if (v[0][i] + v[1][i] <= k)
                    dp[i][VV] = *min_element(&dp[i - 1][0], &dp[i - 1][5]) + 1;
                else
                    dp[i][VV] = INF;
                if (v[1][i - 1] + v[1][i] <= k)
                    dp[i][SL] = min(dp[i - 1][SS], dp[i - 1][LS]) + 1;
                else
                    dp[i][SL] = INF;
                if (v[0][i - 1] + v[0][i] <= k)
                    dp[i][LS] = min(dp[i - 1][SS], dp[i - 1][SL]) + 1;
                else
                    dp[i][LS] = INF;
                if (v[1][i - 1] + v[1][i] <= k && v[0][i - 1] + v[0][i] <= k)
                    dp[i][LL] = dp[i - 1][SS];
                else
                    dp[i][LL] = INF;
            }
            if (start == LL) {
                dp[n - 1][LL] = dp[n - 1][LS] = dp[n - 1][SL] = dp[n - 1][VV] = INF;
                dp[n - 1][SS] -= 2;
            } else if (start == LS) {
                dp[n - 1][LL] = dp[n - 1][LS] = dp[n - 1][VV] = INF;
                dp[n - 1][SS] -= 1;
                dp[n - 1][SL] -= 1;
            } else if (start == SL) {
                dp[n - 1][LL] = dp[n - 1][SL] = dp[n - 1][VV] = INF;
                dp[n - 1][SS] -= 1;
                dp[n - 1][LS] -= 1;
            }
            ans = min(ans, *min_element(&dp[n - 1][0], &dp[n - 1][5]));
        }
        cout << ans << endl;
    }

    return 0;
}
//
// Created by june0 on 2024-02-21.
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

int n, k;
vector<string> nums;
matrix<ll> dp;
vector<int> powOf10, cache;

int operator% (const string& s, int m){
    int ret = 0;
    for (const auto& c : s){
        ret *= 10;
        ret += c - '0';
        ret %= m;
    }
    return ret;
}

void init(){
    cin >> n;
    nums.resize(n);
    for (auto& s : nums) cin >> s;
    cin >> k;
    dp.resize(1 << n, vector<ll>(k, 0));
    dp[0][0] = 1;
    powOf10.emplace_back(1);
    for (int i = 1; i <= 51; i++){
        powOf10.emplace_back((powOf10.back() * 10) % k);
    }
    for (const auto& s : nums) cache.emplace_back(s % k);
}

void solve(){
    for (int bit = 0; bit < (1 << n); bit++){
        for (int i = 0; i < n; i++){
            if (bit & (1 << i)) continue;
            int next_bit = bit | (1 << i);
            for (int j = 0; j < k; j++){
                int next_remainder = ((j * powOf10[nums[i].length()]) % k + cache[i]) % k;
                dp[next_bit][next_remainder] += dp[bit][j];
            }
        }
    }
}

int32_t main() {
    fastIO;
    init();

    solve();

    ll numerator = dp[(1 << n) - 1][0];
    ll denominator = 1;
    for (int i = 2; i <= n; i++) denominator *= i;

    auto GCD = gcd(numerator, denominator);

    cout << numerator / GCD << '/' << denominator / GCD;

    return 0;
}
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

string s;
matrix<int> is_pal;
vector<int> dp;

bool is_palindrome(int l, int r){
    if (is_pal[l][r] != -1) return is_pal[l][r];
    if (l == r) return is_pal[l][r] = true;

    if (s[l] != s[r]) return is_pal[l][r] = false;
    if (l + 1 == r) return is_pal[l][r] = true;
    return is_pal[l][r] = is_palindrome(l + 1, r - 1);
}

int solve(int start){
    if (start == s.size()) return 0;

    if (dp[start] != -1) return dp[start];

    dp[start] = INT_MAX;
    for (int i = start; i < s.size(); i++){
        if (is_palindrome(start, i))
            dp[start] = min(dp[start], 1 + solve(i + 1));
    }
    return dp[start];
}

int32_t main() {
    fastIO;
    cin >> s;
    is_pal.resize(s.size(), vector<int>(s.size(), -1));
    dp.resize(s.size(), -1);

    cout << solve(0);

    return 0;
}
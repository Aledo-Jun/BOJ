//
// Created by june0 on 2024-09-20.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
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

// Count the number of positive integers less than or equal to n
// that are coprime with n, using Euler's totient function.
int phi_naive(int n) {
    int res = n;

    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;

            res -= res / p;
        }
    }

    if (n > 1)
        res -= res / n;

    return res;
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;

    if (n == 1 || n == 2) return cout << n, 0;
    if (n & 1) return cout << -1, 0;

    vector<int> factors;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            factors.emplace_back(i);
            factors.emplace_back(n / i);
        }
    }

    for (const auto &x : factors) {
        if (x * phi_naive(x) == n) return cout << x, 0;
    }
    cout << -1;

    return 0;
}

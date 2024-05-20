//
// Created by june0 on 2024-05-20.
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

template<typename T>
T pow_mod(T a, ull pow, ull MOD) {
    lll base = a;
    lll res = 1;
    while (pow > 0) {
        if (pow & 1) {
            res = lll(res * base) % MOD;
        }
        base = lll(base * base) % MOD;
        pow >>= 1;
    }
    return res;
}

bool miller_rabin(ull n, ull a) {
    for (ull d = n - 1; ; d >>= 1) {
        ull t = pow_mod(a, d, n);
        if (t == n - 1) return true;
        if (d & 1) return t == 1 || t == n - 1;
    }
    // cannot reach here
}

bool is_prime(ull n) {
    if (n < 2) return false;
    static ull a[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // works for n <= 2^64
    for (ull p : a) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    for (ull p : a) {
        if (!miller_rabin(n, p)) return false;
    }
    return true;
}

ull pollard_rho(lll n) {
    if (~n & 1) return 2;
    if (is_prime(n)) return n;

    static mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<ull> rand(2, n - 1);
    lll x = rand(rng), y = x, c = rand(rng) % 10 + 1;
    lll d = 1;
    auto f = [&](lll x) { return ((x * x) % n + c) % n; };
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(abs(x - y), n);
        if (d == n) return pollard_rho(d); // resolve possible infinite loop
    }
    if (is_prime(d)) return d;
    return pollard_rho(d);
}

// Count the number of positive integers less than or equal to n
// that are coprime with n, using Euler's totient function.
ull phi(ull n) {
    if (n == 1) return 1;
    ull res = n;
    while (n > 1 && !is_prime(n)) {
        ull factor = pollard_rho(n);
        while (n % factor == 0) n /= factor;
        res -= res / factor;
    }
    if (n > 1) res -= res / n;

    return res;
}

int32_t main() {
    fastIO;
    ull n;
    cin >> n;
    cout << phi(n) << endl;

    return 0;
}
//
// Created by june0 on 2024-01-11.
// Naive approach that uses the 1E13 digit representation of the big integer
// to calculate the large factorial
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

#define int ll
const int d = 1E13;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> f(n + 1);
    f[0] = 1;

    int nn = 0;
    for (int i = 1; i <= n; i++){
        int k = 0;
        for (int j = 0; j <= nn; j++){
            f[j] *= i;
            f[j] += k;
            k = f[j] / d;
            f[j] %= d;
        }
        if (k != 0){
            f[nn + 1] = k;
            nn++;
        }
    }

    cout << f[nn];
    for (int i = nn - 1; i >= 0; i--){
        cout << setw(13) << setfill('0');
        cout << f[i];
    }

    return 0;
}
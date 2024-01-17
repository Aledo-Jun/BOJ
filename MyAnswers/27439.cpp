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

#ifdef BOJ_FFT_HPP
/// solution using NTT
using namespace NTT;

vector<int> multiply(const vector<int> &a, const vector<int> &b){
    auto res = convolution(a, b);
    for (int i = 0; i < res.size(); i++){
        if (res[i] > 9) {
            if (i + 1 == res.size()) res.emplace_back(0);
            res[i + 1] += res[i] / 10;
            res[i] %= 10;
        }
    }
    return res;
}

vector<int> iToVec(int n){
    vector<int> res;
    while (n > 0){
        res.emplace_back(n % 10);
        n /= 10;
    }
    return res;
}

vector<int> solve(int l, int r){
    if (l > r) return iToVec(1);
    if (l == r) return iToVec(l);
    int mid = (l + r) >> 1;
    return multiply(solve(l, mid), solve(mid + 1, r));
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    auto res = solve(1, n);
    for (int i = res.size() - 1; i >= 0; i--)
        cout << res[i];

    return 0;
}
#endif
//
// Created by june0 on 2024-01-27.
// The method of solving Cubic Equations that is guaranteed to have at least one integer root.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

#define double lld
const int MAX = 1'000'000;

int32_t main() {
    fastIO;
    int tc;
    cin >> tc;
    cout << fixed << setprecision(4);
    while (tc--) {
        double a, b, c, d;
        cin >> a >> b >> c >> d;

        double p, q, r; // roots
        if (d == 0) p = 0;
        else {
            for (int i = -MAX; i <= MAX; i++){ // find the first integer root p
                if (a * i * i * i + b * i * i + c * i + d == 0){
                    p = i;
                    break;
                }
            }
        }

        // Synthetic division
        b = b + a * p;
        c = c + b * p;

        // Now solve the quadratic equation with coefficients of a, b, c
        d = b * b - 4 * a * c;
        if (d < 0) {
            cout << p << endl;
        } else {
            q = (-b + sqrt(d)) / (2 * a);
            r = (-b - sqrt(d)) / (2 * a);
            set<double> ans;
            ans.insert({p, q, r});
            for (const auto& e : ans)
                cout << e << ' ';
            cout << endl;
        }
    }

    return 0;
}
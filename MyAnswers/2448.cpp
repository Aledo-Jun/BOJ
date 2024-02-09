//
// Created by june0 on 2024-02-09.
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


matrix<char> a;

void stars(int n, int x, int y){
    if (n == 3) {
        /*
         *     *
         *    * *
         *   *****
         */
        a[x][y] = '*';
        a[x + 1][y - 1] = a[x + 1][y + 1] = '*';
        for (int i = y - 2; i <= y + 2; i++)
            a[x + 2][i] = '*';
        return;
    }

    stars(n / 2, x, y);
    stars(n / 2, x + n / 2, y - n / 2);
    stars(n / 2, x + n / 2, y + n / 2);
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;

    a.resize(n, vector<char>(2 * n - 1, ' '));

    stars(n, 0, n - 1); //start from middle of the first row

    for (const auto& row : a) {
        for (const auto &col: row)
            cout << col;
        cout << endl;
    }
    return 0;
}
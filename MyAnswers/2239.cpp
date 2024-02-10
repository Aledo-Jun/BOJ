//
// Created by june0 on 2024-02-10.
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

vector<vector<int>> table(9, vector<int>(9));
vector<bitset<10>> row_check(9, bitset<10>().set()),
        col_check(9, bitset<10>().set()),
        squ_check(9, bitset<10>().set());

inline int square_idx(int x, int y){
    return (x / 3) * 3 + (y / 3);
}

bool solve(int n){
    if (n == 81) return true;

    int x = n / 9;
    int y = n % 9;

    if (table[x][y] != 0) return solve(n + 1); // already filled

    for (int i = 1; i <= 9; i++){
        // i is possible for table[x][y]
        if (row_check[x][i] && col_check[y][i] && squ_check[square_idx(x, y)][i]){
            row_check[x][i] = col_check[y][i] = squ_check[square_idx(x, y)][i] = false;
            table[x][y] = i;

            // try to finish the sudoku
            if (solve(n + 1)) return true;

            // impossible to finish -> back-track
            table[x][y] = 0;
            row_check[x][i] = col_check[y][i] = squ_check[square_idx(x, y)][i] = true;
        }
    }
    return false;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c; cin >> c;
            table[i][j] = c - '0';
            if (table[i][j] == 0) continue;
            row_check[i][table[i][j]] = false;
            col_check[j][table[i][j]] = false;
            squ_check[square_idx(i, j)][table[i][j]] = false;
        }
    }

    solve(0);
    for (const auto& row : table) {
        for (const auto &e: row) cout << e;
        cout << endl;
    }

    return 0;
}
//
// Created by june0 on 2024-02-19.
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

int n, m;
char board[11][10];
char dp[11][10][1 << 11];
const int dc[6] = { -1,-1,-1,1,1,1 };
const int dr[6] = { -1,0,1,-1,0,1 };

bool is_valid(int pos){ // pos is available and there's no adjacent marking
    int r = pos / m, c = pos % m;
    if (board[r][c] != '.') return false;
    for (int i = 0; i < 6; i++){
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr > n || nc < 0 || nc >= m) continue;
        if (board[nr][nc] == 'm') return false;
    }
    return true;
}
char solve(int pos, int bit){
    int r = pos / m, c = pos % m;
    if (r > n) return 0;

    char& ret = dp[r][c][bit];
    if (ret != -1) return ret;

    int next_pos = pos + 1;
    int nr = next_pos / m, nc = next_pos % m;

    bit = 0;
    for (int i = max(0, nc - 1); i < m; i++){
        bit <<= 1;
        if (board[nr - 1][i] == 'm') bit++;
    }
    for (int i = 0; i < nc; i++){
        bit <<= 1;
        if (board[nr][i] == 'm') bit++;
    }

    ret = solve(next_pos, bit);
    if (is_valid(pos)) {
        board[r][c] = 'm';
        ret = max(ret, (char)(1 + solve(next_pos, bit + 1)));
        board[r][c] = '.';
    }
    return ret;
}

int32_t main() {
    fastIO;
    memset(board, 'x', sizeof board);
    int t;
    cin >> t;
    while (t--){
        cin >> n >> m;
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < m; j++)
                cin >> board[i][j];
        memset(dp, -1, sizeof dp);

        cout << (int)solve(m, 0) << endl;
    }

    return 0;
}
//
// Created by june0 on 2024-02-14.
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

int n;
matrix<int> board;

void init(){
    cin >> n;
    board.resize(n, vector<int>(n));
    for (auto& r : board)
        for (auto& c : r) cin >> c;
}

enum color {B, W};

int ans[] = {0, 0};
void solve(int x, int y, int cnt, int c){
    ans[c] = max(ans[c], cnt);

    if (x >= n) return;

    int next = x * n + y + 1;
    while ((next / n + next % n) % 2 != c) next++;
    int nx = next / n, ny = next % n;

    if (board[x][y] >= 1) {
        for (int i = 0; i < n; i++){
            int diff = x - i;
            if (0 <= y + diff && y + diff < n)
                board[i][y + diff] -= 1;
            if (0 <= y - diff && y - diff < n)
                board[i][y - diff] -= 1;
        }
        board[x][y] += 1;

        solve(nx, ny, cnt + 1, c);

        for (int i = 0; i < n; i++){
            int diff = x - i;
            if (0 <= y + diff && y + diff < n)
                board[i][y + diff] += 1;
            if (0 <= y - diff && y - diff < n)
                board[i][y - diff] += 1;
        }
        board[x][y] -= 1;
    }

    solve(nx, ny, cnt, c);
}

int32_t main() {
    fastIO;
    init();
    solve(0, 0, 0, B);
    solve(0, 1, 0, W);

    cout << ans[B] + ans[W] << endl;

    return 0;
}
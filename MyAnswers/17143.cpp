//
// Created by june0 on 2024-02-12.
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
int dx[] = {-1, 1, 0 ,0};
int dy[] = {0, 0, 1, -1};

int r, c, m;
matrix<int> grid, temp;

struct Shark {
    int x, y, spd, dir, sz;
    int idx;
    bool caught = false;

    Shark(int x, int y, int spd, int dir, int sz, int idx) : x(x), y(y), spd(spd), dir(dir - 1), sz(sz), idx(idx) {}

    void move();
};
vector<Shark> sharks;

void Shark::move(){
    int tmp = spd;
    while (tmp--){
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        if (nx < 0 || nx >= r || ny < 0 || ny >= c){
            if (dir == 0) dir = 1;
            else if (dir == 1) dir = 0;
            else if (dir == 2) dir = 3;
            else if (dir == 3) dir = 2;
            nx = x + dx[dir];
            ny = y + dy[dir];
        }
        x = nx;
        y = ny;
    }
    if (temp[x][y] != -1){
        if (sharks[temp[x][y]].sz > sz) {
            caught = true;
            return;
        }
        sharks[temp[x][y]].caught = true;
    }
    temp[x][y] = idx;
}

void init(){
    cin >> r >> c >> m;
    grid.resize(r, vector<int>(c, -1));
    for (int i = 0; i < m; i++){
        int x, y, spd, dir, sz;
        cin >> x >> y >> spd >> dir >> sz;
        sharks.emplace_back(--x, --y, spd % (dir <= 2 ? (r - 1) * 2 : (c - 1) * 2), dir, sz, i);
        grid[x][y] = i;
    }
}

int32_t main() {
    fastIO;
    init();
    int ans = 0;
    for (int j = 0; j < c; j++){
        for (int i = 0; i < r; i++){
            if (grid[i][j] != -1 && !sharks[grid[i][j]].caught){
                ans += sharks[grid[i][j]].sz;
                sharks[grid[i][j]].caught = true;
                grid[sharks[grid[i][j]].x][sharks[grid[i][j]].y] = -1;
                break;
            }
        }
        temp = matrix<int>(r, vector<int>(c, -1));
        for (auto& shark : sharks) {
            if (shark.caught) continue;
            shark.move();
        }
        grid = temp;
    }
    cout << ans;
    return 0;
}
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
class FenWickTree {
private:
    vector<int> tree;
    int size;

    void _update(int x, int val){
        for (int i = x; i < size; i += (i & -i)){
            tree[i] += val;
        }
    }

    int _query(int x){
        int res = 0;
        for (int i = x; i > 0; i -= (i & -i)){
            res += tree[i];
        }
        return res;
    }

public:
    FenWickTree(const vector<int>& v){
        size = v.size();
        tree = vector<int>(size);
        for (int i = 1; i < size; i++){
                _update(i, v[i]);
        }
    }

    void update(int x, int val){
        _update(x, val);
    }

    int query(int left, int right, int k){
        if (left == right) return left;

        int mid = (left + right) >> 1;
        int l = _query(left - 1);
        int m = _query(mid);
        if (m - l >= k) return query(left, mid, k);
        else return query(mid + 1, right, k - m + l);
    }
};
const int mx = 2'000'001;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(mx, 0);
    FenWickTree fenWickTree(v);

    for (int i = 0; i < n; i++) {
        int cmd, x;
        cin >> cmd >> x;
        if (cmd == 1){
            fenWickTree.update(x, 1);
        } else {
            int ans = fenWickTree.query(1, mx - 1, x);
            fenWickTree.update(ans, -1);
            cout << ans << '\n';
        }
    }

    return 0;
}
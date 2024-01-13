//
// Created by june0 on 2024-01-13.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define int ll
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

const int MOD = 1'000'000'007;

/**
 * Lazy Segment Tree that can be used to efficiently handle the range queries
 */
template<typename T>
class LazySegTree {
private:
    vector<T> tree, lazy_sum, lazy_mul;
    vector<T> arr;
    int size, height;

    T init(int node, int left, int right){
        if (left == right) return tree[node] = arr[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node] = (left_result + right_result) % MOD;

        return tree[node];
    }

    void update_lazy(int node, int start, int end) {
        if (lazy_sum[node] == 0 && lazy_mul[node] == 1) return;

        ((tree[node] *= lazy_mul[node])+= (end - start + 1) * lazy_sum[node]) %= MOD;
        if (start != end) {
            ((lazy_sum[node << 1] *= lazy_mul[node]) += lazy_sum[node]) %= MOD;
            ((lazy_sum[node << 1 | 1] *= lazy_mul[node]) += lazy_sum[node]) %= MOD;
            (lazy_mul[node << 1] *= lazy_mul[node]) %= MOD;
            (lazy_mul[node << 1 | 1] *= lazy_mul[node]) %= MOD;
        }
        lazy_sum[node] = 0;
        lazy_mul[node] = 1;
    }

    void _update(int node, int start, int end, int s_idx, int e_idx, T value, int mode) {
        update_lazy(node, start, end);

        if (e_idx < start || end < s_idx) return;

        if (s_idx <= start && end <= e_idx) {
            if (mode == 1) {
                (lazy_sum[node] += value) %= MOD;
            }
            else if (mode == 2) {
                (lazy_sum[node] *= value) %= MOD;
                (lazy_mul[node] *= value) %= MOD;
            }
            else if (mode == 3) {
                lazy_sum[node] = value;
                lazy_mul[node] = 0;
            }
            update_lazy(node, start, end);
            return;
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, s_idx, e_idx, value, mode);
        _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value, mode);
        tree[node] = (tree[node << 1] + tree[node << 1 | 1]) % MOD;
    }

    int _query(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);

        if (left > end || right < start) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return (left_result + right_result) % MOD;
    }

public:
    /**
     * Constructor for a lazy segment tree
     * @param arr  Build a segment tree from the given array
     */
    LazySegTree(const vector<int>& v){
        arr = v;
        height = (int)ceil(log2(arr.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        lazy_sum.resize(size + 1, 0);
        lazy_mul.resize(size + 1, 1);
        init(1, 0, arr.size() - 1);
    }

    void update(int s_idx, int e_idx, int value, int mode) {
        _update(1, 0, arr.size() - 1, s_idx, e_idx, value, mode);
    }

    int query(int left, int right){
        return _query(1, 0, arr.size() - 1, left, right);
    }
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v)
        cin >> e, e %= MOD;

    LazySegTree<int> lst(v);

    int m;
    cin >> m;
    while (m--){
        int cmd, x, y;
        cin >> cmd >> x >> y;
        if (cmd == 1){
            int a;
            cin >> a;
            lst.update(x - 1, y - 1, a, 1);
        } else if (cmd == 2){
            int a;
            cin >> a;
            lst.update(x - 1, y - 1, a, 2);
        } else if (cmd == 3){
            int a;
            cin >> a;
            lst.update(x - 1, y - 1, a, 3);
        } else {
            cout << lst.query(x - 1, y - 1) << endl;
        }
    }

    return 0;
}
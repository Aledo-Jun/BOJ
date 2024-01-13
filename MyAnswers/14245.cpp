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

/**
 * Lazy Segment Tree that can be used to efficiently handle the range queries
 */
template<typename T>
class LazySegTree {
private:
    T default_query;

    vector<T> tree, lazy;
    vector<T> arr;
    int size, height;

    T init(int node, int left, int right){
        if (left == right) return tree[node] = arr[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node] = (left_result ^ right_result);

        return tree[node];
    }

    void update_lazy(int node, int start, int end){
        if (lazy[node]) {
            tree[node] ^= (end - start + 1) & 1 ? lazy[node] : 0;
            if (start != end) {
                lazy[node << 1] ^= lazy[node];
                lazy[node << 1 | 1] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void _update(int node, int start, int end, int s_idx, int e_idx, T value) {
        update_lazy(node, start, end);

        if (e_idx < start || end < s_idx) return;

        if (s_idx <= start && end <= e_idx) {
            tree[node] ^= (end - start + 1) & 1 ? value : 0;
            if (start != end){
                lazy[node << 1] ^= value;
                lazy[node << 1 | 1] ^= value;
            }
            return;
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, s_idx, e_idx, value);
        _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
        tree[node] = (tree[node << 1] ^ tree[node << 1 | 1]);
    }

    int _query(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);

        if (left > end || right < start) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return (left_result ^ right_result);
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
        lazy.resize(size + 1);
        init(1, 0, arr.size() - 1);
    }

    void update(int s_idx, int e_idx, int value) {
        _update(1, 0, arr.size() - 1, s_idx, e_idx, value);
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
        cin >> e;

    LazySegTree<int> lst(v);

    int m;
    cin >> m;
    while (m--){
        int cmd;
        cin >> cmd;
        if (cmd == 1){
            int a, b, c;
            cin >> a >> b >> c;
            lst.update(a, b, c);
        } else {
            int a;
            cin >> a;
            cout << lst.query(a, a) << endl;
        }
    }

    return 0;
}
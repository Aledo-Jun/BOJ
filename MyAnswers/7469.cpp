//
// Created by june0 on 2024-01-09.
// Using merge-sort tree and binary search
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
template<typename T,
        typename func = plus<T>,
        typename updating_func = plus<T>>
class SegTree {
private:
    func f;
    updating_func updating_f;
    T default_query;

    vector<T> tree, arr;
    int size, height;

    void init(int node, int left, int right){
        if (left == right) {
            tree[node] = arr[left];
            return;
        }

        int mid = (left + right) >> 1;
        init(node << 1, left, mid);
        init(node << 1 | 1, mid + 1, right);
        f(tree[node << 1], tree[node << 1 | 1], tree[node]);
    }

    void _update(int node, int start, int end, int idx, T value) {
        if (idx < start || end < idx) return;

        if (start == end){
            tree[node] = updating_f(tree[node], value);
        } else {
            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, idx, value);
            _update(node << 1 | 1, mid + 1, end, idx, value);
            f(tree[node << 1], tree[node << 1 | 1], tree[node]);
        }
    }

    int lower = 0, upper = 0;
    void _query(int node, int start, int end, int left, int right, int k) {
        if (end < left || right < start) return;
        if (left <= start && end <= right) {
            lower += distance(tree[node].begin(),
                              lower_bound(tree[node].begin(), tree[node].end(), k));
            upper += distance(tree[node].begin(),
                              upper_bound(tree[node].begin(), tree[node].end(), k));
            return;
        }

        int mid = (start + end) >> 1;
        _query(node << 1, start, mid, left, right, k);
        _query(node << 1 | 1, mid + 1, end, left, right, k);
    }

public:
    explicit SegTree(const vector<T>& v, T default_query = 0) : arr(v), default_query(std::move(default_query)){
        height = (int)ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        init(1, 0, arr.size() - 1);
    }

    void update(int idx, T value) {
        _update(1, 0, arr.size() - 1, idx, value);
    }

    int query(int left, int right, int k){
        int low = -1E9, high = 1E9, mid = 0;
        while (true){
            lower = upper = 0;
            if (low + high < 0){
                mid = (low + high - 1) / 2;
            } else {
                mid = (low + high) / 2;
            }
            _query(1, 0, arr.size() - 1, left, right, mid);
            if (lower == k - 1 && upper == k) break;
            lower < k ? low = mid : high = mid;
        }
        return mid;
    }
};

template<typename T>
struct merge_vec {
    constexpr void operator()(const vector<T>& a, const vector<T>& b, vector<T>& res){
        res.resize(a.size() + b.size());
        std::merge(a.begin(), a.end(), b.begin(), b.end(), res.begin());
    }
};

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    matrix<int> v(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v[i].emplace_back(x);
    }

    SegTree<vector<int>, merge_vec<int>> segTree(v, vector<int>());

    while (m--){
        int i, j, k;
        cin >> i >> j >> k;
        cout << segTree.query(i - 1, j - 1, k) << '\n';
    }

    return 0;
}
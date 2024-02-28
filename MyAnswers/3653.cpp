//
// Created by june0 on 2024-02-28.
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

//
/// "Premature optimization is the root of all evil." -- Donald Knuth
//

/**
 * Segment Tree that contains the result of a query over the range.
 * @tparam T type of elements
 * @tparam func function object to be called to perform the query
 * @tparam updating_func function object to be called to update the containing element
 */
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

    T init(int node, int left, int right) {
        if (left == right) return tree[node] = arr[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node] = f(left_result, right_result);

        return tree[node];
    }

    /**
     * Update the tree as a result of performing <i>updating_func</i> with <i>value</i> to the arr[idx]
     * @param node current node index in the tree
     * @param start starting index that the current node is covering
     * @param end ending index that the current node is covering
     * @param idx index of array that updating is required
     * @param value the value to be used for performing <i>updating_func</i> to the arr[idx]
     */
    void _update(int node, int start, int end, int idx, T value) {
        if (idx < start || end < idx) return;

        if (start == end) {
            tree[node] = updating_f(tree[node], value);
        } else {
            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, idx, value);
            _update(node << 1 | 1, mid + 1, end, idx, value);
            tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
        }
    }


    /**
     * Find the result of @p func over the array elements in range [left, right]
     * @param node current node index in the tree
     * @param start starting index that the current node is covering
     * @param end ending index that the current node is covering
     * @param left starting index of performing @p func
     * @param right ending index of performing @p func
     * @return the result of @p func over the array elements in range [left, right]
     */
    T _query(int node, int start, int end, int left, int right) {
        if (end < left || right < start) return default_query;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return f(left_result, right_result);
    }

public:
    /**
     * Constructor for a segment tree
     * @param v Array that the segment tree will be constructed from
     * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
     */
    SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
        arr = v;
        height = (int) ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        init(1, 0, v.size() - 1);
    }

    void update(int idx, T value) {
        _update(1, 0, arr.size() - 1, idx, value);
    }

    T query(int left, int right) {
        return _query(1, 0, arr.size() - 1, left, right);
    }
}; // class SegTree

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    while (t--){
        int n, m;
        cin >> n >> m;
        vector<int> v(n + m, 0), q(m);
        for (int i = 0; i < n; i++) v[i] = 1;
        for (int i = 0; i < m; i++) cin >> q[i];

        vector<int> height(n + 1);
        for (int i = 1; i <= n; i++) height[i] = n - i;
        int top = n - 1;

        SegTree segTree(v);
        for (int i = 0; i < m; i++){
            int res = segTree.query(height[q[i]] + 1, top);
            cout << res << ' ';

            segTree.update(height[q[i]], -1);
            segTree.update(++top, +1);
            height[q[i]] = top;
        }
        cout << endl;
    }
    return 0;
}
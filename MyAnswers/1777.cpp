//
// Created by june0 on 2024-01-29.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

namespace Utils
{
    namespace SegTree {
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
            explicit SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
                arr = v;
                height = (int) ceil(log2(v.size()));
                size = (1 << (height + 1));
                tree.resize(size + 1);
                init(1, 0, v.size() - 1);
            }

            void update(int idx, T value) {
                _update(1, 0, arr.size() - 1, idx, value);
            }

            int query(int k) {
                int l = 1, r = arr.size() - 1;
                int m;
                while (l <= r) {
                    m = (l + r) >> 1;
                    int cnt = _query(1, 0, arr.size() - 1, m, arr.size() - 1);
                    if (cnt > k) l = m + 1;
                    else r = m - 1;
                }
                return r;
            }
        }; // class SegTree
    } // namespace SegTree

} // namespace Utils

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> src(n + 1);
    for (int i = 1; i <= n; i++) cin >> src[i];

    vector<int> v(n + 1, 1);

    Utils::SegTree::SegTree segTree(v);

    vector<int> ans(n + 1);
    for (int i = n; i > 0; i--){
        int idx = segTree.query(src[i]);
        ans[idx] = i;
        segTree.update(idx, -1);
    }

    for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
    return 0;
}

#ifdef ANOTHER_SOLUTION
//
// This solution uses an external data structure called "rope"
// that allows us to insert items or slice the sequence in logarithmic time.
//
#include <bits/extc++.h>
using namespace __gnu_cxx;

int32_t main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    __gnu_cxx::rope<int> r;
    for (int i = 1; i <= n; i++){
        int x; cin >> x;
        r.insert(r.size() - x, i);
    }
    for (auto e : r) cout << e << ' ';

    return 0;
}

#endif
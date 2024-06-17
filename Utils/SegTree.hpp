#include <vector>
#include <cmath>
#include <functional>

using namespace std;

namespace Utils
{
namespace SegTree
{
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

/**
 * Segment Tree using iterative method
 * @tparam T type of elements
 * @tparam func function object to be called to perform the query
 * @tparam updating_func function object to be called to update the containing element
 */
    template<typename T,
            typename func = plus<T>,
            typename updating_func = plus<T>>
    class SegTree_iter {
    private:
        func f;
        updating_func updating_f;
        T default_query;

        vector<T> tree, arr;
        int size, height;

        void init() {
            for (int i = size / 2 - 1; i > 0; i--)
                tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
        }

        void _update(int i, T value) {
            i += size / 2;
            tree[i] = updating_f(tree[i], value);
            for (i >>= 1; i > 0; i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
        }

        T _query(int i) {
            T res = default_query;
            for (i += size / 2; i > 0; i >>= 1) res = f(res, tree[i]);
            return res;
        }

        T _query(int l, int r) {
            T res1 = default_query, res2 = default_query;
            for (l += size / 2, r += size / 2; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) res1 = f(res1, tree[l++]);
                if (~r & 1) res2 = f(tree[r--], res2);
                // NOTE: There exists cases that the operation's order must be considered
            }
            return f(res1, res2);
        }

    public:
        /**
         * Constructor for a segment tree
         * @param v Array that the segment tree will be constructed from
         * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
         */
        SegTree_iter(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
            arr = v;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1, default_query);
            std::copy(arr.begin(), arr.end(), tree.begin() + size / 2);
            init();
        }

        void update(int idx, T value) {
            _update(idx, value);
        }

        T query(int idx) {
            return _query(idx);
        }

        T query(int left, int right) {
            return _query(left, right);
        }
    }; // class SegTree_iter

/**
 * Lazy Segment Tree that can be used to efficiently handle the range queries
 * @tparam T Value type
 * @tparam S Lazy type
 * @tparam TT Functor to merge tree nodes -> T(T,T)
 * @tparam SS Functor to update lazy value -> S(S,S)
 * @tparam TS Functor to update tree node with lazy value and offset -> T(T,S,int)
 */
    template<typename T, typename S,
            typename TT = T(T,T),
            typename SS = S(S,S),
            typename TS = T(T,S,int)>
    class LazySegTree {
    private:
        TT f;
        SS lazy_to_lazy;
        TS lazy_to_tree;

        vector<T> v;
        vector<T> tree;
        vector<S> lazy;

        int size{}, height{};
        T default_query;
        S default_lazy;

        T init(int node, int left, int right) {
            if (left == right) return tree[node] = v[left];

            int mid = (left + right) >> 1;
            auto left_result = init(node << 1, left, mid);
            auto right_result = init(node << 1 | 1, mid + 1, right);
            tree[node] = f(left_result, right_result);

            return tree[node];
        }

        void update_lazy(int node, int start, int end) {
            if (lazy[node] != default_lazy) {
                tree[node] = lazy_to_tree(tree[node], lazy[node], end - start + 1);
                if (start != end) {
                    lazy[node << 1] = lazy_to_lazy(lazy[node << 1], lazy[node]);
                    lazy[node << 1 | 1] = lazy_to_lazy(lazy[node << 1 | 1], lazy[node]);
                }
                lazy[node] = default_lazy;
            }
        }

        /**
         * Update the tree as a result of adding values to the array from s_idx to e_idx
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param s_idx starting index that updating is required
         * @param e_idx ending index that updating is required
         * @param value the value to be added to the array
         */
        void _update(int node, int start, int end, int s_idx, int e_idx, S value) {
            update_lazy(node, start, end);

            if (e_idx < start || end < s_idx) return;

            if (s_idx <= start && end <= e_idx) {
                lazy[node] = lazy_to_lazy(lazy[node], value);
                update_lazy(node, start, end);
                return;
            }

            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, s_idx, e_idx, value);
            _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
            tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
        }

        /**
         * Find the sum of the array elements in range [left, right]
         * @param node current node index in the tree
         * @param start starting index that the current node is covering
         * @param end ending index that the current node is covering
         * @param left starting index of summation
         * @param right ending index of summation
         * @return the sum of the array elements in range [left, right]
         */
        T _query(int node, int start, int end, int left, int right) {
            update_lazy(node, start, end);

            if (end < left || right < start) return default_query;
            if (left <= start && end <= right) return tree[node];

            int mid = (start + end) >> 1;
            auto left_result = _query(node << 1, start, mid, left, right);
            auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
            return f(left_result, right_result);
        }

        int _get_kth(int node, int start, int end, T k) {
            update_lazy(node, start, end);
            if (start == end) return start;
            int mid = (start + end) >> 1;
            update_lazy(node << 1, start, mid);
            update_lazy(node << 1 | 1, mid + 1, end);
            if (k <= tree[node << 1]) return _get_kth(node << 1, start, mid, k);
            return _get_kth(node << 1 | 1, mid + 1, end, k - tree[node << 1]);
        }

    public:
        LazySegTree() = default;
        /**
         * Construct segTree with the size of @p sz filled with default values
         * @param sz
         */
        LazySegTree(int sz, T default_query = {}, S default_lazy = {})
                : default_query(std::move(default_query)), default_lazy(std::move(default_lazy))
        {
            v = vector<T>(sz, default_query);
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1, default_query);
            lazy.resize(size + 1, default_lazy);
        }
        /**
         * Constructor for a lazy segment tree
         * @param arr  Build a segment tree from the given array
         */
        LazySegTree(const vector<T> &arr, T default_query, S default_lazy)
                : default_query(std::move(default_query)),
                  default_lazy(std::move(default_lazy))
        {
            v = arr;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            tree.resize(size + 1);
            lazy.resize(size + 1, default_lazy);
            init(1, 0, v.size() - 1);
        }

        void update(int s_idx, int e_idx, S value) {
            if (s_idx > e_idx) return;
            _update(1, 0, v.size() - 1, s_idx, e_idx, value);
        }

        T query(int left, int right) {
            if (left > right) return default_query;
            return _query(1, 0, v.size() - 1, left, right);
        }

        int get_kth(T k) {
            return _get_kth(1, 0, v.size() - 1, k);
        }
    }; // class LazySegTree

/**
 * Lazy Segment Tree using iterative method
 * @tparam T value type
 * @tparam S lazy type
 * @tparam TT functor to merge tree nodes -> T(T,T)
 * @tparam SS functor to update the lazy value -> S(S,S)
 * @tparam TS functor to apply lazy update to tree node -> T(T,S,int)
 */
    template<typename T, typename S = T,
            typename TT = T(T,T),
            typename SS = S(S,S),
            typename TS = T(T,S,int)>
    class LazySegTree_iter {
    private:
        TT f;
        SS lazy_to_lazy;
        TS lazy_to_tree;
        T default_query;
        S default_lazy;

        vector<T> tree, arr;
        vector<S> lazy;
        int size{}, height{}, n{};

        void init() {
            for (int i = n - 1; i >= 1; i--) pull(i);
        }

        void apply(int node, S value, int offset) {
            tree[node] = lazy_to_tree(tree[node], value, offset);
            if (node < n) lazy[node] = lazy_to_lazy(lazy[node], value);
        }

        void pull(int node) {
            tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
        }

        void pull_all(int l, int r) {
            for (int i = 1; i <= height; i++) {
                if ((l >> i << i) != l) pull(l >> i);
                if ((r >> i << i) != r) pull((r - 1) >> i);
            }
        }

        void push(int node, int offset = 2) {
            if (lazy[node] == default_lazy) return;
            apply(node << 1, lazy[node], offset >> 1);
            apply(node << 1 | 1, lazy[node], offset >> 1);
            lazy[node] = default_lazy;
        }

        void push_all(int l, int r) {
            for (int i = height, k = n; i >= 1; i--, k >>= 1) {
                if ((l >> i << i) != l) push(l >> i, k);
                if ((r >> i << i) != r) push((r - 1) >> i, k);
            }
        }

        void _update(int i, S value) {
            i += n;
            for (int j = height; j >= 1; j--) push(i >> j);
            tree[i] = lazy_to_tree(tree[i], value, 1);
            for (int j = 1; j <= height; j++) pull(i >> j);
        }

        void _update(int l, int r, S value) {
            l += n, r += n;
            push_all(l, r + 1);

            int l0 = l, r0 = r;
            for (int k = 1; l <= r; l >>= 1, r >>= 1, k <<= 1) {
                if (l & 1) apply(l++, value, k);
                if (~r & 1) apply(r--, value, k);
            }

            l = l0, r = r0;
            pull_all(l, r + 1);
        }

        T _query(int i) {
            i += n;
            for (int j = height; j >= 1; j--) push(i >> j);
            return tree[i];
        }

        T _query(int l, int r) {
            l += n, r += n;
            push_all(l, r + 1);

            T res1 = default_query, res2 = default_query;
            for (; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) res1 = f(res1, tree[l++]);
                if (~r & 1) res2 = f(tree[r--], res2);
                // NOTE: There exists cases that the operation's order must be considered
            }
            return f(res1, res2);
        }

        int _get_kth(T k) {
            for (int node = 1, offset = n; ; offset >>= 1) {
                if (node >= n) return node - n;
                push(node, offset);
                if (k <= tree[node << 1]) node = node << 1;
                else {
                    k -= tree[node << 1];
                    node = node << 1 | 1;
                }
            }
        }

    public:
        LazySegTree_iter() = default;
        /**
         * Construct segTree with the size of @p sz filled with default values
         * @param sz
         */
        LazySegTree_iter(int sz, T _default_query = {}, S _default_lazy = {})
                : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy))
        {
            height = (int) ceil(log2(sz));
            size = (1 << (height + 1));
            n = size >> 1;
            tree.resize(size + 1, default_query);
            lazy.resize(size + 1, default_lazy);
        }
        /**
         * Constructor for a segment tree
         * @param v Array that the segment tree will be constructed from
         * @param default_query The result of query that doesn't affect the other query result when performed <i>TT</i> with
         */
        explicit
        LazySegTree_iter(const vector<T> &v, T _default_query = 0, S _default_lazy = 0)
                : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy))
        {
            arr = v;
            height = (int) ceil(log2(v.size()));
            size = (1 << (height + 1));
            n = size >> 1;
            tree.resize(size + 1, default_query);
            lazy.resize(size + 1, default_lazy);
            std::copy(arr.begin(), arr.end(), tree.begin() + n);
            init();
        }

        void update(int idx, S value) {
            _update(idx, value);
        }

        void update(int l, int r, S value) {
            _update(l, r, value);
        }

        T query(int idx) {
            return _query(idx);
        }

        T query(int left, int right) {
            return _query(left, right);
        }

        int get_kth(T k) {
            return _get_kth(k);
        }
    }; // class LazySegTree_iter


    template<typename T = int,
            typename Func = plus<T>,
            typename Inv_Func = minus<T>,
            T Identity = 0>
    class FenWickTree {
    private:
        Func f;
        Inv_Func inv_f;

        vector<T> tree;
        int size;

        void _update(int x, T val) {
            for (int i = x; i < size; i += (i & -i)) {
                tree[i] = f(tree[i], val);
            }
        }

        T _query(int x) {
            T res = Identity;
            for (int i = x; i > 0; i -= (i & -i)) {
                res = f(res, tree[i]);
            }
            return res;
        }

    public:
        // Empty tree constructor
        FenWickTree(int size) : size(size) { // NOLINT
            tree.resize(size, Identity);
        }

        FenWickTree(const vector<T> &v) {
            size = (int) v.size();
            tree.resize(size);
            for (int i = 1; i < size; i++) {
                _update(i, v[i]);
            }
        }

        void update(int x, T val) {
            _update(x, val);
        }

        T query(int idx) {
            return _query(idx);
        }

        T query(int left, int right) {
            if (left > right) return Identity;
            return inv_f(_query(right), _query(left - 1));
        }
    }; // class FenWickTree

    template<typename T> using matrix = vector<vector<T>>;

    class FenWickTree_2D {
    private:
        matrix<int> tree;
        int size;

        void _update(int x, int y, int val) {
            for (int i = x; i < size; i += (i & -i)) {
                for (int j = y; j < size; j += (j & -j)) {
                    tree[i][j] += val;
                }
            }
        }

        int _query(int x, int y) {
            int res = 0;
            for (int i = x; i > 0; i -= (i & -i)) {
                for (int j = y; j > 0; j -= (j & -j)) {
                    res += tree[i][j];
                }
            }
            return res;
        }

    public:
        FenWickTree_2D(const matrix<int> &mat) {
            size = mat.size();
            tree = matrix<int>(size, vector<int>(size));
            for (int i = 1; i < size; i++) {
                for (int j = 1; j < size; j++) {
                    _update(i, j, mat[i][j]);
                }
            }
        }

        void update(int x, int y, int val) {
            _update(x, y, val);
        }

        int query(int x1, int y1, int x2, int y2) {
            return _query(x2, y2) - _query(x2, y1 - 1) - _query(x1 - 1, y2) + _query(x1 - 1, y1 - 1);
        }
    }; // class FenWickTree_2D

    template<typename T = int,
            typename Func = plus<T>,
            typename Inv_Func = minus<T>,
            typename Update_Func = plus<T>,
            const int MAX = 100'000>
    class PersistentSegTree {
    private:
        Func f;
        Inv_Func inv_f;
        Update_Func u;

        struct Node {
            T val;
            int l, r;

            Node() : val(0), l(0), r(0) {}
            Node(T val, int l, int r) : val(val), l(l), r(r) {}
        };

        int sz, ptr = 1;
        std::vector<int> roots;
        std::vector<Node> tree;

        void make_root() { // maybe not useful?
            roots.emplace_back(ptr++);
            tree.emplace_back();
        }

        void _update(int prev, int curr, int s, int e, int idx, T val) {
            tree[curr].val = u(tree[prev].val, val);

            if (s == e) return;

            int m = (s + e) >> 1;
            if (idx <= m) {
                tree[curr].l = ptr++;
                tree.emplace_back();
                tree[curr].r = tree[prev].r;
                _update(tree[prev].l, tree[curr].l, s, m, idx, val);
            } else {
                tree[curr].r = ptr++;
                tree.emplace_back();
                tree[curr].l = tree[prev].l;
                _update(tree[prev].r, tree[curr].r, m + 1, e, idx, val);
            }
        }

        T _query(int node, int s, int e, int l, int r) {
            if (e < l || r < s) return T();
            if (l <= s && e <= r) return tree[node].val;

            int m = (s + e) >> 1;
            return f(_query(tree[node].l, s, m, l, r), _query(tree[node].r, m + 1, e, l, r));
        }

        int _find_kth(int i, int j, int p, int pp, int s, int e, int k) {
            if (s == e) return s;
            int sum = tree[tree[i].l].val
                      + tree[tree[j].l].val
                      - tree[tree[p].l].val
                      - tree[tree[pp].l].val;
            int m = (s + e) >> 1;
            if (sum >= k) return _find_kth(tree[i].l, tree[j].l, tree[p].l, tree[pp].l, s, m, k);
            else return _find_kth(tree[i].r, tree[j].r, tree[p].r, tree[pp].r, m + 1, e, k - sum);
        }

        int _find_kth(int l, int r, int s, int e, int k) {
            if (s == e) return s; // Leaf node

            int l1 = tree[tree[l].l].val, l2 = tree[tree[l].r].val;
            int r1 = tree[tree[r].l].val, r2 = tree[tree[r].r].val;

            int left = r1 - l1;

            int m = (s + e) >> 1;
            if (left >= k) return _find_kth(tree[l].l, tree[r].l, s, m, k);
            else return _find_kth(tree[l].r, tree[r].r, m + 1, e, k - left);
        }

        int _find_kth(int node, int s, int e, int k) {
            if (s == e) return s; // Leaf node

            int left = tree[tree[node].l].val;

            int m = (s + e) >> 1;
            if (left >= k) return _find_kth(tree[node].l, s, m, k);
            else return _find_kth(tree[node].r, m + 1, e, k - left);
        }

    public:
        // Construct the empty tree with size of n
        explicit PersistentSegTree(int n = MAX + 5) : sz(n) {
            tree.reserve(1'000'000); // n + q * log n
            tree.emplace_back(); // padding for convenience

            roots.emplace_back(ptr++); // Create NIL node
            tree.emplace_back(0, 1, 1);
        }

        int update(int idx, T val) {
            int prev = roots.back();
            roots.emplace_back(ptr++); // Create new root node
            tree.emplace_back();
            int curr = roots.back();

            _update(prev, curr, 0, sz - 1, idx, val);
            return (int) roots.size() - 1;
        }

        int update(int version, int idx, T val) {
            int prev = roots[version];
            roots.emplace_back(ptr++); // Create new root node
            tree.emplace_back();
            int curr = roots.back();

            _update(prev, curr, 0, sz - 1, idx, val);
            return (int) roots.size() - 1;
        }

        /**
         * Returns the query over the range [l,r] when updates with index [i,j] are performed.
         * @param i starting index of included updates
         * @param j ending index of included updates
         * @param l starting range of the query
         * @param r ending range of the query
         * @return querying result
         */
        T query(int i, int j, int l, int r) {
            T res1 = _query(roots[max(0, i - 1)], 0, sz - 1, l, r);
            T res2 = _query(roots[j], 0, sz - 1, l, r);
            return inv_f(res2, res1);
        }

        T query(int i, int l, int r) {
            return _query(roots[i], 0, sz - 1, l, r);
        }

        /**
         * Find the k-th element on the path of i -> j in a tree
         * @param p lca of i, j
         * @param pp p's direct parent
         * @return
         */
        int find_kth(int i, int j, int p, int pp, int k) {
            return _find_kth(roots[i], roots[j], roots[p], roots[pp], 0, sz - 1, k);
        }

        int find_kth(int l, int r, int k) {
            return _find_kth(roots[l], roots[r], 0, sz - 1, k);
        }

        int find_kth(int version, int k) {
            return _find_kth(roots[version], 0, sz - 1, k);
        }
    };
} // namespace SegTree

namespace SpecialSegTree
{
/**
 * @brief SegTree for Mars Map query i.e. counts the number of 0's
 * @tparam T value type
 */
    template<typename T>
    class MarsSegTree {
    private:
        vector<T> tree, tree2;
        int size, height, n;

        void init() {
            for (int i = 0; i < n; i++) {
                tree[i + size / 2] = 0;
                tree2[i + size / 2] = 1;
            }
            for (int i = size / 2 - 1; i > 0; i--) {
                tree2[i] = tree2[i << 1] + tree2[i << 1 | 1];
            }
        }

        void apply(int node, T value) {
            tree[node] += value;
            if (tree[node] > 0) tree2[node] = 0;
            else if (node >= size / 2) tree2[node] = 1;
            else tree2[node] = tree2[node << 1] + tree2[node << 1 | 1];
        }

        void _update(int l, int r, T value) {
            l += size / 2, r += size / 2;
            int l0 = l, r0 = r;

            for (; l <= r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, value);
                if (~r & 1) apply(r--, value);
            }

            // pulling up
            l = l0, r = r0;
            while (l > 1) {
                l >>= 1;
                apply(l, 0);
            }
            while (r > 1) {
                r >>= 1;
                apply(r, 0);
            }
        }

    public:
        MarsSegTree(int n) : n(n) {
            height = (int) ceil(log2(n));
            size = (1 << (height + 1));
            tree.resize(size + 1);
            tree2.resize(size + 1);
            init();
        }

        void update(int l, int r, T value) {
            if (l > r) return;
            _update(l, r, value);
        }

        int get_total_visible() {
            return tree2[1];
        }
    }; // class MarsSegTree

    class GoldMineSegTree {
        template<typename T = long long>
        struct GoldMineSeg {
            /*
             * Suppose a node is representing a range of [s,...m,...e]
             * l := max_contiguous_sum[(s,...m,...),...e]
             * r := max_contiguous_sum[s,...,(...m,...e)]
             * mx := max_contiguous_sum[(s,...m,...e)] -> answer
             * sum := total sum of the range
             */
            T l = 0, r = 0, mx = 0, sum = 0;

            GoldMineSeg() = default;

            GoldMineSeg(T l, T r, T mx, T sum) : l(l), r(r), mx(mx), sum(sum) {}

            GoldMineSeg(T val) : l(max(val, 0LL)), r(max(val, 0LL)), mx(max(val, 0LL)), sum(val) {}
        };

        struct merge_goldmine {
            GoldMineSeg<> operator()(const GoldMineSeg<> &l, const GoldMineSeg<> &r) {
                return {max({l.l, l.sum + r.l, 0LL}),
                        max({l.r + r.sum, r.r, 0LL}),
                        max({l.mx, r.mx, l.r + r.l, 0LL}),
                        l.sum + r.sum};
            }
        };
    }; // class GoldMineSegTree

} // namespace SpecialSegTree
} // namespace Utils
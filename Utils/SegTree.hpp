#include <vector>
#include <cmath>
#include <functional>

using namespace std;
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

    T init(int node, int left, int right){
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

        if (start == end){
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
    SegTree(const vector<T>& v, T default_query = 0) : default_query(std::move(default_query)){
        arr = v;
        height = (int)ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        init(1, 0, v.size() - 1);
    }

    void update(int idx, T value) {
        _update(1, 0, arr.size() - 1, idx, value);
    }

    T query(int left, int right){
        return _query(1, 0, arr.size() - 1, left, right);
    }
};

/**
 * Lazy Segment Tree that can be used to efficiently handle the range queries
 */
class LazySegTree {
private:
    vector<int> tree, lazy;
    vector<int> v;
    int size, height;

    int init(int node, int left, int right){
        if (left == right) return tree[node] = v[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node] = (left_result + right_result);

        return tree[node];
    }

    void update_lazy(int node, int start, int end){
        if (lazy[node]) {
            tree[node] += lazy[node] * (end - start + 1);
            if (start != end) {
                lazy[node << 1] += lazy[node];
                lazy[node << 1 | 1] += lazy[node];
            }
            lazy[node] = 0;
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
    void _update(int node, int start, int end, int s_idx, int e_idx, int value) {
        update_lazy(node, start, end);

        if (e_idx < start || end < s_idx) return;

        if (s_idx <= start && end <= e_idx) {
            tree[node] += value * (end - start + 1);
            if (start != end){
                lazy[node << 1] += value;
                lazy[node << 1 | 1] += value;
            }
            return;
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, s_idx, e_idx, value);
        _update(node << 1 | 1, mid + 1, end, s_idx, e_idx, value);
        tree[node] = (tree[node << 1] + tree[node << 1 | 1]);
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
    int _query(int node, int start, int end, int left, int right) {
        update_lazy(node, start, end);

        if (left > end || right < start) return 0;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return (left_result + right_result);
    }

public:

    /**
     * Constructor for a lazy segment tree
     * @param arr  Build a segment tree from the given array
     */
    LazySegTree(const vector<int>& arr){
        v = arr;
        height = (int)ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        lazy.resize(size + 1);
        init(1, 0, v.size() - 1);
    }

    void update(int s_idx, int e_idx, int value) {
        _update(1, 0, v.size() - 1, s_idx, e_idx, value);
    }

    int query(int left, int right){
        return _query(1, 0, v.size() - 1, left, right);
    }
};

template<typename T> using matrix = vector<vector<T>>;

class FenWickTree {
private:
    matrix<int> tree;
    int size;

    void _update(int x, int y, int val){
        for (int i = x; i < size; i += (i & -i)){
            for (int j = y; j < size; j += (j & -j)){
                tree[i][j] += val;
            }
        }
    }

    int _query(int x, int y){
        int res = 0;
        for (int i = x; i > 0; i -= (i & -i)){
            for (int j = y; j > 0; j -= (j & -j)){
                res += tree[i][j];
            }
        }
        return res;
    }

public:
    FenWickTree(const matrix<int>& mat){
        size = mat.size();
        tree = matrix<int>(size, vector<int>(size));
        for (int i = 1; i < size; i++){
            for (int j = 1; j < size; j++){
                _update(i, j, mat[i][j]);
            }
        }
    }

    void update(int x, int y, int val){
        _update(x, y, val);
    }

    int query(int x1, int y1, int x2, int y2){
        return _query(x2, y2) - _query(x2, y1 - 1) - _query(x1 - 1, y2) + _query(x1 - 1, y1 - 1);
    }
};
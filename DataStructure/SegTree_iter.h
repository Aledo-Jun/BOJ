//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_SEGTREE_ITER_H
#define BOJ_SEGTREE_ITER_H

#include <cmath>
#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
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
            int size, height, n;

            void init() {
                for (int i = n - 1; i > 0; i--)
                    tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
            }

            void _update(int i, T value) {
                i += n;
                tree[i] = updating_f(tree[i], value);
                for (i >>= 1; i > 0; i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
            }

            T _query(int i) {
                T res = default_query;
                for (i += n; i > 0; i >>= 1) res = f(res, tree[i]);
                return res;
            }

            T _query(int l, int r) {
                T res1 = default_query, res2 = default_query;
                for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
                    if (l & 1) res1 = f(res1, tree[l++]);
                    if (~r & 1) res2 = f(tree[r--], res2);
                    // NOTE: There exists cases that the operation's order must be considered
                }
                return f(res1, res2);
            }

        public:
            SegTree_iter() = default;
            SegTree_iter(int sz, T&& default_query = {}) : default_query(std::move(default_query)) {
                height = (int) ceil(log2(sz));
                size = (1 << (height + 1));
                n = size >> 1;
                tree.resize(size + 1, default_query);
            }

            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
             */
            SegTree_iter(const vector<T> &v, T&& default_query = {}) : SegTree_iter(v.size()) {
                arr = v;
                this->default_query = default_query;
                std::copy(arr.begin(), arr.end(), tree.begin() + n);
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
    }
}

#endif //BOJ_SEGTREE_ITER_H

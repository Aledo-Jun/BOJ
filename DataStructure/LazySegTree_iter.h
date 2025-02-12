//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_LAZYSEGTREE_ITER_H
#define BOJ_LAZYSEGTREE_ITER_H

#include <cmath>
#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
/**
 * Lazy Segment Tree using iterative method
 * @tparam T value type
 * @tparam S lazy type
 * @tparam TT functor to merge tree nodes -> T(T,T)
 * @tparam SS functor to update the lazy value -> S(S,S)
 * @tparam TS functor to apply lazy update to tree node -> T(T,S,int)
 */
        template<typename T, typename S = T,
                typename TT = T(T, T),
                typename SS = S(S, S),
                typename TS = T(T, S, int)>
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

            void push(int node, int offset) {
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
                for (int j = height, k = n >> 1; j >= 1; j--, k >>= 1) push(i >> j, k);
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
                for (int j = height, k = n >> 1; j >= 1; j--, k >>= 1) push(i >> j, k);
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
                for (int node = 1, offset = n;; offset >>= 1) {
                    if (node >= n) return node - n;
                    push(node, offset);
                    if (k <= tree[node << 1]) node = node << 1;
                    else {
                        k -= tree[node << 1];
                        node = node << 1 | 1;
                    }
                }
            }

            bool is_valid_range(int idx) {
                return 0 <= idx && idx < n;
            }

            bool is_valid_range(int l, int r) {
                return ((l <= r) && is_valid_range(l) && is_valid_range(r));
            }

        public:
            LazySegTree_iter() = default;

            /**
             * Construct segTree with the size of @p sz filled with default values
             * @param sz
             */
            LazySegTree_iter(int sz, T _default_query = {}, S _default_lazy = {})
                    : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy)) {
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
                    : default_query(std::move(_default_query)), default_lazy(std::move(_default_lazy)) {
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
                if (!is_valid_range(idx)) return;
                _update(idx, value);
            }

            void update(int l, int r, S value) {
                _update(max(0, l), min(r, n-1), value);
            }

            T query(int idx) {
                if (!is_valid_range(idx)) return 0;
                return _query(idx);
            }

            T query(int l, int r) {
                return _query(max(0, l), min(r, n-1));
            }

            int get_kth(T k) {
                return _get_kth(k);
            }
        }; // class LazySegTree_iter
    }
}

#endif //BOJ_LAZYSEGTREE_ITER_H

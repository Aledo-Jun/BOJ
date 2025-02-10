//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_LAZYSEGTREE_H
#define BOJ_LAZYSEGTREE_H

#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
/**
 * Lazy Segment Tree that can be used to efficiently handle the range queries
 * @tparam T Value type
 * @tparam S Lazy type
 * @tparam TT Functor to merge tree nodes -> T(T,T)
 * @tparam SS Functor to update lazy value -> S(S,S)
 * @tparam TS Functor to update tree node with lazy value and offset -> T(T,S,int)
 */
        template<typename T, typename S,
                typename TT = T(T, T),
                typename SS = S(S, S),
                typename TS = T(T, S, int)>
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
                    : default_query(std::move(default_query)), default_lazy(std::move(default_lazy)) {
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
                      default_lazy(std::move(default_lazy)) {
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
    }
}

#endif //BOJ_LAZYSEGTREE_H

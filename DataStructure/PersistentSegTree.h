//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_PERSISTENTSEGTREE_H
#define BOJ_PERSISTENTSEGTREE_H

#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
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
    }
}

#endif //BOJ_PERSISTENTSEGTREE_H

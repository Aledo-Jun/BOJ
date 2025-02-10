//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_FENWICKTREE_H
#define BOJ_FENWICKTREE_H

#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
        // [NOTE] 1-indexed
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
    }
}

#endif //BOJ_FENWICKTREE_H

//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_FENWICKTREE_2D_H
#define BOJ_FENWICKTREE_2D_H

#include <functional>
#include "../Utils/using_templates.hpp" // matrix<T>
using namespace std;

namespace DataStructure {
    namespace SegTree {
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
    }
}

#endif //BOJ_FENWICKTREE_2D_H

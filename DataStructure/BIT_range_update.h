//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_BIT_RANGE_UPDATE_H
#define BOJ_BIT_RANGE_UPDATE_H

#include <functional>
using namespace std;

namespace DataStructure {
    namespace SegTree {
        // use this if you're dealing with range updates and range queries
        // whose inverse operation is well-defined(ex. sum-minus, mul-div, xor-xor)
        template<typename T = int>
        class BIT_RangeUpdate {
        private:
            vector<T> tree1, tree2;
            int size;

            void _update(vector<T>& tree, int x, T val) {
                for (int i = x; i < size; i += (i & -i)) {
                    tree[i] += val;
                }
            }

            T _query(const vector<T>& tree, int x) const {
                T res = 0;
                for (int i = x; i > 0; i -= (i & -i)) {
                    res += tree[i];
                }
                return res;
            }

        public:
            // Empty tree constructor
            BIT_RangeUpdate(int size) : size(size) {
                tree1.resize(size + 1, 0);
                tree2.resize(size + 1, 0);
            }

            BIT_RangeUpdate(const vector<T>& v) : BIT_RangeUpdate((int)v.size()) {
                for (int i = 1; i <= size; i++) {
                    update(i, v[i - 1]);
                }
            }

            // Point update: add val to the element at x
            void update(int x, T val) {
                _update(tree1, x, val);
            }

            // Range update: add val to each element in range [left, right]
            void update(int left, int right, T val) {
                _update(tree1, left, val);
                _update(tree1, right + 1, -val);

                _update(tree2, left, -val * (left - 1));
                _update(tree2, right + 1, val * right);
            }

            // Query the prefix sum up to idx
            T query(int idx) const {
                return _query(tree1, idx) + _query(tree2, idx) - idx;
            }

            // Query the sum in the range [left, right]
            T query(int left, int right) const {
                if (left > right) return 0;
                left--;
                T l = _query(tree1, left) * (left) + _query(tree2, left);
                T r = _query(tree1, right) * right + _query(tree2, right);
                return r - l;
            }
        }; // class BIT_RangeUpdate
    }
}

#endif //BOJ_BIT_RANGE_UPDATE_H

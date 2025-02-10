//
// Created by june0 on 2025-02-10.
//

#ifndef BOJ_SPECIALSEGTREES_H
#define BOJ_SPECIALSEGTREES_H

#include <vector>
#include <cmath>
#include <functional>
using namespace std;

namespace DataStructure {
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

}
#endif //BOJ_SPECIALSEGTREES_H

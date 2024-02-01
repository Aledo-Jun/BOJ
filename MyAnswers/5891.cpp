//
// Created by june0 on 2024-02-01.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;

namespace Utils
{
    namespace SegTree {
        //
        // Bottom-Up version of SegTree
        //
        template<typename T,
                typename func = plus<T>,
                typename updating_func = plus<T>>
        class SegTree {
        private:
            func f;
            updating_func updating_f;
            T default_query;

            vector<T> tree;
            int size;

            void buildTree(const vector<T> &v) {
                size = v.size();
                tree.resize(size * 2);

                // Copy the elements to the leaves of the tree
                copy(v.begin(), v.end(), tree.begin() + size);

                // Build the rest of the tree bottom-up
                for (int i = size - 1; i > 0; --i) {
                    tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
                }
            }

            void updateLeaf(int idx, T value) {
                idx += size;
                tree[idx] = updating_f(tree[idx], value);

                // Propagate the update upwards
                for (idx >>= 1; idx > 0; idx >>= 1) {
                    tree[idx] = f(tree[idx << 1], tree[idx << 1 | 1]);
                }
            }

            T queryRange(int left, int right) const {
                T result = default_query;

                // Go up the tree to find the result for the given range
                for (left += size, right += size; left <= right; left >>= 1, right >>= 1) {
                    if (left & 1) result = f(result, tree[left++]);
                    if (!(right & 1)) result = f(result, tree[right--]);
                }

                return result;
            }

        public:
            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
             */
            explicit SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
                buildTree(v);
            }

            void update(int idx, T value) {
                updateLeaf(idx, value);
            }

            T query(int left, int right) const {
                return queryRange(left, right);
            }
        }; // class SegTree
    } // namespace SegTree

} // namespace Utils

const int MAX_N = 100'000;

struct min_max_query {
    int min_val = INT_MAX, max_val = -1;

    min_max_query operator()(const min_max_query& a, const min_max_query& b) const {
        return {min(a.min_val, b.min_val), max(a.max_val, b.max_val)};
    }

    friend min_max_query operator+(const min_max_query& a, const min_max_query& b)  {
        return b;
    }
};

int32_t main() {
    fastIO;
    int n, d;
    cin >> n >> d;
    vector<min_max_query> v(n);
    vector<pair<int,int>> points(n);
    for (int i = 0; i < n; i++){
        cin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end());

    Utils::SegTree::SegTree<min_max_query, min_max_query> segTree(v, {INT_MAX, -1});

    int ans = INT_MAX;
    int i = 0, j = 0;
    segTree.update(0, {points[0].second, points[0].second});
    while (j < n) {
        auto [mn, mx] = segTree.query(i, j);
        if (mx - mn >= d) {
            ans = min(ans, points[j].first - points[i].first);
            segTree.update(i++, {INT_MAX, -1});
        } else {
            j++;
            segTree.update(j, {points[j].second, points[j].second});
        }
    }

    cout << (ans == INT_MAX ? -1 : ans);

    return 0;
}
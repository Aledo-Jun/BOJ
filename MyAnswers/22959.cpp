//
// Created by june0 on 2024-02-01.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

#define int ll

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


struct replace_element {
    int operator()(const int a, const int b) const {
        return b;
    }
};

struct min_query {
    int operator()(const int a, const int b) const {
        return min(a, b);
    }
};

int32_t main() {
    fastIO;
    int n, m;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v) cin >> e;

    Utils::SegTree::SegTree<int, plus<>, replace_element> sumSegTree(v);
    Utils::SegTree::SegTree<int, min_query, replace_element> minSegTree(v, INT_MAX);

    cin >> m;
    while (m--) {
        int cmd, i, j;
        cin >> cmd >> i >> j;
        i--;
        if (cmd == 1) {
            sumSegTree.update(i, j);
            minSegTree.update(i, j);
        } else {
            int l = i, r = i;
            int low = 0, high = i;
            while (low <= high) {
                int mid = (low + high) >> 1;
                if (minSegTree.query(mid, i) >= j) l = mid, high = mid - 1;
                else low = mid + 1;
            }
            low = i, high = n - 1;
            while (low <= high) {
                int mm = (low + high) >> 1;
                if (minSegTree.query(i, mm) >= j) r = mm, low = mm + 1;
                else high = mm - 1;
            }

            int ans = sumSegTree.query(l, r);
            cout << ans << endl;
        }
    }

    return 0;
}
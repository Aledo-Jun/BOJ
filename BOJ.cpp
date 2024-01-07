#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

#define int ll
template<typename T,
        typename func = plus<T>,
        typename updating_func = plus<T>>
class SegTree {
private:
    func f;
    updating_func updating_f;
    T default_query;

    vector<T> tree, arr;
    int size, height;

    T init(int node, int left, int right){
        if (left == right) return tree[node] = arr[left];

        int mid = (left + right) >> 1;
        auto left_result = init(node << 1, left, mid);
        auto right_result = init(node << 1 | 1, mid + 1, right);
        tree[node].resize(left_result.size() + right_result.size());
        f(left_result, right_result, tree[node]);

        return tree[node];
    }

    void _update(int node, int start, int end, int idx, T value) {
        if (idx < start || end < idx) return;

        if (start == end){
            tree[node] = updating_f(tree[node], value);
        } else {
            int mid = (start + end) >> 1;
            _update(node << 1, start, mid, idx, value);
            _update(node << 1 | 1, mid + 1, end, idx, value);
            f(tree[node << 1], tree[node << 1 | 1], tree[node]);
        }
    }

    int _query(int node, int start, int end, int left, int right, int k) {
        if (end < left || right < start) return 0;
        if (left <= start && end <= right) {
            return distance(upper_bound(tree[node].begin(), tree[node].end(), k), tree[node].end());
        }

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right, k);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right, k);
        return left_result + right_result;
    }

public:
    explicit SegTree(const vector<T>& v, int default_query = 0) : arr(v), default_query(std::move(default_query)){
        height = (int)ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        init(1, 0, arr.size() - 1);
    }

    void update(int idx, T value) {
        _update(1, 0, arr.size() - 1, idx, value);
    }

    int query(int left, int right, int k){
        return _query(1, 0, arr.size() - 1, left, right, k);
    }
};

template<typename T>
struct merge_vec {
    constexpr void operator()(const vector<T>& a, const vector<T>& b, vector<T>& res){
        std::merge(a.begin(), a.end(), b.begin(), b.end(), res.begin());
    }
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    matrix<int> v(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        v[i].emplace_back(x);
    }

    SegTree<vector<int>, merge_vec<int>> segTree(v);

    int m;
    cin >> m;
    while (m--){
        int i, j, k;
        cin >> i >> j >> k;
        cout << segTree.query(i - 1, j - 1, k) << '\n';
    }

    return 0;
}
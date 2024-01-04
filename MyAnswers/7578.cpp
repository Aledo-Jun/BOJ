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
        tree[node] = f(left_result, right_result);

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
            tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
        }
    }

    T _query(int node, int start, int end, int left, int right) {
        if (end < left || right < start) return default_query;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return f(left_result, right_result);
    }

public:
    SegTree(const vector<T>& v, T default_query = 0) : default_query(std::move(default_query)){
        arr = v;
        height = (int)ceil(log2(v.size()));
        size = (1 << (height + 1));
        tree.resize(size + 1);
        init(1, 0, v.size() - 1);
    }

    void update(int idx, T value) {
        _update(1, 0, arr.size() - 1, idx, value);
    }

    T query(int left, int right){
        return _query(1, 0, arr.size() - 1, left, right);
    }
};

struct return_max {
    constexpr int operator()(const int& a, const int& b){
        return max(a, b);
    }
};
int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> m(1'000'000);
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        m[v[i]] = i;
    }
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        v[i] = m[x];
    }

    vector<int> w(n, 0);
    SegTree<int> segTree(w);

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += segTree.query(v[i] + 1, n - 1);
        segTree.update(v[i], 1);
    }
    cout << ans;

    return 0;
}
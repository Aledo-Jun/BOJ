//
// Created by june0 on 2024-02-13.
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

vector<int> buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    // Create a map to store the indices of elements in the inorder traversal
    unordered_map<int, int> inorder_map;
    for (int i = 0; i < inorder.size(); ++i) {
        inorder_map[inorder[i]] = i;
    }

    // Recursive helper function to build the tree
    function<vector<int>(int, int, int, int)> build = [&](int in_start, int in_end, int post_start, int post_end) -> vector<int> {
        if (in_start > in_end) return {};
        vector<int> preorder;
        int root_val = postorder[post_end];
        int root_idx = inorder_map[root_val];
        int left_size = root_idx - in_start;
        preorder.push_back(root_val);
        // Build left subtree
        vector<int> left_subtree = build(in_start, root_idx - 1, post_start, post_start + left_size - 1);
        preorder.insert(preorder.end(), left_subtree.begin(), left_subtree.end());
        // Build right subtree
        vector<int> right_subtree = build(root_idx + 1, in_end, post_start + left_size, post_end - 1);
        preorder.insert(preorder.end(), right_subtree.begin(), right_subtree.end());
        return preorder;
    };

    return build(0, inorder.size() - 1, 0, postorder.size() - 1);
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> inorder(n), postorder(n);
    for (auto& e : inorder) cin >> e;
    for (auto& e : postorder) cin >> e;

    auto preorder = buildTree(inorder, postorder);

    for (const auto& e : preorder) cout << e << ' ';

    return 0;
}

#ifdef ANOTHER_SOLUTION
// This solution doesn't use vector to store the preorder,
// rather it just print out the preorder itself, so that it's much faster than the above.
void buildTree(const vector<int>& inorder, const vector<int>& postorder) {
    // Create a map to store the indices of elements in the inorder traversal
    vector<int> inorder_map(inorder.size() + 1);
    for (int i = 0; i < inorder.size(); ++i) {
        inorder_map[inorder[i]] = i;
    }

    // Recursive helper function to build the tree
    function<void(int, int, int, int)> build = [&](int in_start, int in_end, int post_start, int post_end) -> void {
        if (in_start > in_end) return;
        int root_val = postorder[post_end];
        cout << root_val << ' ';
        int root_idx = inorder_map[root_val];
        int left_size = root_idx - in_start;
        // Build left subtree
        build(in_start, root_idx - 1, post_start, post_start + left_size - 1);
        // Build right subtree
        build(root_idx + 1, in_end, post_start + left_size, post_end - 1);
    };

    build(0, inorder.size() - 1, 0, postorder.size() - 1);
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> inorder(n), postorder(n);
    for (auto& e : inorder) cin >> e;
    for (auto& e : postorder) cin >> e;

    buildTree(inorder, postorder);

    return 0;
}

#endif
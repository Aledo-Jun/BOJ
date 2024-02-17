//
// Created by june0 on 2024-02-13.
//
#include <vector>
#include <unordered_map>
#include <functional>

using namespace std;

#ifndef BOJ_TREE_HPP
#define BOJ_TREE_HPP

namespace Utils
{
namespace Tree
{
    template<typename T>
    using graph = std::vector<std::vector<std::pair<int,T>>>;

    vector<int> getPreorder(const vector<int>& inorder, const vector<int>& postorder) {
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

    class LCA {
    private:
        const int MAX_N = 100001; // Adjust this based on your maximum number of nodes

        std::vector<int> depth; // Depth of each node
        std::vector<std::vector<int>> parent; // Binary Lifting table
        graph<int> adj; // Adjacency list of the tree, Assume that nodes are 1-indexed

    public:
        LCA(const graph<int>& adj) : adj(adj) {
            make_tree(1, 0, 0);
        }

        void make_tree(int u, int p, int d) {
            depth[u] = d;
            parent[u][0] = p;
            for (int i = 1; i < 20; i++) {
                parent[u][i] = parent[parent[u][i - 1]][i - 1];
            }
            for (const auto& [v, w]: adj[u]) {
                if (v != p) {
                    make_tree(v, u, d + 1);
                }
            }
        }

        int lca(int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);
            for (int i = 19; i >= 0; i--) {
                if (depth[u] - (1 << i) >= depth[v]) {
                    u = parent[u][i];
                }
            }
            if (u == v) return u;
            for (int i = 19; i >= 0; i--) {
                if (parent[u][i] != parent[v][i]) {
                    u = parent[u][i];
                    v = parent[v][i];
                }
            }
            return parent[u][0];
        }
    };

} // namespace Tree
} // namespace Utils

#endif //BOJ_TREE_HPP

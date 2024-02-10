#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

/*
 * Algorithm to find the LIS(Longest Increasing Subsequence)
 */
namespace LIS
{
    template<typename T, typename Iter, typename Container>
    Container _lis(const Iter &left, const Iter &right) {
        // from left to right - 1
        int n = std::distance(left, right);
        std::vector<int> idx(n);
        std::vector<T> lis;

        for (int i = 0; i < n; i++) {
            if (lis.size() == 0 || lis.back() < *(left + i)) {
                lis.emplace_back(*(left + i));
                idx[i] = lis.size() - 1;
            } else {
                auto it = std::lower_bound(lis.begin(), lis.end(), *(left + i));
                *it = *(left + i);
                idx[i] = std::distance(lis.begin(), it);
            }
        }

        std::vector<T> res;
        int j = lis.size() - 1;
        for (int i = n - 1; i >= 0; i--) {
            if (idx[i] == j){
                j--;
                res.emplace_back(*(left + i));
            }
        }
        std::reverse(res.begin(), res.end());

        return Container(res);
    }

    template<typename Container>
    Container lis(const Container& v){
        return _lis<typename Container::value_type,
                    typename Container::const_iterator,
                    Container>(v.begin(), v.end());
    }
}// End namespace LIS

/*
 * Algorithm to find the Lowest Common Ancestor of two given nodes
 */
namespace LCA {
    const int MAX_N = 100001; // Adjust this based on your maximum number of nodes

    std::vector<int> depth; // Depth of each node
    std::vector<std::vector<int>> parent; // Binary Lifting table
    std::vector<std::map<int,int>> adj; // Adjacency map of the tree

    void make_tree(int v, int p, int d) {
        depth[v] = d;
        parent[v][0] = p;
        for (int i = 1; i < 20; i++) {
            parent[v][i] = parent[parent[v][i - 1]][i - 1];
        }
        for (auto u : adj[v]) {
            if (u.first != p) {
                make_tree(u.first, v, d + 1);
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
}// End namespace LCA
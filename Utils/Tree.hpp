//
// Created by june0 on 2024-02-13.
//
#include <vector>
#include <map>
#include <functional>
#include <cmath>

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
        int MAX_BIT;

        std::vector<int> depth; // Depth of each node
        std::vector<std::vector<int>> parent; // Binary Lifting table
        graph<int> adj; // Adjacency list of the tree, Assume that nodes are 1-indexed

    public:
        LCA(const graph<int>& g) : adj(g) {
            int sz = (int) adj.size();
            MAX_BIT = std::ceil(std::log2(sz));
            depth.resize(sz);
            parent.resize(sz, vector<int>(MAX_BIT));
            make_tree(1, 0, 0);
        }

        void make_tree(int u, int p, int d) {
            depth[u] = d;
            parent[u][0] = p;
            for (int i = 1; i < MAX_BIT; i++) {
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
            for (int i = MAX_BIT - 1; i >= 0; i--) {
                if (depth[u] - (1 << i) >= depth[v]) {
                    u = parent[u][i];
                }
            }
            if (u == v) return u;
            for (int i = MAX_BIT - 1; i >= 0; i--) {
                if (parent[u][i] != parent[v][i]) {
                    u = parent[u][i];
                    v = parent[v][i];
                }
            }
            return parent[u][0];
        }
    }; // class LCA


/**
 * Splay tree implementation
 * @tparam T Value type
 */
    template<typename T>
    class SplayTree {
        struct Node {
            Node *l, *r, *p;
            T key; // value stored in the node
            int cnt; // # of nodes in the subtree
            bool flip;

            /* Add more variables if needed */

            Node() : l(nullptr), r(nullptr), p(nullptr), key(T(0)), cnt(1), flip(false) {}
            explicit Node(T key) : l(nullptr), r(nullptr), p(nullptr), key(key), cnt(1), flip(false) {
                /* Initialize extra variables */
            }
        } *tree;

        // modify if needed
        void update(Node *x) {
            x->cnt = 1;
            if (x->l) x->cnt += x->l->cnt;
            if (x->r) x->cnt += x->r->cnt;
        }

        void rotate(Node *x) {
            Node *p = x->p;
            Node *b;
            if (x == p->l) {
                p->l = b = x->r;
                x->r = p;
            } else {
                p->r = b = x->l;
                x->l = p;
            }
            x->p = p->p;
            p->p = x;
            if (b) b->p = p;
            (x->p ? p == x->p->l ? x->p->l : x->p->r : tree) = x;

            update(p);
            update(x);
        }

        void push(Node *x) {
            if (x->flip) {
                swap(x->l, x->r);
                if (x->l) x->l->flip ^= 1;
                if (x->r) x->r->flip ^= 1;
                x->flip = false;
            }
        }

        void splay(Node *x) {
            while (x->p) {
                Node *p = x->p;
                Node *g = p->p;

                if (g) push(g);
                push(p);push(x);

                if (g) rotate((x == p->l) == (p == g->l) ? p : x);
                rotate(x);
            }
        }

    public:
        template<typename Iter>
        SplayTree(const Iter& s, const Iter& e) {
            Node *p = tree = new Node(0);
            for (auto it = s; it != e; it++) {
                p->r = new Node(*it);
                p->r->p = p;
                p = p->r;
            }
            p->r = new Node(0);
            p->r->p = p;
            p = p->r;

            while (p) {
                update(p);
                p = p->p;
            }
        }

        //
        /* Key Based Methods */
        // NOTE: No duplicates are allowed
        /**
         * Insert a new node with the given key
         * @param key the key value to insert
         */
        void insert(T key) {
            Node *p = tree, **pp;
            if (!p) {
                Node *x = new Node(key);
                tree = x;
                return;
            }
            while (true) {
                if (key == p->key) return; // no duplicate allowed
                if (key < p->key) {
                    if (!p->l) {
                        pp = &p->l;
                        break;
                    }
                    p = p->l;
                } else {
                    if (!p->r) {
                        pp = &p->r;
                        break;
                    }
                    p = p->r;
                }
            }
            Node *x = new Node(key);
            *pp = x;  // p -> x
            x->p = p; // x -> p

            splay(x); // Crucial!
        }

        /**
         * The node with the given key becomes the root node after the function call
         * @param key the key value to find
         * @return true if found, false otherwise
         */
        bool find(T key) {
            Node *p = tree;
            if (!p) return false;
            while (p) {
                if (key == p->key) break;
                if (key < p->key) {
                    if (!p->l) break;
                    p = p->l;
                } else {
                    if (!p->r) break;
                    p = p->r;
                }
            }
            splay(p);
            return key == p->key;
        }

        /**
         * Erase the node with the given key
         */
        void erase(T key) {
            if (!find(key)) return;
            Node *p = tree;
            if (p->l) {
                if (p->r) {
                    tree = p->l;
                    tree->p = nullptr;

                    Node *x = tree;
                    while (x->r) x = x->r;
                    x->r = p->r;
                    p->r->p = x;
                    splay(x);
                    delete p;
                    return;
                }
                tree = p->l;
                tree->p = nullptr;
                delete p;
                return;
            }
            if (p->r) {
                tree = p->r;
                tree->p = nullptr;
                delete p;
                return;
            }
            delete p;
            tree = nullptr;
        }

        //
        /* Index Based Methods */
        // NOTE: 1-based indexing
        /**
         * Make the root node to be the k-th
         */
        void find_kth(int k) {
            Node *x = tree; push(x);
            while (true) {
                while (x->l && x->l->cnt > k) {
                    x = x->l; push(x);
                }
                if (x->l) k -= x->l->cnt;
                if (!k--) break;
                x = x->r; push(x);
            }
            splay(x);
        }

        /**
         * Make the tree->r->l to represent the given interval [l,r]
         */
        void interval(int l, int r) {
            find_kth(l - 1);
            auto *p = tree;
            tree = p->r;
            tree->p = nullptr;
            find_kth(r - l + 1);
            p->r = tree;
            tree->p = p;
            tree = p;
        }

        /**
         * Insert a new node with the key of val into the given pos
         */
        void insert(int pos, T val) {
            find_kth(pos);
            auto *p = tree, *x = new Node(val);
            x->p = p;
            p->l->p = x;
            x->l = p->l;
            p->l = x;
            splay(x);
        }

        /**
         * Erase the node at the given pos
         */
        void erase_at(int pos) {
            interval(pos, pos);
            auto *x = tree->r->l;
            x->p->l = nullptr;
            splay(x->p);
            delete x;
        }

        /**
         * Update the node's key at pos to val
         */
        void update(int pos, T val) {
            find_kth(pos);
            tree->key = val;
            update(tree);
        }

        /**
         * Flip the interval[l, r]
         */
        void flip(int l, int r) {
            interval(l, r);
            tree->r->l->flip ^= 1;
        }

        /**
         * Cyclic shift the range[l, r] k steps
         * @param k positive to right, negative to left
         */
        void shift(int l, int r, int k) {
            interval(l, r);
            k %= r - l + 1;
            if (k < 0) k += r - l + 1;
            if (k) flip(l, r), flip(l, l + k - 1), flip(l + k, r);
        }

        T operator[](int idx) {
            find_kth(idx);
            return tree->key;
        }

        T query(int l, int r, int k) {
            interval(l, r);
            // Do something within the interval
        }
    }; // class SplayTree

    array<vector<int>,2> EulerTour(const graph<int>& g) {
        int n = (int) g.size() - 1;
        vector<int> S(n + 1), T(n + 1);

        int pv = 0;
        vector<bool> visited(n + 1, false);
        function<void(int)> dfs = [&](int u) -> void {
            S[u] = ++pv;
            visited[u] = true;
            for (const auto& [v, _]: g[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                dfs(v);
            }
            T[u] = pv;
        };

        dfs(1);

        return {S, T};
    }

    /**
     * @brief Heavy Light Decomposition to perform a query on a path in a tree
     */
    class HLD {
    private:
        vector<int> sz,     // size of the subtree
                    depth,  // depth of the node
                    parent, // parent of the node
                    top,    // top of the chain the node belongs to
                    S, T;   // Euler Tour

        int root;
        graph<int> adj;     // adjacent list for original tree
        vector<vector<int>> g;

        vector<bool> visited;
        void dfs(int u) { // construct g
            visited[u] = true;
            for (const auto& [v, _]: adj[u]) {
                if (visited[v]) continue;
                visited[v] = true;
                g[u].emplace_back(v);
                dfs(v);
            }
        }

        // construct sz, depth, parent, and make the nodes adjacent if they belong to the same chain
        void dfs1(int u) {
            sz[u] = 1;
            for (auto& v : g[u]) {
                depth[v] = depth[u] + 1;
                parent[v] = u;
                dfs1(v);
                sz[u] += sz[v];
                if (sz[v] > sz[g[u][0]]) std::swap(v, g[u][0]);
            }
        }

        int pv = 0;
        // construct S, T, and top
        void dfs2(int u) {
            S[u] = ++pv;
            for (const auto& v: g[u]) {
                top[v] = v == g[u][0] ? top[u] : v;
                dfs2(v);
            }
            T[u] = pv;
        }

        /* Add something to Utilize the HLD e.g. SegTree */

    public:
        explicit
        HLD(const graph<int>& g, int root = 1) : adj(g), root(root) {
            int n = (int) g.size();
            sz.resize(n);
            depth.resize(n);
            parent.resize(n);
            top.resize(n);
            S.resize(n); T.resize(n);
            this->g.resize(n);
            visited.resize(n);
            dfs(root), dfs1(root), dfs2(root);

            // initialize additional variables
        }

        void path_query(int x, int y) {
            while (top[x] ^ top[y]) {
                if (depth[top[x]] < depth[top[y]]) swap(x, y);
                int st = top[x];
                // perform query from S[st] to S[x]
                x = parent[st];
            }
            if (depth[x] > depth[y]) swap(x, y);
            // perform query from S[x] to S[y]
        }
    }; // class HLD

    /**
     * @brief Centroid Tree implementation
     */
    class CentroidTree {
        int n, root;
        int MAX_BIT;
        graph<int> g;
        vector<int> sz,    // size of the subtree
                    depth, // depth of the node
                    dist,  // distance from the initial root
                    tree,  // centroid tree(tree[i] = parent of i at the centroid tree)
                    S, T, E;  // Euler Tour
        vector<vector<int>> parent;

        int pw = 0;
        int dfs(int u, int p) {
            sz[u] = 1;
            E[++pw] = u;
            S[u] = pw;
            for (const auto& [v, w]: g[u]) {
                if (v == p) continue;
                depth[v] = depth[u] + 1;
                dist[v] = dist[u] + w;
                parent[v][0] = u;
                for (int i = 1; i < MAX_BIT; i++) {
                    parent[v][i] = parent[parent[v][i - 1]][i - 1];
                }
                sz[u] += dfs(v, u);
                E[++pw] = u;
            }
            return sz[u];
        }

        vector<int> pw2, lg2;
        vector<vector<pair<int,int>>> ST;
        void lca_prepare(){
            pw2.resize(MAX_BIT);
            pw2[0] = 1;
            for (int i = 1; i < MAX_BIT; i++) pw2[i] = pw2[i - 1] << 1;

            lg2.resize(n * 2);
            fill(all(lg2), -1);
            for (int i = 0; i < MAX_BIT; i++) if (pw2[i] < n * 2) lg2[pw2[i]] = i;
            for (int i = 1; i < n * 2; i++) if (lg2[i] == -1) lg2[i] = lg2[i - 1];

            ST.resize(MAX_BIT, vector<pair<int,int>>(n * 2));
            for (int i = 1; i < n * 2; i++) ST[0][i] = {depth[E[i]], E[i]};

            for(int k = 1; k < MAX_BIT; k++) {
                for (int i = 1; i < n * 2; i++) {
                    if (i + pw2[k - 1] > n * 2) continue;
                    ST[k][i] = min(ST[k - 1][i], ST[k - 1][i + pw2[k - 1]]);
                }
            }
        }

        int lca(int u, int v) {
            int l = S[u], r = S[v];
            if (l > r) swap(l, r);
            int k = lg2[r - l + 1];
            return min(ST[k][l], ST[k][r - pw2[k] + 1]).second;
        }

        int get_dist(int u, int v) {
            return dist[u] + dist[v] - 2 * dist[lca(u, v)];
        }

        int get_centroid(int u) {
            for (const auto& [v, w]: g[u]) {
                if (sz[u] >> 1 < sz[v] && sz[v] < sz[u]) {
                    sz[u] -= sz[v];
                    sz[v] += sz[u];
                    return get_centroid(v);
                }
            }
            return u;
        }

        void build_centroid_tree(int u, int p = -1) {
            u = get_centroid(u);

            if (p == -1) tree[u] = u;
            else tree[u] = p;

            for (const auto& [v, _]: g[u])
                if (sz[v] < sz[u])
                    build_centroid_tree(v, u);
        }

    public:

        explicit
        CentroidTree(const graph<int>& g, int root = 1) : g(g), n((int)g.size()), root(root) {
            sz.resize(n, 0);
            depth.resize(n, 0);
            dist.resize(n, 0);
            S.resize(n), T.resize(n), E.resize(n * 2);
            tree.resize(n);
            MAX_BIT = std::ceil(std::log2(n));
            parent.resize(n, vector<int>(MAX_BIT));


            dfs(root, -1);
            lca_prepare();
            build_centroid_tree(root);

        }

        void query_template(int u) {
            // climb up the centroid tree and update ancestor's set
            for (int v = u, prev = u;; prev = v, v = tree[v]) {

                if (tree[v] == v) break;
            }
        }
    }; // class CentroidTree

} // namespace Tree
} // namespace Utils

#endif //BOJ_TREE_HPP

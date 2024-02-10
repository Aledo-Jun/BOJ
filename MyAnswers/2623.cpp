//
// Created by june0 on 2024-02-10.
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

namespace Utils
{
    namespace Math {
        constexpr long long safe_mod(long long x, unsigned long long m) {
            x = (long long)(x % m);
            if (x < 0) x = (long long)(x + m);
            return x;
        }

        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
            a = safe_mod(a, b);
            if (a == 0) return {b, 0};

            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t) {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u;

                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            if (m0 < 0) m0 += b / s;
            return {s, m0};
        }

        constexpr unsigned pow_mod_constexpr(long long a, unsigned long long n, unsigned long long MOD) {
            if (MOD == 1) return 0;
            unsigned long long _a = safe_mod(a, MOD);
            unsigned long long res = 1;
            while (n) {
                if (n & 1) res = (res * _a) % MOD;
                n >>= 1;
                _a = (_a * _a) % MOD;
            }
            return res;
        }

        // NOTE : m must be prime
        constexpr unsigned primitive_root_constexpr(unsigned long long m) {
            // some popular roots
            if (m == 2) return 1;
            if (m == 786'433) return 10;
            if (m == 167'772'161) return 3;
            if (m == 469'762'049) return 3;
            if (m == 754'974'721) return 11;
            if (m == 998'244'353) return 3;
            if (m == 9'223'372'036'972'216'319ull) return 3;

            // find divisors of m - 1
            unsigned divs[20] = {};
            divs[0] = 2;
            unsigned cnt = 1;
            unsigned x = (m - 1) / 2;
            while (x % 2 == 0) x /= 2;
            for (int i = 3; (long long) (i) * i <= x; i += 2) {
                if (x % i == 0) {
                    divs[cnt++] = i;
                    while (x % i == 0) {
                        x /= i;
                    }
                }
            }
            if (x > 1) {
                divs[cnt++] = x;
            }
            // find the first g s.t. there exist some d in divs, g^(m - 1)/d == 1 mod m
            for (int g = 2;; g++) {
                bool ok = true;
                for (int i = 0; i < cnt; i++) {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                        ok = false;
                        break;
                    }
                }
                if (ok) return g;
            }
        }

        template<unsigned long long m> constexpr unsigned primitive_root = primitive_root_constexpr(m);

        // Structure for fast modular multiplication
        struct Barrett {
            unsigned MOD;
            unsigned long long inv_MOD;

            explicit Barrett(unsigned m) : MOD(m), inv_MOD((unsigned long long) (-1) / MOD + 1) {}

            [[nodiscard]]
            unsigned mod() const { return MOD; }

            [[nodiscard]]
            unsigned multiply(unsigned a, unsigned b) const {
                unsigned long long res1 = a;
                res1 *= b;
                unsigned long long res2 = ((unsigned __int128) (res1) * inv_MOD) >> 64;
                res2 *= MOD;
                return (res1 - res2 + (res1 < res2 ? MOD : 0));
            }
        };

        std::vector<int> prime_sieve(int n) {
            std::vector<bool> is_prime = std::vector<bool>(n + 1, true);
            is_prime[0] = is_prime[1] = false;
            for (int i = 2; i * i <= n; i++) {
                if (is_prime[i]) {
                    for (int j = i * i; j <= n; j += i) {
                        is_prime[j] = false;
                    }
                }
            }
            std::vector<int> sieve;
            for (int i = 3; i <= n; i++) {
                if (is_prime[i])
                    sieve.push_back(i);
            }
            return sieve;
        }
    } // namespace Math

    namespace TypeTraits {
        template<typename T>
        using is_signed_int =
                typename std::conditional_t<std::is_integral_v<T> && std::is_signed_v<T>,
                        std::true_type,
                        std::false_type>;

        template<typename T>
        using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

        template<typename T>
        using is_unsigned_int =
                typename std::conditional_t<std::is_integral_v<T> && std::is_unsigned_v<T>,
                        std::true_type,
                        std::false_type>;

        template<typename T>
        using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

        struct modint_base {};

        template<typename T>
        using is_modint = std::is_base_of<modint_base, T>;
        template<typename T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;
    } // namespace TypeTraits

    namespace Modulo {
        using namespace TypeTraits;
        using namespace Math;

        /**
         * an Integer type that modular arithmetic is automatically applied
         * @tparam MOD the modulus that will be applied to the value
         */
        template<unsigned long long MOD,
                enable_if_t<(MOD >= 1)> * = nullptr>
        class ModInt : modint_base {
            using mint = ModInt;

        private:
            unsigned long long _v;

            static constexpr unsigned long long _umod() { return MOD; }

        public:
            static constexpr unsigned long long mod() { return MOD; }

            [[nodiscard]]
            unsigned long long value() const { return _v; }

            [[nodiscard]]
            mint pow(unsigned long long n) const {
                mint base = *this, res = 1;
                while (n > 0) {
                    if (n & 1) res *= base;
                    base *= base;
                    n >>= 1;
                }
                return res;
            }

            [[nodiscard]]
            mint inv() const {
                return pow(_umod() - 2);
            }

            ////////////////////////////////////////////////////////////////
            // Constructors
            ////////////////////////////////////////////////////////////////

            ModInt() : _v(0) {}

            ModInt(const mint &other) : _v(other._v) {}

            template<typename T,
                    is_signed_int_t<T> * = nullptr>
            /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
                __int128 x = value % _umod();
                if (x < 0) x += _umod();
                _v = x;
            }

            template<typename T,
                    is_unsigned_int_t<T> * = nullptr>
            /* implicit */ ModInt(T value) { // NOLINT(google-explicit-constructor)
                _v = value % _umod();
            }

            ////////////////////////////////////////////////////////////////
            // Operators
            ////////////////////////////////////////////////////////////////

            /* Assignment operators */
            mint &operator=(const mint &other) {
                _v = other._v;
                return *this;
            }

            mint &operator+=(const mint &rhs) {
                unsigned __int128 tmp = _v;
                tmp += rhs._v;
                _v = tmp % _umod();
                return *this;
            }

            mint &operator-=(const mint &rhs) {
                __int128 tmp = _v;
                tmp -= rhs._v;
                if (tmp < 0) tmp += _umod();
                _v = tmp % _umod();
                return *this;
            }

            mint &operator*=(const mint &rhs) {
                unsigned __int128 tmp = _v;
                tmp *= rhs._v;
                _v = tmp % _umod();
                return *this;
            }

            mint &operator/=(const mint &rhs) {
                return *this = *this * rhs.inv();
            }


            /* Binary operators */
            friend mint operator+(const mint &lhs, const mint &rhs) {
                return mint(lhs) += rhs;
            }

            friend mint operator-(const mint &lhs, const mint &rhs) {
                return mint(lhs) -= rhs;
            }

            friend mint operator*(const mint &lhs, const mint &rhs) {
                return mint(lhs) *= rhs;
            }

            friend mint operator/(const mint &lhs, const mint &rhs) {
                return mint(lhs) /= rhs;
            }


            /* Unary operators */
            mint operator+() { return *this; }

            mint operator-() { return mint() - *this; }


            /* Increment/Decrement operators */
            mint &operator++() {
                _v++;
                if (_v == _umod()) _v = 0;
                return *this;
            }

            mint &operator--() {
                if (_v == 0) _v = _umod();
                _v--;
                return *this;
            }

            mint operator++(int) {
                mint res = *this;
                ++*this;
                return res;
            }

            mint operator--(int) {
                mint res = *this;
                --*this;
                return res;
            }

            /* Conditional operators */
            bool operator==(const mint &other) { return _v == other._v; }

            bool operator==(const unsigned long long &other) { return _v == other; }

            bool operator!=(const mint &other) { return _v != other._v; }

            bool operator!=(const unsigned long long &other) { return _v != other; }

            /* I/O operator */
            friend std::ostream &operator<<(std::ostream &out, const mint &m) {
                out << m._v;
                return out;
            }

            friend std::istream &operator>>(std::istream &in, mint &m) {
                in >> m._v;
                m._v %= _umod();
                return in;
            }
        };

    } // namespace Modulo

    namespace SegTree {
/**
 * Segment Tree that contains the result of a query over the range.
 * @tparam T type of elements
 * @tparam func function object to be called to perform the query
 * @tparam updating_func function object to be called to update the containing element
 */
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

            T init(int node, int left, int right) {
                if (left == right) return tree[node] = arr[left];

                int mid = (left + right) >> 1;
                auto left_result = init(node << 1, left, mid);
                auto right_result = init(node << 1 | 1, mid + 1, right);
                tree[node] = f(left_result, right_result);

                return tree[node];
            }

            /**
             * Update the tree as a result of performing <i>updating_func</i> with <i>value</i> to the arr[idx]
             * @param node current node index in the tree
             * @param start starting index that the current node is covering
             * @param end ending index that the current node is covering
             * @param idx index of array that updating is required
             * @param value the value to be used for performing <i>updating_func</i> to the arr[idx]
             */
            void _update(int node, int start, int end, int idx, T value) {
                if (idx < start || end < idx) return;

                if (start == end) {
                    tree[node] = updating_f(tree[node], value);
                } else {
                    int mid = (start + end) >> 1;
                    _update(node << 1, start, mid, idx, value);
                    _update(node << 1 | 1, mid + 1, end, idx, value);
                    tree[node] = f(tree[node << 1], tree[node << 1 | 1]);
                }
            }


            /**
             * Find the result of @p func over the array elements in range [left, right]
             * @param node current node index in the tree
             * @param start starting index that the current node is covering
             * @param end ending index that the current node is covering
             * @param left starting index of performing @p func
             * @param right ending index of performing @p func
             * @return the result of @p func over the array elements in range [left, right]
             */
            T _query(int node, int start, int end, int left, int right) {
                if (end < left || right < start) return default_query;
                if (left <= start && end <= right) return tree[node];

                int mid = (start + end) >> 1;
                auto left_result = _query(node << 1, start, mid, left, right);
                auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
                return f(left_result, right_result);
            }

        public:
            /**
             * Constructor for a segment tree
             * @param v Array that the segment tree will be constructed from
             * @param default_query The result of query that doesn't affect the other query result when performed <i>func</i> with
             */
            explicit SegTree(const vector<T> &v, T default_query = 0) : default_query(std::move(default_query)) {
                arr = v;
                height = (int) ceil(log2(v.size()));
                size = (1 << (height + 1));
                tree.resize(size + 1);
                init(1, 0, v.size() - 1);
            }

            void update(int idx, T value) {
                _update(1, 0, arr.size() - 1, idx, value);
            }

            T query(int left, int right) {
                return _query(1, 0, arr.size() - 1, left, right);
            }

        }; // class SegTree
    } // namespace SegTree

    namespace DisjointSet {
        template<bool Union_By_Rank = true>
        class DisjointSet {
        private:
            const int def_sz = 1001;
            vector<int> parent;
            vector<int> rank;
        public:
            DisjointSet() {
                parent.assign(def_sz, 0);
                rank.assign(def_sz, 0);
            }

            explicit DisjointSet(int sz) {
                parent.assign(sz, 0);
                for (int i = 0; i < sz; i++)
                    parent[i] = i;
                rank.assign(sz, 0);
            }

            // find the root of x
            int find(int x) {
                if (x != parent[x]) {
                    parent[x] = find(parent[x]);
                }
                return parent[x];
            }

            // Union By Rank,
            // i.e. the parent relation could be relational(not specified).
            template<std::enable_if_t<Union_By_Rank>* = nullptr>
            void uni(int x, int y) {
                int rootx = find(x);
                int rooty = find(y);

                if (rootx != rooty) {
                    if (rank[rootx] < rank[rooty])
                        parent[rootx] = rooty;
                    else if (rank[rootx] > rank[rooty])
                        parent[rooty] = rootx;
                    else {
                        parent[rooty] = rootx;
                        rank[rootx]++;
                    }
                }
            }

            // Dangle y to the root of x
            void uni(int x, int y) {
                int rootx = find(x);
                int rooty = find(y);

                if (rootx != rooty)
                    parent[rooty] = rootx;
            }
        }; // class DisjointSet
    } // namespace DisjointSet

    namespace Graph {
        template<typename T> using graph = vector<vector<pair<int, T>>>;
        template<typename T> using matrix = vector<vector<T>>;
        const int INF = INT_MAX;

        vector<int> dijkstra(const graph<int> &g, int start) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            vector<int> dist(g.size(), INF);
            pq.emplace(0, start);
            dist[start] = 0;
            while (!pq.empty()) {
                int distance = pq.top().first;
                int u = pq.top().second;
                pq.pop();

                if (distance > dist[u]) continue;

                for (const auto &[v, w]: g[u]) {
                    if (distance + w < dist[v]) {
                        dist[v] = distance + w;
                        pq.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        }

        vector<int> bellmanFord(const graph<int> &g, int start) {
            int n = (int) g.size() - 1;
            vector<int> dist(n + 1, INF);
            dist[start] = 0;

            for (int i = 1; i < n; i++) {
                for (int u = 1; u <= n; u++) {
                    for (const auto &[v, w]: g[u]) {
                        if (dist[u] != INF && dist[u] + w < dist[v])
                            dist[v] = dist[u] + w;
                    }
                }
            }
            return dist;
        }

/**
 * Verify whether the graph has a negative cycle or not when called <i>after</i> calling bellmanFord
 */
        bool is_there_negative_cycle(const graph<int> &g, const vector<int> &dist) {
            int n = (int) g.size() - 1;
            for (int u = 1; u <= n; u++) {
                if (g[u].empty()) continue;
                for (const auto &[v, w]: g[u]) {
                    if (dist[u] != INF && dist[u] + w < dist[v])
                        return true;
                }
            }
            return false;
        }

        matrix<int> floydWarshall(const graph<int> &g) {
            int n = (int) g.size() - 1;
            matrix<int> res(n + 1, vector<int>(n + 1, INT_MAX));
            for (int i = 1; i <= n; i++) {
                for (const auto &e: g[i]) {
                    res[i][e.first] = e.second;
                }
            }
            for (int k = 1; k <= n; k++) {
                for (int i = 1; i <= n; i++) {
                    for (int j = 1; j <= n; j++) {
                        res[i][j] = min(res[i][j], res[i][k] + res[k][j]);
                    }
                }
            }
            return res;
        }

        void dfs_for_topological_order(graph<int> &g, int u, vector<bool> &visited, vector<int> &order) {
            if (visited[u]) return;
            visited[u] = true;

            for (const auto &[v, w]: g[u]) {
                dfs_for_topological_order(g, v, visited, order);
            }

            order.emplace_back(u);
        }

        vector<int> topological_order_dfs(graph<int> &g) {
            int n = (int) g.size() - 1;
            vector<bool> visited(n + 1, false);
            vector<int> result;

            for (int i = 1; i <= n; i++)
                dfs_for_topological_order(g, i, visited, result);

            std::reverse(result.begin(), result.end());
            return result;
        }

        vector<int> topological_order_degree(graph<int> &g) {
            int n = (int) g.size() - 1;
            vector<int> in_degree(g.size(), 0);
            vector<int> result;
            queue<int> q;
            for (int u = 1; u <= n; u++){
                for (const auto&[v, w] : g[u])
                    in_degree[v]++;
            }
            for (int u = 1; u <= n; u++){
                if (in_degree[u] == 0) q.emplace(u);
            }

            while (!q.empty()){
                int u = q.front(); q.pop();
                result.emplace_back(u);

                for (const auto&[v, w] : g[u]){
                    in_degree[v]--;
                    if (in_degree[v] == 0) q.emplace(v);
                }
            }

            return result;
        }

        struct Edge {
            int u, v, w;

            Edge(int u, int v, int w) : u(u), v(v), w(w) {};

            bool operator<(const Edge &other) const {
                return w < other.w;
            }

            bool operator>(const Edge &other) const {
                return w > other.w;
            }
        };

        int minimumSpanningTree(const vector<Edge> &g) {
            priority_queue<Edge, vector<Edge>, greater<>> minHeap(g.begin(), g.end());

            Utils::DisjointSet::DisjointSet ds((int)g.size() + 1);

            int res = 0;
            while (!minHeap.empty()) {
                auto e = minHeap.top();
                minHeap.pop();
                if (ds.find(e.u) != ds.find(e.v)) {
                    ds.uni(e.u, e.v);
                    res += e.w;
                }
            }
            return res;
        }

        void dfs_scc(graph<int> &g, int u, vector<bool> &visited, stack<int> &finishing) {
            if (visited[u]) return;
            visited[u] = true;

            for (const auto &e: g[u]) {
                dfs_scc(g, e.first, visited, finishing);
            }
            finishing.emplace(u);
        }

        void inv_dfs_scc(graph<int> &g, int u, vector<bool> &visited, vector<int> &curr_scc) {
            for (const auto &e: g[u]) {
                if (visited[e.first]) continue;
                visited[e.first] = true;
                inv_dfs_scc(g, e.first, visited, curr_scc);
            }
            curr_scc.emplace_back(u);
        }

/**
 * Algorithm to find the <b>SCC(Strongly Connected Components)</b>
 */
        matrix<int> scc(graph<int> &g, graph<int> &g_r) {
            vector<bool> visited(g.size(), false);
            stack<int> finishing_time;
            for (int i = 1; i < g.size(); i++) {
                if (visited[i]) continue;
                dfs_scc(g, i, visited, finishing_time);
            }

            visited.assign(g.size(), false);
            matrix<int> res;
            vector<int> curr_scc;
            while (!finishing_time.empty()) {
                int u = finishing_time.top();
                finishing_time.pop();
                if (visited[u]) continue;
                visited[u] = true;
                inv_dfs_scc(g_r, u, visited, curr_scc);
                res.emplace_back(curr_scc);
                curr_scc.clear();
            }

            return res;
        }

    } // namespace Graph

} // namespace Utils

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    graph<int> g(n + 1);
    for (int i = 0; i < m; i++){
        int x; cin >> x;
        vector<int> v(x);
        for (int j = 0; j < x; j++) {
            cin >> v[j];
            for (int k = 0; k < j; k++)
                g[v[k]].emplace_back(v[j], 1);
        }
    }

    auto res = Utils::Graph::topological_order_degree(g);

    if (res.size() != n) cout << 0;
    else {
        for (const auto& e : res) cout << e << endl;
    }

    return 0;
}
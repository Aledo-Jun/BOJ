//
// Created by june0 on 2024-07-03.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
#define GRAPH_TYPE_DEFINED
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
#define MATRIX_TYPE_DEFINED
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

#ifdef ONLINE_JUDGE // Be careful if problem is about strings.
/**
 * Namespace for Fast I/O
 *
 * @class@b INPUT
 * class which can replace the cin
 *
 * @class@b OUTPUT
 * class which can replace the cout
 *
 * @Description
 * These classes use low-level i/o functions (@c fread()/mmap() for input, @c fwrite()/write() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char* p;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }
        INPUT() {
            struct stat st;
            fstat(0, &st);
            p = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, 0, 0);
        }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            return *p++;
        }

        char ReadChar() {
            char ret = _ReadChar();
            for (; IsBlank(ret); ret = _ReadChar());

            return ret;
        }

        template<class T>
        T ReadInt() {
            T ret = 0;
            char curr = _ReadChar();
            bool minus_flag = false;

            for (; IsBlank(curr); curr = _ReadChar());
            if (curr == '-') minus_flag = true, curr = _ReadChar();
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret = 10 * ret + (curr & 15);
            if (IsEnd(curr)) __END_FLAG__ = true;

            return minus_flag ? -ret : ret;
        }

        std::string ReadString() {
            std::string ret;
            char curr = _ReadChar();
            for (; IsBlank(curr); curr = _ReadChar());
            for (; !IsBlank(curr) && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (IsEnd(curr)) __END_FLAG__ = true;

            return ret;
        }

        double ReadDouble() {
            std::string ret = ReadString();
            return std::stod(ret);
        }

        std::string getline() {
            std::string ret;
            char curr = _ReadChar();
            for (; curr != '\n' && !IsEnd(curr); curr = _ReadChar())
                ret += curr;
            if (__GET_LINE_FLAG__) __END_FLAG__ = true;
            if (IsEnd(curr)) __GET_LINE_FLAG__ = true;

            return ret;
        }

        friend INPUT &getline(INPUT &in, std::string &s) {
            s = in.getline();
            return in;
        }
    } _in;
    /* End of Class INPUT */

    /* Class OUTPUT */
    class OUTPUT {
    private:
        char writeBuffer[SZ];
        int write_idx;
    public:
        ~OUTPUT() { Flush(); }

        explicit operator bool() const { return true; }

        void Flush() {
            write(1, writeBuffer, write_idx);
            write_idx = 0;
        }

        void WriteChar(char c) {
            if (write_idx == SZ) Flush();
            writeBuffer[write_idx++] = c;
        }

        template<class T>
        void WriteInt(T n) {
            int sz = GetSize(n);
            if (write_idx + sz >= SZ) Flush();
            if (n < 0) writeBuffer[write_idx++] = '-', n = -n;
            for (int i = sz; i-- > 0; n /= 10)
                writeBuffer[write_idx + i] = n % 10 | 48;
            write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        void WriteDouble(double d) {
            WriteString(std::to_string(d));
        }

        template<class T>
        int GetSize(T n) {
            int ret = 1;
            for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;

            return ret;
        }
    } _out;
    /* End of Class OUTPUT */

    /* Operators */
    INPUT &operator>>(INPUT &in, char &i) {
        i = in.ReadChar();
        return in;
    }

    INPUT &operator>>(INPUT &in, std::string &i) {
        i = in.ReadString();
        return in;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    INPUT &operator>>(INPUT &in, T &i) {
        if constexpr (std::is_floating_point_v<T>) i = in.ReadDouble();
        else if constexpr (std::is_integral_v<T>) i = in.ReadInt<T>();
        return in;
    }

    OUTPUT &operator<<(OUTPUT &out, char i) {
        out.WriteChar(i);
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, const std::string &i) {
        out.WriteString(i);
        return out;
    }

    template<class T, typename std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
    OUTPUT &operator<<(OUTPUT &out, T i) {
        if constexpr (std::is_floating_point_v<T>) out.WriteDouble(i);
        else if constexpr (std::is_integral_v<T>) out.WriteInt(i);
        return out;
    }

    /* Macros for convenience */
    #undef fastIO
    #define fastIO 1
    #define cin _in
    #define cout _out
    #define istream INPUT
    #define ostream OUTPUT
};
using namespace FastIO;
#endif

template<bool Union_By_Rank = true>
class DisjointSet {
private:
    const int def_sz = 1001;
    vector<int> parent;
    vector<int> rank;
public:
    template<std::enable_if_t<Union_By_Rank>* = nullptr>
    DisjointSet() {
        parent.assign(def_sz, 0);
        rank.assign(def_sz, 0);
    }

    DisjointSet() {
        parent.assign(def_sz, 0);
    }

    template<std::enable_if_t<Union_By_Rank>* = nullptr>
    DisjointSet(int sz) {
        parent.assign(sz, 0);
        iota(all(parent), 1);
        rank.assign(sz, 0);
    }

    DisjointSet(int sz) {
        parent.assign(sz, 0);
        for (int i = 0; i < sz; i++)
            parent[i] = i;
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

template<typename T>
struct Edge {
    int u, v;
    T w;

    Edge(int u, int v, T w) : u(u), v(v), w(w) {};

    bool operator<(const Edge &other) const {
        return w < other.w;
    }

    bool operator>(const Edge &other) const {
        return w > other.w;
    }
};

template<typename T>
int minimumSpanningTree(const std::vector<Edge<T>> &g, int sz) {
    std::priority_queue<Edge<T>, std::vector<Edge<T>>, std::greater<>> minHeap(g.begin(), g.end());

    DisjointSet<> ds(sz + 1);

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

int32_t main() {
    fastIO;
    int n, m, k;
    while (cin >> n >> m >> k) {
        if (n == 0) break;

        vector<Edge<int>> g, h;
        for (int i = 0; i < m; i++) {
            char c;
            int u, v;
            cin >> c >> u >> v;
            if (c == 'B') {
                g.emplace_back(u, v, 0);
                h.emplace_back(u, v, 0);
            } else {
                g.emplace_back(u, v, 1);
                h.emplace_back(u, v, -1);
            }
        }

        int mx = n - 1 - minimumSpanningTree(g, n);
        int mn = n - 1 + minimumSpanningTree(h, n);
        if (mn <= k && k <= mx) cout << 1 << endl;
        else cout << 0 << endl;
    }

    return 0;
}
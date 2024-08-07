//
// Created by june0 on 2024-07-20.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
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

template<typename T = int,
        typename Func = plus<T>,
        typename Inv_Func = minus<T>,
        typename Update_Func = plus<T>,
        const int MAX = (1 << 19) - 1> // ~ 500'000
class PersistentSegTree {
private:
    Func f;
    Inv_Func inv_f;
    Update_Func u;

    struct Node {
        T val;
        int l, r;

        Node() : val(0), l(0), r(0) {}
        Node(T val, int l, int r) : val(val), l(l), r(r) {}
    };

    int sz, ptr = 1;
    std::vector<int> roots;
    std::vector<Node> tree;

    void make_root() { // maybe not useful?
        roots.emplace_back(ptr++);
        tree.emplace_back();
    }

    void _update(int prev, int curr, int s, int e, int idx, T val) {
        tree[curr].val = u(tree[prev].val, val);

        if (s == e) return;

        int m = (s + e) >> 1;
        if (idx <= m) {
            tree[curr].l = ptr++;
            tree.emplace_back();
            tree[curr].r = tree[prev].r;
            _update(tree[prev].l, tree[curr].l, s, m, idx, val);
        } else {
            tree[curr].r = ptr++;
            tree.emplace_back();
            tree[curr].l = tree[prev].l;
            _update(tree[prev].r, tree[curr].r, m + 1, e, idx, val);
        }
    }

    T _query(int node, int s, int e, int l, int r) {
        if (e < l || r < s) return T();
        if (l <= s && e <= r) return tree[node].val;

        int m = (s + e) >> 1;
        return f(_query(tree[node].l, s, m, l, r), _query(tree[node].r, m + 1, e, l, r));
    }

    int _find_kth_in_path(int i, int j, int p, int pp, int s, int e, int k) {
        if (s == e) return s;
        int sum = tree[tree[i].l].val
                  + tree[tree[j].l].val
                  - tree[tree[p].l].val
                  - tree[tree[pp].l].val;
        int m = (s + e) >> 1;
        if (sum >= k) return _find_kth(tree[i].l, tree[j].l, tree[p].l, tree[pp].l, s, m, k);
        else return _find_kth(tree[i].r, tree[j].r, tree[p].r, tree[pp].r, m + 1, e, k - sum);
    }

    int _find_kth(int l, int r, int s, int e, int k) {
        if (s == e) return s; // Leaf node

        int l1 = tree[tree[l].l].val, l2 = tree[tree[l].r].val;
        int r1 = tree[tree[r].l].val, r2 = tree[tree[r].r].val;

        int left = r1 - l1;

        int m = (s + e) >> 1;
        if (left >= k) return _find_kth(tree[l].l, tree[r].l, s, m, k);
        else return _find_kth(tree[l].r, tree[r].r, m + 1, e, k - left);
    }

    int _find_kth(int node, int s, int e, int k) {
        if (s == e) return s; // Leaf node

        int left = tree[tree[node].l].val;

        int m = (s + e) >> 1;
        if (left >= k) return _find_kth(tree[node].l, s, m, k);
        else return _find_kth(tree[node].r, m + 1, e, k - left);
    }

    int _xor_query(int l, int r, int s, int e, int x) {
        if (s == e) return s;

        int left = tree[tree[r].l].val - tree[tree[l].l].val;
        int right = tree[tree[r].r].val - tree[tree[l].r].val;

        int m = (s + e) >> 1;
        // s = 0b{same}1(0..0), e = 0b{same}1(1..1)
        // e - s = 0b1..1 -> e - s + 1 = 0b10..0
        if ((e - s + 1) >> 1 & x && left || !right)
            return _xor_query(tree[l].l, tree[r].l, s, m, x);
        else return _xor_query(tree[l].r, tree[r].r, m + 1, e, x);
    }

public:
    // Construct the empty tree with size of n
    explicit PersistentSegTree(int n = MAX) : sz(n) {
        tree.reserve(20'000'000); // n + q * log n
        tree.emplace_back(); // padding for convenience

        roots.reserve(500'000);
        roots.emplace_back(ptr++); // Create NIL node
        tree.emplace_back(0, 1, 1);
    }

    int update(int idx, T val) {
        int prev = roots.back();
        roots.emplace_back(ptr++); // Create new root node
        tree.emplace_back();
        int curr = roots.back();

        _update(prev, curr, 0, sz - 1, idx, val);
        return (int) roots.size() - 1;
    }

    int update(int version, int idx, T val) {
        int prev = roots[version];
        roots.emplace_back(ptr++); // Create new root node
        tree.emplace_back();
        int curr = roots.back();

        _update(prev, curr, 0, sz - 1, idx, val);
        return (int) roots.size() - 1;
    }

    /**
     * Returns the query over the range [l,r] when updates with index [i,j] are performed.
     * @param i starting index of included updates
     * @param j ending index of included updates
     * @param l starting range of the query
     * @param r ending range of the query
     * @return querying result
     */
    T query(int i, int j, int l, int r) {
        if (i == 0) return _query(roots[j], 0, sz - 1, l, r);
        T res1 = _query(roots[i-1], 0, sz - 1, l, r);
        T res2 = _query(roots[j], 0, sz - 1, l, r);
        return inv_f(res2, res1);
    }

    T query(int i, int l, int r) {
        return _query(roots[i], 0, sz - 1, l, r);
    }

    /**
     * Find the k-th element on the path of i -> j in a tree
     * @param p lca of i, j
     * @param pp p's direct parent
     * @return
     */
    int find_kth_in_path(int i, int j, int p, int pp, int k) {
        return _find_kth_in_path(roots[i], roots[j], roots[p], roots[pp], 0, sz - 1, k);
    }

    int find_kth(int l, int r, int k) {
        if (l == 0) return _find_kth(roots[r], 0, sz - 1, k);
        return _find_kth(roots[l-1], roots[r], 0, sz - 1, k);
    }

    int find_kth(int version, int k) {
        return _find_kth(roots[version], 0, sz - 1, k);
    }

    void erase(int k) {
        while (k--) roots.pop_back();
    }

    int xor_query(int l, int r, int x) {
        return _xor_query(roots[l-1], roots[r], 0, (1 << 19) - 1, x);
    }
};

PersistentSegTree<int> pst;

int32_t main() {
    fastIO;
    int q;
    cin >> q;
    while (q--) {
        int cmd;
        cin >> cmd;
        switch (cmd) {
            case 1: {
                int x;
                cin >> x;
                pst.update(x, 1);
                break;
            }
            case 2: {
                int l, r, x;
                cin >> l >> r >> x;
                cout << pst.xor_query(l, r, x) << endl;
                break;
            }
            case 3: {
                int k;
                cin >> k;
                pst.erase(k);
                break;
            }
            case 4: {
                int l, r, x;
                cin >> l >> r >> x;
                cout << pst.query(l, r, 0, x) << endl;
                break;
            }
            case 5: {
                int l, r, x;
                cin >> l >> r >> x;
                cout << pst.find_kth(l, r, x) << endl;
                break;
            }
            default: assert(0);
        }
    }

    return 0;
}
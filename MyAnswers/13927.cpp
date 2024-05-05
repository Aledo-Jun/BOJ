//
// Created by june0 on 2024-05-05.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
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
 * These classes use low-level i/o functions (@c fread() for input, @c fwrite() for output)
 * so that they can read or write much faster than cin and cout. <br>
 * Several macros are defined for convenience of using them.
 *
 * @Author  <a href="https://blog.naver.com/jinhan814/222266396476">jinhan814</a>
 * @Date    2021-05-06
 */
namespace FastIO {
    constexpr int SZ = 1 << 20;

    /* Class INPUT */
    class INPUT {
    private:
        char readBuffer[SZ];
        int read_idx, next_idx;
        bool __END_FLAG__, __GET_LINE_FLAG__; // NOLINT
    public:
        explicit operator bool() const { return !__END_FLAG__; }

        static bool IsBlank(char c) { return c == ' ' || c == '\n'; }

        static bool IsEnd(char c) { return c == '\0'; }

        char _ReadChar() { // NOLINT
            if (read_idx == next_idx) {
                next_idx = (int)fread(readBuffer, sizeof(char), SZ, stdin);
                if (next_idx == 0) return 0;
                read_idx = 0;
            }
            return readBuffer[read_idx++];
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
            fwrite(writeBuffer, sizeof(char), write_idx, stdout);
            write_idx = 0;
        }

        void WriteChar(char c) {
            if (write_idx == SZ) Flush();
            writeBuffer[write_idx++] = c;
        }

        template<class T>
        void WriteInt(T total) {
            int sz = GetSize(total);
            if (write_idx + sz + 1 >= SZ) Flush();
            if (total < 0) writeBuffer[write_idx++] = '-', total = -total;
            for (int i = sz; i-- > 0; total /= 10)
                writeBuffer[write_idx + i] = total % 10 | 48;
            write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        void WriteDouble(double d) {
            WriteString(std::to_string(d));
        }

        template<class T>
        int GetSize(T total) {
            int ret = 1;
            for (total = total >= 0 ? total : -total; total >= 10; total /= 10) ret++;

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

const int MAX = 100'000;

template<typename T = int,
        typename Func = plus<T>,
        typename Inv_Func = minus<T>,
        typename Update_Func = plus<T>>
class PersistentSegTree {
private:
    Func f;
    Inv_Func inv_f;
    Update_Func u;

    struct Node {
        T val;
        int l, r;

        Node() : val(0), l(-1), r(-1) {}
        Node(T val, int l, int r) : val(val), l(l), r(r) {}
    };

    int sz, ptr = 0;
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
        if (e < l || r < s) return 0;
        if (l <= s && e <= r) return tree[node].val;

        int m = (s + e) >> 1;
        return f(_query(tree[node].l, s, m, l, r), _query(tree[node].r, m + 1, e, l, r));
    }

public:
    // Construct the empty tree with size of n
    explicit PersistentSegTree(int n = MAX + 5) : sz(n) {
        tree.reserve(1'000'000); // n + q * log n

        roots.emplace_back(ptr++); // Create root node
        tree.emplace_back();
        tree[0].l = tree[0].r = 0;
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
        T res1 = _query(roots[max(0, i - 1)], 0, sz - 1, l, r);
        T res2 = _query(roots[j], 0, sz - 1, l, r);
        return inv_f(res2, res1);
    }

    T query(int i, int l, int r) {
        return _query(roots[i], 0, sz - 1, l, r);
    }
};

using pst = PersistentSegTree<>;

pst PST;

class SSegTree {
    map<int,int> tree[4 * MAX]; // tree[node][val] = version
public:
    SSegTree() {
        for (int i = 1; i < 4 * MAX; i++) tree[i][0] = 0;
    }

    void update(int node, int s, int e, int idx, int last_pos, int curr_pos) {
        int m = (s + e) >> 1;

        if (node != 1) {
            int version = tree[node].rbegin()->second;
            tree[node][curr_pos] = PST.update(PST.update(version, last_pos, -1), curr_pos, 1);
        }
        if (s == e) return;
        if (idx <= m) update(node * 2, s, m, idx, last_pos, curr_pos);
        else update(node * 2 + 1, m + 1, e, idx, last_pos, curr_pos);
    }
    void update(int node, int s, int e, int idx, int curr_pos) {
        int m = (s + e) >> 1;

        if (node != 1) {
            int version = tree[node].rbegin()->second;
            tree[node][curr_pos] = PST.update(version, curr_pos, 1);
        }
        if (s == e) return;
        if (idx <= m) update(node * 2, s, m, idx, curr_pos);
        else update(node * 2 + 1, m + 1, e, idx, curr_pos);
    }

    int query(int node, int s, int e, int l, int r, int k) {
        if (s == e) return s;
        int m = (s + e) >> 1, tmp = 0;

        auto it = tree[node * 2].upper_bound(r); // find the version that updates has been done at most r-th idx
        if (it != tree[node * 2].begin())
            tmp = PST.query((--it)->second, l, r);

        if (tmp >= k) return query(node * 2, s, m, l, r, k);
        else return query(node * 2 + 1, m + 1, e, l, r, k - tmp);
    }
} TREE;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n), compr(n), last(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        compr[i] = v[i];
    }
    sort(all(compr));
    compr.resize(unique(all(compr)) - compr.begin());
    for (int i = 0; i < n; i++) {
        v[i] = int(lower_bound(all(compr), v[i]) - compr.begin());
    }

    for (int i = 0; i < n; i++) {
        if (last[v[i]] != -1)
            TREE.update(1, 0, MAX, v[i], last[v[i]], i);
        else
            TREE.update(1, 0, MAX, v[i], i);
        last[v[i]] = i;
    }

    int m;
    cin >> m;
    ll prev = 0;
    while (m--) {
        int a, b, c, d, k;
        cin >> a >> b >> c >> d >> k;
        int l = int((a * max(0LL, prev) + b) % n); // 0-indexed
        int r = int((c * max(0LL, prev) + d) % n);
        if (l > r) swap(l, r);


        prev = TREE.query(1, 0, MAX, l, r, k);
        if (prev == MAX) prev = -1;
        else prev = compr[prev];
        cout << prev << endl;
    }

    return 0;
}
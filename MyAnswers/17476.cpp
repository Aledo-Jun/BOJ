//
// Created by june0 on 2025-02-15.
//
//
// ** The #include statements were replaced by [ CCopy ] **
// @See http://github.com/Aledo-Jun/CCopy
//

// [ #include "Utils/using_templates.hpp" ]


#include <bits/stdc++.h>
//#pragma GCC target("avx2")
#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
using namespace std;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using ld [[maybe_unused]] = double;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;



// end of [ Utils/using_templates.hpp ]

#ifndef ONLINE_JUDGE
#define LOCAL
#else
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
#include <iomanip>

    constexpr int SZ = 1 << 23;

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

        long double ReadLongDouble() {
            std::string ret = ReadString();
            return std::stold(ret);
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
        char _write_buffer[SZ];
        int _write_idx;
        int _precision = 6;
    public:
        ~OUTPUT() { Flush(); }

        explicit operator bool() const { return true; }

        void Flush() {
            write(1, _write_buffer, _write_idx);
            _write_idx = 0;
        }

        void SetPrecision(int precision) {
            _precision = precision;
        }

        void WriteChar(char c) {
            if (_write_idx == SZ) Flush();
            _write_buffer[_write_idx++] = c;
        }

        template<class T>
        void WriteInt(T n) {
            int sz = GetSize(n);
            if (_write_idx + sz >= SZ) Flush();
            if (n < 0) _write_buffer[_write_idx++] = '-', n = -n;
            for (int i = sz; i-- > 0; n /= 10)
                _write_buffer[_write_idx + i] = n % 10 | 48;
            _write_idx += sz;
        }

        void WriteString(const std::string& s) {
            for (auto &c: s) WriteChar(c);
        }

        template<class T>
        void WriteDouble(T d) {
            WriteString(FloatingToFixedString(d, _precision));
        }

        template<class T>
        int GetSize(T n) {
            int ret = 1;
            for (n = n >= 0 ? n : -n; n >= 10; n /= 10) ret++;

            return ret;
        }

        template<class T>
        std::string FloatingToFixedString(T val, int precision) {
            char buf[64];
            if constexpr (std::is_same_v<double, T>)
                snprintf(buf, sizeof(buf), "%.*f", precision, val);
            else
                snprintf(buf, sizeof(buf), "%.*Lf", precision, val);
            return std::string(buf);
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
        if constexpr (std::is_same_v<double, T>) i = in.ReadDouble();
        else if constexpr (std::is_same_v<long double, T>) i = in.ReadLongDouble();
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

    OUTPUT &operator<<(OUTPUT &out, OUTPUT &(*fp)(OUTPUT &)) {
        return fp(out);
    }

    OUTPUT &flush(OUTPUT& out) {
        out.Flush();
        return out;
    }

    OUTPUT &fixed(OUTPUT& out) {
        // Do nothing since there's no other floating point format than fixed.
        return out;
    }

    OUTPUT &operator<<(OUTPUT &out, const _Setprecision &m) {
        out.SetPrecision(m._M_n);
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

template<typename NodeType, typename LazyType,
        typename MergeNode = NodeType(NodeType,NodeType),
        typename MergeLazy = LazyType(LazyType,LazyType,NodeType),
        typename UpdateLazy = LazyType(LazyType,LazyType,NodeType),
        typename ApplyLazy = NodeType(NodeType,LazyType,int),
        typename TAG = bool(NodeType,LazyType),
        typename BREAK = bool(NodeType,LazyType)>
class SegTreeBeats {
private:
    MergeNode mergeNode;
    MergeLazy mergeLazy;
    UpdateLazy updateLazy;
    ApplyLazy applyLazy;
    TAG tag_condition;
    BREAK break_condition;

    vector<NodeType> tree;
    vector<LazyType> lazy;

    int size{}, height{}, n{};
    NodeType default_node;
    LazyType default_lazy;

    void init() {
        for (int i = n - 1; i >= 1; i--) pull(i);
    }

    void pull(int node) {
        tree[node] = mergeNode(tree[node << 1], tree[node << 1 | 1]);
    }

    void push(int node, int start, int end) {
        if (lazy[node] != default_lazy) {
            tree[node] = applyLazy(tree[node], lazy[node], end - start + 1);
            if (start != end) {
                lazy[node << 1] = mergeLazy(lazy[node << 1], lazy[node], tree[node]);
                lazy[node << 1 | 1] = mergeLazy(lazy[node << 1 | 1], lazy[node], tree[node]);
            }
            lazy[node] = default_lazy;
        }
    }

    void _update(int node, int start, int end, int l, int r, LazyType value) {
        push(node, start, end);

        if (r < start || end < l || break_condition(tree[node], lazy[node])) return;

        if (l <= start && end <= r) {
            if (tag_condition(tree[node], lazy[node])) {
                lazy[node] = updateLazy(lazy[node], value, tree[node]);
                push(node, start, end);
                return;
            }
        }

        int mid = (start + end) >> 1;
        _update(node << 1, start, mid, l, r, value);
        _update(node << 1 | 1, mid + 1, end, l, r, value);
        pull(node);
    }

    NodeType _query(int node, int start, int end, int left, int right) {
        push(node, start, end);

        if (end < left || right < start) return default_node;
        if (left <= start && end <= right) return tree[node];

        int mid = (start + end) >> 1;
        auto left_result = _query(node << 1, start, mid, left, right);
        auto right_result = _query(node << 1 | 1, mid + 1, end, left, right);
        return mergeNode(left_result, right_result);
    }

public:
    SegTreeBeats() = default;

    explicit
    SegTreeBeats(int sz, NodeType default_node = {}, LazyType default_lazy = {})
            : default_node(std::move(default_node)), default_lazy(std::move(default_lazy)) {
        height = (int) ceil(log2(sz));
        size = (1 << (height + 1));
        n = size >> 1;
        tree.resize(size + 1, this->default_node);
        lazy.resize(size + 1, this->default_lazy);
    }

    explicit
    SegTreeBeats(const vector<NodeType> &v, NodeType default_node = {}, LazyType default_lazy = {})
            : default_node(std::move(default_node)),
              default_lazy(std::move(default_lazy)) {
        height = (int) ceil(log2(v.size()));
        size = (1 << (height + 1));
        n = size >> 1;
        tree.resize(size + 1, this->default_node);
        lazy.resize(size + 1, this->default_lazy);
        std::copy(v.begin(), v.end(), tree.begin() + n);
        init();
    }

    void update(int l, int r, LazyType value) {
        if (l > r) return;
        _update(1, 0, n - 1, l, r, value);
    }

    NodeType query(int l, int r) {
        if (l > r) return default_node;
        return _query(1, 0, n - 1, l, r);
    }
};

struct Node {
    ll mx = -1, mn = 1e18, sum = 0;
};
struct Lazy {
    ll add = 0, assign = -1;
    bool operator!=(const Lazy &other) const { return add != other.add || assign != other.assign; }
};
struct MergeNode {
    Node operator()(const Node &a, const Node &b) const {
        return {max(a.mx, b.mx), min(a.mn, b.mn), a.sum + b.sum};
    }
};
struct MergeLazy {
    Lazy operator()(const Lazy &a, const Lazy &b, const Node &node) const {
        if (b.assign == 0) {
            return {a.add + b.add, max(a.assign, 0LL)}; // make this Lazy valid
        }
        return b;
    }
};
struct UpdateLazy {
    Lazy operator()(const Lazy &a, const Lazy &b, const Node &node) const {
        if (b.assign == 0) {
            return b;
        }
        if (floor(sqrt(node.mn)) == floor(sqrt(node.mx))) {
            return {0, (ll)floor(sqrt(node.mn))};
        }
        if (node.mn + 1 == node.mx) {
            return {(ll)floor(sqrt(node.mn)) - node.mn, 0};
        }
        return a;
    }
};
struct ApplyLazy {
    Node operator()(const Node &node, const Lazy &lazy, int len) const {
        assert(lazy.assign != -1);
        if (lazy.assign == 0) {
            return {node.mx + lazy.add,
                    node.mn + lazy.add,
                    node.sum + len * lazy.add};
        } else {
            return {lazy.assign + lazy.add,
                    lazy.assign + lazy.add,
                    (lazy.assign + lazy.add) * len};
        }
    }
};
struct TAG {
    bool operator()(const Node &node, const Lazy &lazy) const {
        return lazy.assign == 0
               || floor(sqrt(node.mn)) == floor(sqrt(node.mx))
               || node.mn + 1 == node.mx;
    }
};
struct BREAK {
    bool operator()(const Node &node, const Lazy &lazy) const {
        return lazy.assign > 0 && node.mx == 1;
    }
};

using segtree_beats = SegTreeBeats<Node,Lazy,MergeNode,MergeLazy,UpdateLazy,ApplyLazy,TAG,BREAK>;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<Node> v(n);
    for (auto &[mx, mn, sum] : v) {
        cin >> mx;
        mn = sum = mx;
    }

    segtree_beats seg(v);

    int m;
    cin >> m;
    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, val;
            cin >> l >> r >> val; l--, r--;
            seg.update(l, r, {val, 0});
        } else if (op == 2) {
            int l, r;
            cin >> l >> r; l--, r--;
            seg.update(l, r, {0, 1});
        } else {
            int l, r;
            cin >> l >> r; l--, r--;
            auto [mx, mn, sum] = seg.query(l, r);
            cout << sum << endl;
        }
    }

    return 0;
}

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

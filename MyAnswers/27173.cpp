//
// Created by june0 on 2025-02-14.
//
//
// ** The #include statements were replaced by [ CCopy ] **
// @See http://github.com/Aledo-Jun/CCopy
//

// [ #include "Utils/using_templates.hpp" ]


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

enum class OpType { SUB, SQRT, SET_LINE };

struct LazyOp {
    OpType type;
    ll val;
    // For SET_LINE, val = baseOffset = (t - y).
    // For SUB, val = how much to subtract.
    // For SQRT, val = # of consecutive SQRT ops
    LazyOp(OpType type, ll val) : type(type), val(val) {}
};

const int MAX_N = 100'000;
const int MAX_OPS = 20;

struct Node {
    int l, r;
    vector<LazyOp> lazy;
    ll mn;
} tree[MAX_N * 4];

vector<ll> A;

Node merge(const Node &a, const Node &b) {
    Node ret;
    ret.l = a.l;
    ret.r = b.r;
    ret.mn = min(a.mn, b.mn);
    return ret;
}

void build(int node, int l, int r) {
    if (l == r) {
        tree[node].l = l;
        tree[node].r = r;
        tree[node].mn = A[l];
        tree[node].lazy.reserve(MAX_OPS);
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

void apply(int node, const LazyOp &op) {
    const auto &[type, val] = op;
    switch (type) {
        case OpType::SQRT:
            for (int i = 0; i < val && tree[node].mn > 1; i++)
                tree[node].mn = (ll) floor(sqrtl(tree[node].mn));
            if (!tree[node].lazy.empty() && tree[node].lazy.back().type == OpType::SQRT) {
                tree[node].lazy.back().val += val;
            } else {
                tree[node].lazy.emplace_back(op);
            }
            break;
        case OpType::SUB:
            tree[node].mn -= val;
            if (!tree[node].lazy.empty() && tree[node].lazy.back().type == OpType::SUB) {
                tree[node].lazy.back().val += val;
            } else {
                tree[node].lazy.emplace_back(op);
            }
            break;
        case OpType::SET_LINE:
            tree[node].mn = tree[node].l + 1 + val;
            tree[node].lazy.clear();
            tree[node].lazy.emplace_back(op);
    }

    if (tree[node].lazy.size() > MAX_OPS) {
        assert(("Lazy ops > MAX_OPS", false));
        // probably? not reachable
    }
}

void push(int node) {
    if (tree[node].lazy.empty()) return;
    if (tree[node].l == tree[node].r) return;
    for (const auto &op: tree[node].lazy) {
        apply(node << 1, op);
        apply(node << 1 | 1, op);
    }
    tree[node].lazy.clear();
}

void pull(int node) {
    tree[node] = merge(tree[node << 1], tree[node << 1 | 1]);
}

void update(int node, int l, int r, const LazyOp &op) {
    int s = tree[node].l, e = tree[node].r;
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
        apply(node, op);
        return;
    }
    push(node);
    update(node << 1, l, r, op);
    update(node << 1 | 1, l, r, op);
    pull(node);
}

ll query(int node, int l, int r) {
    int s = tree[node].l, e = tree[node].r;
    if (r < s || e < l) return LLONG_MAX;
    if (l <= s && e <= r) return tree[node].mn;
    push(node);
    return min(query(node << 1, l, r), query(node << 1 | 1, l, r));
}

void printA() {
    cout << "A: ";
    for (int i = 0; i < A.size(); i++) cout << query(1, i, i) << ' ';
    cout << endl;
}

int32_t main() {
    fastIO;
    int n, q;
    cin >> n >> q;
    A.resize(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    build(1, 0, n-1);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int idx;
            cin >> idx; idx--;
            cout << query(1, idx, idx) << endl;
        } else if (op == 2) {
            int x, y;
            ll t;
            cin >> x >> y >> t; x--; y--;
            if (query(1, x, y) < t) continue;
            update(1, x, y, {OpType::SUB, t});
        } else if (op == 3) {
            int x, y;
            ll t;
            cin >> x >> y >> t; x--; y--;
            update(1, x, y, {OpType::SET_LINE, t - y - 1});
        } else {
            int x, y;
            cin >> x >> y; x--; y--;
            update(1, x, y, {OpType::SQRT, 1});
        }
        //if (op != 1) printA();
    }

    return 0;
}

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

//
// Created by june0 on 2025-01-30.
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
using ld [[maybe_unused]] = double;
using lld [[maybe_unused]] = long double;
using llld [[maybe_unused]] = __float128;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the root of all evil."
 *  <sub> Donald Knuth </sub>
 */

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

template<typename T = int,
        typename Func = plus<T>,
        typename Inv_Func = minus<T>,
        T Identity = 0>
class FenWickTree {
private:
    Func f;
    Inv_Func inv_f;

    vector<T> tree;
    int size;

    void _update(int x, T val) {
        for (int i = x; i < size; i += (i & -i)) {
            tree[i] = f(tree[i], val);
        }
    }

    T _query(int x) {
        T res = Identity;
        for (int i = x; i > 0; i -= (i & -i)) {
            res = f(res, tree[i]);
        }
        return res;
    }

public:
    // Empty tree constructor
    FenWickTree(int size) : size(size) { // NOLINT
        tree.resize(size, Identity);
    }

    FenWickTree(const vector<T> &v) {
        size = (int) v.size();
        tree.resize(size);
        for (int i = 1; i < size; i++) {
            _update(i, v[i]);
        }
    }

    void update(int x, T val) {
        _update(x, val);
    }

    T query(int idx) {
        return _query(idx);
    }

    T query(int left, int right) {
        if (left > right) return Identity;
        return inv_f(_query(right), _query(left - 1));
    }
}; // class FenWickTree

int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<int> v(n), w, cnt(m+1, 0);
    for (auto &e : v) {
        cin >> e;
        cnt[e]++;
    }
    w = v;
    rotate(w.begin(), w.begin()+1, w.end()); // 1 step shifted
    v.emplace_back(v[0]);
    w.emplace_back(w[0]);

    auto sub = [](int s, int e, int ps, int pe) -> pair<int,int> {
        if (s > e) return {1e9, 1e9}; // current set is empty
        else if (e < ps || pe < s) return {s, e};
        else if (ps <= s && e <= pe) return {1e9, 1e9}; // make empty set
        else if (ps <= s) return {pe + 1, e};
        else if (e <= pe) return {s, ps - 1};
        return {s, e};
    };

    FenWickTree seg1(m + 1), seg2(m + 1);
    int s, e, ps = 1e9, pe = 1e9; // keep track of [s, e] - [ps, pe]
    for (int i = 0; i < n; i++) {
        s = v[i], e = v[i+1];
        if (s > e) swap(s, e);
        s++, e--;
        tie(s, e) = sub(s, e, ps, pe);
        if (i == n - 1) {
            ps = v[0], pe = v[1];
            if (ps > pe) swap(ps, pe);
            ps++, pe--;
            tie(s, e) = sub(s, e, ps, pe);
        }
        seg1.update(s, +1);
        seg1.update(e+1, -1);
        ps = s, pe = e;
    }
    ps = pe = 1e9;
    for (int i = 0; i < n; i++) {
        s = w[i], e = w[i+1];
        if (s > e) swap(s, e);
        s++, e--;
        tie(s, e) = sub(s, e, ps, pe);
        if (i == n - 1) {
            ps = w[0], pe = w[1];
            if (ps > pe) swap(ps, pe);
            ps++, pe--;
            tie(s, e) = sub(s, e, ps, pe);
        }
        seg2.update(s, +1);
        seg2.update(e+1, -1);
        ps = s, pe = e;
    }

    for (int i = 1; i <= m; i++) {
        if (cnt[i] == 0) cout << "-1 ";
        else cout << n - cnt[i] + max(seg1.query(i), seg2.query(i)) << ' ';
    }

    return 0;
}

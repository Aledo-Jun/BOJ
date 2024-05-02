//
// Created by june0 on 2024-05-02.
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

class FenWickTree {
public:
    int tree[MAX + 5];
    int size = MAX + 1;

    void _update(int x, int val) {
        for (int i = x; i < size; i += (i & -i)) {
            tree[i] += val;
        }
    }

    int _query(int x) {
        int res = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            res += tree[i];
        }
        return res;
    }

public:
    FenWickTree() {
        memset(tree, 0, sizeof tree);
    }

    void update(int x, int val) {
        _update(x, val);
    }

    int query(int x) {
        return _query(x);
    }

    int query(int left, int right) {
        if (left > right) return 0;
        return _query(right) - _query(left - 1);
    }
} rsq1, rsq2; // class FenWickTree

int n, sqrt_n, m;
struct query {
    int l, r, k, idx;

    bool operator<(const query& other) const {
        if (l / sqrt_n == other.l / sqrt_n)
            return ((l / sqrt_n) % 1) ? r < other.r : r > other.r;
        return l < other.l;
    }
};

int a[MAX + 5], b[MAX + 5];
int cnt_a[MAX + 5], cnt_b[MAX + 5];
int sqrt_[MAX + 5];

int32_t main() {
    fastIO;
    int last = 1;
    for (int i = 2; i <= 317; i++) // precompute sqrt
    {
        while (last < i * i) sqrt_[last++] = i - 1;
    }
    memset(cnt_a, 0, sizeof(cnt_a));
    memset(cnt_b, 0, sizeof(cnt_b));

    cin >> n;
    sqrt_n = sqrt_[n];
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    cin >> m;
    vector<query> q(m);
    for (int i = 0; i < m; i++){
        cin >> q[i].l >> q[i].r >> q[i].k;
        q[i].idx = i;
    }
    sort(all(q));

    vector<ll> ans(m);

    auto add = [&](int i) {
        rsq1._update(a[i], 1);
        rsq2._update(b[i], 1);
        cnt_a[a[i]]++;
        cnt_b[b[i]]++;
    };
    auto del = [&](int i) {
        rsq1._update(a[i], -1);
        rsq2._update(b[i], -1);
        cnt_a[a[i]]--;
        cnt_b[b[i]]--;
    };
    auto solve = [&](int k) -> ll {
        int sqrt_k = sqrt_[k];
        ll res = 0;

        for (int i = 1; i <= sqrt_k; i++) {
            if (cnt_a[i] == 0) continue;
            res += (ll)cnt_a[i] * rsq2.query(1, k / i);
        }
        for (int i = 1; i <= sqrt_k; i++) {
            if (cnt_b[i] == 0) continue;
            res += (ll)cnt_b[i] * rsq1.query(sqrt_k + 1, k / i); // exclude the overlap(both are <= sqrt_k)
        }
        return res;
    };

    int s = q[0].l, e = s - 1;

    for (const auto& [l, r, k, idx]: q) {
        // Mo's + BIT update -> O(sqrt(n) * log n)
        while (s > l) add(--s);
        while (e < r) add(++e);
        while (s < l) del(s++);
        while (e > r) del(e--);

        ans[idx] = solve(k); // O(sqrt(k) * log n) = O(sqrt(n) * log n)
    } // => O(m * sqrt(n) * log n) = O(n * sqrt(n) * log n)

    for (const auto& answer : ans) cout << answer << endl;
    return 0;
}
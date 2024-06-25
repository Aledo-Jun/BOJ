//
// Created by june0 on 2024-06-25.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC target("avx2")
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
using llld [[maybe_unused]] = __float128;
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

/**
 * Convex Hull Trick implementation
 * @tparam Comp default to be std::greater which means query gives minimum value
 */
template<typename Comp = std::greater<>>
class ConvexHullTrick {
    Comp comp;

    struct Fraction {
        // a / b
        ll a, b;
        Fraction(ll a, ll b) : a(a), b(b) {}
        Fraction(ll a) : a(a), b(1) {} // NOLINT(implicit conversion)
        bool operator< (const Fraction& other) const {
            return (lll) a * other.b < (lll) b * other.a;
        }
        bool operator> (const Fraction& other) const {
            return (lll) a * other.b > (lll) b * other.a;
        }
        bool operator<= (const Fraction& other) const {
            return (lll) a * other.b <= (lll) b * other.a;
        }
        bool operator>= (const Fraction& other) const {
            return (lll) a * other.b >= (lll) b * other.a;
        }
    };

    struct Line : public Fraction {
        // f(x) = ax + b
        Line(ll a, ll b) : Fraction(a, b) {}
    };


    [[nodiscard]] // return the value of f(x) = ax + b
    ll get_value(const Line& f, const ll x) const { return f.a * x + f.b; }

    [[nodiscard]] // return the x pos of the intersection of the two given lines
    Fraction get_cross_x(const Line& l1, const Line& l2) const {
        // a1 x + b1 = a2 x + b2 -> (a1 - a2)x = (b2 - b1)
        return {l2.b - l1.b, l1.a - l2.a};
    }

    [[nodiscard]] // return cross_x(l1, l2) > cross_x(l2, l3)
    bool compare_cross(const Line& l1, const Line& l2, const Line& l3) const {
        return get_cross_x(l1, l2) > get_cross_x(l2, l3);
    }

    std::vector<Line> lines; // maintain the hull

public:
    void insert(ll a, ll b) {
        Line newLine(a, b);
        for (int sz = (int)lines.size(); sz > 1; sz--) {
            if (compare_cross(lines[sz - 2], lines[sz - 1], newLine)) lines.pop_back();
            else break;
        }
        lines.emplace_back(newLine);
    }

    ll query(ll x) {
        int l = 0, r = lines.size();
        while (l + 1 < r) {
            int m = l + ((r - l) >> 1);
            if (comp(Fraction(x), get_cross_x(lines[m - 1], lines[m]))) l = m;
            else r = m;
        }
        return get_value(lines[l], x);
    }

    // only can be used when x is monotonically increasing
    int ptr = 0;
    ll query_monotonic(ll x) {
        while (ptr + 1 < lines.size() && comp(get_value(lines[ptr], x), get_value(lines[ptr + 1], x))) ptr++;
        return get_value(lines[ptr], x);
    }
};
ConvexHullTrick<less_equal<>> CHT;

ll a, b, c;
ll f(ll x) {
    return a * x * x + b * x + c;
}

int32_t main() {
    fastIO;
    int n;
    cin >> n >> a >> b >> c;

    vector<int> v(n);
    for (auto& e : v) cin >> e;

    vector<ll> prefix(n);
    prefix[0] = v[0];
    for (int i = 1; i < n; i++) prefix[i] = prefix[i - 1] + v[i];

    vector<ll> dp(n);
    // dp[i] = max{0 <= j < i}(dp[j] + f(sum(v[j+1],...,v[i])))
    // sum(v[j+1],...,v[i]) = prefix[i] - prefix[j]
    // with g(Y)(x) = -2aYx + aY^2 - bY
    // f(prefix[i] - prefix[j]) = f(prefix[i]) + g(prefix[j])(prefix[i])
    // dp[i] = max{0 <= j < i}(dp[j] + f(prefix[i]) + g(prefix[j])(prefix[i]))
    // let x := prefix[i], y := dp[i],
    // then y = g(prefix[j])(x) + dp[j] + f(x)
    dp[0] = f(v[0]);
    for (int i = 0; i < n - 1; i++) {
        CHT.insert(-2LL * a * prefix[i], a * prefix[i] * prefix[i] - b * prefix[i] + dp[i]);
        dp[i + 1] = max(CHT.query_monotonic(prefix[i + 1]), 0LL) + f(prefix[i + 1]);
    }
    cout << dp[n - 1];

    return 0;
}
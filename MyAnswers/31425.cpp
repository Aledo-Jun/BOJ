//
// Created by june0 on 2024-08-29.
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
 * Count the number of positive integer pairs (x,y) s.t. px + qy <= r
 */
template<typename int_t>
int_t LatticePointCount(int_t p, int_t q, int_t r) {
    if (p + q > r) return 0;
    if (p < q) swap(p, q);
    int_t Q = p / q, R = p % q;
    int_t t = (Q * r + R) / p;
    int_t t1 = (t - 1) / Q * (2 * t - Q * (1 + (t - 1) / Q)) / 2;
    int_t t2 = LatticePointCount(q, R, r - q * t);
    return t1 + t2;
}

/**
 * Calculate sum_{i=1..n}((p * i + q) // r)
 * @see https://asfjwd.github.io/2020-04-24-floor-sum-ap/
 * @verification https://atcoder.jp/contests/practice2/tasks/practice2_c
 */
template<typename int_t>
int_t FloorSum(int_t p, int_t q, int_t r, int_t n) {
    int_t res = 0;
    res += p / r * n * (n + 1) / 2;
    p %= r;
    res += q / r * n;
    q %= r;
    res += LatticePointCount(p, r, q + p * (n + 1));
    return res;
}

/*
 * Let digit-wise mod sum to be represented as @
 * Problem: Given integers a, b, c, d, p, q, r, s;
 *          Find @_{i=a..c,j=b..d} (A(i,j)) --- (*),
 *          where A(i,j) := (p * i + q) @ (r * j + s) = X_i @ Y_j
 *
 * First, it can be easily found that @ operation is associative and commutative.
 * Then, we can convert (*) into
 * [@_{i=a..c} (X_i @@ w)] @ [@_{j=b..d} (Y_j @@ h)]
 * = [(@_{i=a..c} X_i) @@ w] @ [(@_{j=b..d} Y_j) @@ h],
 * where a @@ b denotes a @ a @ ..(total b times).. @ a and w := d - b + 1, h = c - a + 1.
 *
 * Now we're going to calculate the answer digit-by-digit.
 * Since we only need to calculate each digit one at a time, we can simply convert @ into + and apply modulo.
 * 1st digit: [sum_{i=a..c} (X_i) + sum_{j=b..d} (Y_j)] % MOD
 * 2nd digit: [sum_{i=a..c} (X_i // MOD) + sum_{j=b..d} (Y_j // MOD)] % MOD
 *    ...
 * nth digit: [sum_{i=a..c} (X_i // MOD^(n-1)) + sum_{j=b..d} (Y_j // MOD^(n-1))] % MOD
 *          = [FloorSum(p, q, MOD^(n-1), c) - FloorSum(p, q, MOD^(n-1), a-1)
 *           + FloorSum(r, s, MOD^(n-1), d) - FloorSum(r, s, MOD^(n-1), b-1)] % MOD
 */
int32_t main() {
    fastIO;
    ll n, m, MOD;
    cin >> n >> m >> MOD;
    ll p, q, r, s;
    cin >> p >> q >> r >> s;
    int k;
    cin >> k;
    while (k--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        int len = (int) (log(max(p * c + q, r * d + s)) / log(MOD)) + 1;
        vector<ll> MOD_pow(len);
        MOD_pow[0] = 1;
        for (int i = 1; i < len; i++) MOD_pow[i] = MOD_pow[i-1] * MOD;
        string ans;
        for (int i = len - 1; i >= 0; i--) {
            auto X = (FloorSum<lll>(p, q, MOD_pow[i], c)
                      -FloorSum<lll>(p, q, MOD_pow[i], a-1)) % MOD;
            auto Y = (FloorSum<lll>(r, s, MOD_pow[i], d)
                      -FloorSum<lll>(r, s, MOD_pow[i], b-1)) % MOD;
            X = X * (d - b + 1) % MOD;
            Y = Y * (c - a + 1) % MOD;
            ans += char((X + Y) % MOD + '0');
        }
        int i = 0;
        for (; i < len - 1 && ans[i] == '0'; i++);
        for (; i < len; i++) cout << ans[i];
        cout << endl;
    }

    return 0;
}
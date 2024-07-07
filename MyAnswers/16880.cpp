//
// Created by june0 on 2024-07-07.
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

int32_t main() {
    fastIO;

    // Rook -> two piles of x, y pebbles / any amount > 0
    //      => x ^ y
    //   0 1 2 3 4 5
    //   1 0 3 2 5 4
    //   2 3 0 1 6 7
    //   3 2 1 0 7 6
    //   4 5 6 7 0 1
    //   5 4 7 6 1 0
    auto R = [](int x, int y) { return x ^ y; };

    // Bishop -> pile of min(x, y) pebbles / any amount > 0
    //        => min(x, y)
    auto B = [](int x, int y) { return min(x, y); };

    // King -> two piles of x, y pebbles / take (1,0), (0,1) or (1,1)
    //      => g(x,y) = mex(g(x-1,y), g(x,y-1), g(x-1,y-1))
    //   base: g(0,0) = 0, g(0,1) = 1, g(1,0) = 1, g(1,1) = 2, g(2,0) = 0, g(0,2) = 0
    //   0 1 0 1 0 1
    //   1 2 3 2 3 2    => g(even, even) = 0
    //   0 3 0 1 0 1       g(odd, odd) = 2
    //   1 2 1 2 3 2       g(even > odd) = 3
    //   0 3 0 3 0 1       g(odd > even) = 1   EUREKA!
    //   1 2 1 2 1 2
    auto K = [](int x, int y) {
//        if (x < y) swap(x, y);
//        if (x & 1) {
//            if (y & 1) return 2;
//            return 1;
//        } else {
//            if (y & 1) return 3;
//            return 0;
//        }
        if (x & 1 && y & 1) return 2;
        if (~x & 1 && ~y & 1) return 0;
        if (x & 1) swap(x, y); // x = even
        if (x > y) return 3;
        return 1;
    };

    // Knight -> two piles of x, y pebbles / take (1,2) or (2,1)
    //        => g(x,y) = mex(g(x-2,y-1), g(x-1,y-2))
    //   base: g(0,0) = g(0,n) = g(n,0) = g(1,1) = 0
    //         g(2,1) = g(1,2) = 1
    //   0 0 0 0 0 0 0 ... 0
    //   0 0 1 1 1 1 1 ... 1   => let p = (x - 1) / 3 * 3
    //   0 1 1 1 2 2 2 ... 2
    //   0 1 1 0 0 0 0 ... 0      if y < p then g(x,y) = y % 3
    //   0 1 2 0 0 1 1 ... 1      else if y == p then g(x,y) = 0
    //   0 1 2 0 1 1 1 2 2 2      else g(x,y) = 1
    auto N = [](int x, int y) -> int {
        if (x == y) return x % 3 == 2;

        if (x < y) swap(x, y);
        int p = (x - 1) / 3 * 3;
        if (y < p) return y % 3;
        if (y == p) return 0;
        return 1;
    };

    // Palace -> two piles of x, y pebbles / take (n,0), (0,n) or (1,1)
    //
    //   0 1 2 3 4 5
    //   1 2 0 4 5 3
    //   2 0 1 5 3 4
    //   3 4 5 0 1 2
    //   4 5 3 1 2 0
    //   5 3 4 2 0 1
    auto P = [](int x, int y) {
        if (x < y) swap(x, y);
        int p = int(x / 3) ^ int(y / 3);
        vector<int> a{p*3, p*3+1, p*3+2};
        return a[(x % 3 + y % 3) % 3];
    };

    int n;
    cin >> n;
    int X = 0;
    for (int i = 0; i < n; i++) {
        int x, y;
        char c;
        cin >> x >> y >> c;
        switch (c) {
            case 'R':
                X ^= R(x, y);
                break;
            case 'B':
                X ^= B(x, y);
                break;
            case 'K':
                X ^= K(x, y);
                break;
            case 'N':
                X ^= N(x, y);
                break;
            case 'P':
                X ^= P(x, y);
                break;
            default:
                assert(false);
        }
    }
    cout << (X ? "koosaga" : "cubelover");
    return 0;
}
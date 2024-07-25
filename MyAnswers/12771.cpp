//
// Created by june0 on 2024-07-25.
//
#include <bits/stdc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#pragma comment( user, "Compiled on " __DATE__ " at " __TIME__ )
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

// Structure representing the position of the point
template<typename T = int>
struct Point_type {
    T x{}, y{};

    Point_type() = default;

    Point_type(T x, T y) : x(x), y(y) {}

    Point_type operator-(const Point_type &other) const {
        Point_type res(x - other.x, y - other.y);
        return res;
    }

    bool operator==(const Point_type &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point_type &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator<=(const Point_type &other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Point_type &other) const {
        return !(*this < other) && !(*this == other);
    }

    bool operator>=(const Point_type &other) const {
        return *this > other || *this == other;
    }

    friend ostream &operator<<(ostream &out, const Point_type p) {
        out << p.x << ' ' << p.y << ' ';
        return out;
    }
};

using Point = Point_type<>;

// CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
// Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
int CCW(const Point &p1, const Point &p2, const Point &p3) {
    ll tmp =  (ll)p1.x * p2.y + (ll)p2.x * p3.y + (ll)p3.x * p1.y
              - (ll)p1.y * p2.x - (ll)p2.y * p3.x - (ll)p3.y * p1.x;
    if (tmp == 0) return 0;
    else if (tmp > 0) return 1;
    else return -1;
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> x0(n), x1(n), y(n);
    for (int i = 0; i < n; i++) {
        cin >> x0[i] >> x1[i] >> y[i];
        if (x0[i] > x1[i]) swap(x0[i], x1[i]);
    }

    struct Line {
        int x, y, dx;
        Line(int x, int y, int dx) : x(x), y(y), dx(dx) {}
    }; // denotes the line from starting point to (x,y)

    auto solve = [&](const Point &start) -> int {
        const auto &[sx, sy] = start;
        vector<Line> v;
        for (int i = 0; i < n; i++) {
            if (y[i] > sy) {
                v.emplace_back(sx - x0[i], y[i] - sy, x1[i] - x0[i]); // meeting first -> add dx
                v.emplace_back(sx - x1[i], y[i] - sy, x0[i] - x1[i]); // meeting second -> subtract dx
            }
            if (y[i] < sy) { // if the point is under the starting point, make it point-symmetry
                v.emplace_back(x0[i] - sx, sy - y[i], x0[i] - x1[i]);
                v.emplace_back(x1[i] - sx, sy - y[i], x1[i] - x0[i]);
            }
        }
        // sort the lines by its polar angle
        sort(all(v), [&](const Line &l1, const Line &l2) {
            ll ccw = CCW({0, 0}, {l1.x, l1.y}, {l2.x, l2.y});
            if (ccw == 0) return l1.dx > l2.dx; // when they're aligned, add first and subtract later
            return ccw > 0;
        });
        int res = 0, cur = 0;
        for (const auto &[_x,_y,dx]: v) {
            cur += dx;
            res = max(res, cur);
        }
        return res;
    };

    int mx = -1;
    for (int i = 0; i < n; i++) {
        mx = max(mx, max(solve({x0[i], y[i]}), solve({x1[i], y[i]})) + x1[i] - x0[i]);
    }

    cout << mx;

    return 0;
}
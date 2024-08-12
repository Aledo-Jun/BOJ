//
// Created by june0 on 2024-08-12.
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

struct point {
    int x, y;
};

enum Direction {
    LEFT,
    RIGHT
};

struct line {
    int idx;
    point l, r;
    Direction direction;
    line() = default;
    line(const point &p1, const point &p2, int idx) : idx(idx) {
        if (p1.x < p2.x) {
            l = p1, r = p2;
            if (p1.y < p2.y) direction = LEFT;
            else direction = RIGHT;
        } else {
            l = p2, r = p1;
            if (p1.y < p2.y) direction = RIGHT;
            else direction = LEFT;
        }
    }
    bool operator==(const line &other) const { return idx == other.idx; }
    bool operator<(const line &other) const {
        if (idx == other.idx) return false; // not needed to be specified(?)

        auto otl = other.l, otr = other.r;
        if (l.x <= otl.x && otl.x <= r.x) {
            // (otl.y - l.y) / (otl.x - l.x) < (r.y - l.y) / (r.x - l.x)
            return ll(otl.y - l.y) * (r.x - l.x) - ll(r.y - l.y) * (otl.x - l.x) < 0;
        }
        if (otl.x <= l.x && l.x <= otr.x) {
            return ll(l.y - otl.y) * (otr.x - otl.x) - ll(otr.y - otl.y) * (l.x - otl.x) > 0;
        }
        return idx < other.idx;
    }
};

enum Event_type : int {
    R_UP,
    R_DOWN,
    L_UP,
    L_DOWN
};
struct event {
    int x, idx;
    Event_type type;
    event(const line &l, bool left) : idx(l.idx) {
        switch (l.direction) {
            case LEFT: {
                if (left) {
                    type = L_DOWN;
                    x = l.l.x;
                } else {
                    type = R_UP;
                    x = l.r.x;
                }
                break;
            }
            case RIGHT: {
                if (left) {
                    type = L_UP;
                    x = l.l.x;
                } else {
                    type = R_DOWN;
                    x = l.r.x;
                }
                break;
            }
        }
    }

    // for sweeping according to x
    bool operator<(const event &other) const {
        if (x != other.x) return x < other.x;
        return type > other.type;
    }
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;

    vector<line> lines; lines.reserve(n + 1);
    vector<event> events; events.reserve(n * 2 + 2);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        line l(point{x1, y1}, point{x2, y2}, i);
        lines.emplace_back(l);
        events.emplace_back(l, true);
        events.emplace_back(l, false);
    }

    int x0;
    cin >> x0;
    line l(point{x0-1, 2'000'001}, point{x0, 2'000'000}, n);
    lines.emplace_back(l);
    events.emplace_back(l, true);
    events.emplace_back(l, false);

    sort(all(events));

    set<line> sweep;
    vector<int> trace(n + 1, -1);
    for (const auto &e : events) {
        switch (e.type) {
            case L_UP: {
                sweep.emplace(lines[e.idx]);
                break;
            }
            case R_UP: {
                sweep.erase(lines[e.idx]);
                break;
            }
            case L_DOWN: {
                auto it = ++sweep.emplace(lines[e.idx]).first;
                if (it != sweep.end())
                    trace[e.idx] = it->idx;
                break;
            }
            case R_DOWN: {
                auto it = ++sweep.lower_bound(lines[e.idx]);
                if (it != sweep.end())
                    trace[e.idx] = it->idx;
                sweep.erase(lines[e.idx]);
                break;
            }
        }
    }

    int ptr = n;
    int ans;
    while (trace[ptr] != -1) ptr = trace[ptr];
    if (lines[ptr].direction == LEFT) ans = lines[ptr].l.x;
    else ans = lines[ptr].r.x;
    cout << ans;

    return 0;
}
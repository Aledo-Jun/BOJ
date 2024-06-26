//
// Created by june0 on 2024-06-26.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
//#pragma GCC target("avx2")
//#pragma GCC optimize("O3,unroll-loops")
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
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

// Structure representing the position of the point
struct Point {
    ll x{}, y{};

    Point() = default;

    Point(ll x, ll y) : x(x), y(y) {}

    Point operator-(const Point &other) const {
        Point res(x - other.x, y - other.y);
        return res;
    }

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator<=(const Point &other) const {
        return *this < other || *this == other;
    }

    bool operator>(const Point &other) const {
        return !(*this < other) && !(*this == other);
    }

    bool operator>=(const Point &other) const {
        return *this > other || *this == other;
    }

    friend ostream &operator<<(ostream &out, const Point p) {
        out << p.x << ' ' << p.y << ' ';
        return out;
    }
};

ll dist(const Point &a, const Point &b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
// Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
int CCW(const Point &p1, const Point &p2, const Point &p3) {
    ll tmp = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y
             - p1.y * p2.x - p2.y * p3.x - p3.y * p1.x;
    if (tmp == 0) return 0;
    else if (tmp > 0) return 1;
    else return -1;
}

// Convex Hull algorithm that returns a stack of the indices of the points
// that forms the convex hull(clockwise from top to bottom of the stack).
deque<int> convexHull(vector<Point> &v) {
    int n = (int) v.size();
    if (n == 1) return {0};

    // Find the lowest point (leftmost, bottommost)
    int lowest = 0;
    for (int i = 1; i < n; i++) {
        if (v[i].y < v[lowest].y ||
            (v[i].y == v[lowest].y && v[i].x < v[lowest].x)) {
            lowest = i;
        }
    }

    // Swap the lowest point to the first position
    swap(v[0], v[lowest]);

    // Sort the points by polar angle from the lowest point
    auto cmp = [&](const Point &p1, const Point &p2) {
        auto diff1 = p1 - v[0];
        auto diff2 = p2 - v[0];
        ll cross = (ll) diff1.x * diff2.y - (ll) diff1.y * diff2.x;

        if (cross == 0) {
            // If two points have the same polar angle, choose the one closer to the origin
            return dist(p1, v[0]) < dist(p2, v[0]);
        }

        return cross > 0;
    };

    sort(v.begin() + 1, v.end(), cmp);

    deque<int> s;
    s.emplace_back(0);
    s.emplace_back(1);

    int next = 2;

    while (next < n) {
        while (s.size() >= 2) {
            int first, second;
            second = s.back();
            s.pop_back();
            first = s.back();

            if (CCW(v[first], v[second], v[next]) > 0) {
                s.emplace_back(second);
                break;
            }
        }
        s.emplace_back(next++);
    }
    return s;
}

// Identify whether the two lines(p1->p2, p3->p4) intersect or not using CCW.
bool doesIntersect(Point p1, Point p2, Point p3, Point p4) {
    auto res1 = CCW(p1, p2, p3) * CCW(p1, p2, p4);
    auto res2 = CCW(p3, p4, p1) * CCW(p3, p4, p2);

    if (res1 == 0 && res2 == 0) {
        if (p1 > p2) swap(p1, p2);
        if (p3 > p4) swap(p3, p4);

        return (p3 <= p2 && p1 <= p4);
    } else if (res1 <= 0 && res2 <= 0)
        return true;
    else
        return false;
}

int32_t main() {
    fastIO;
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<Point> black(n), white(m);
        for (auto &[x, y]: black) cin >> x >> y;
        for (auto &[x, y]: white) cin >> x >> y;
        if (n < m) {
            swap(black, white);
            swap(n, m);
        }
        if (n <= 1) {
            cout << "YES" << endl;
            continue;
        }

        auto hull1 = convexHull(black);
        hull1.emplace_back(hull1[0]);
        auto hull2 = convexHull(white);
        hull2.emplace_back(hull2[0]);

        bool flag1 = false; // check whether intersection exists between hull1 and hull2
        for (int i = 0; i < hull1.size() - 1; i++) {
            for (int j = 0; j < hull2.size() - 1; j++) {
                flag1 = doesIntersect(black[hull1[i]], black[hull1[i + 1]],
                                      white[hull2[j]], white[hull2[j + 1]]);
                if (flag1) break;
            }
            if (flag1) break;
        }

        bool flag2 = true;
        if (!flag1) { // they can be divided, or one completely contain the other
            if (black[hull1[0]].y > white[hull2[0]].y) { // make sure black is outside hull
                swap(black, white);
                swap(hull1, hull2);
            }
            for (const auto &p : white) { // check there's any point that is outside the hull1
                for (int i = 0; i < hull1.size() - 1; i++) {
                    if (CCW(black[hull1[i]], black[hull1[i + 1]], p) <= 0) {
                        flag2 = false;
                        break;
                    }
                }
                if (!flag2) break;
            }
        }

        cout << (flag1 || flag2 ? "NO" : "YES") << endl;
    }

    return 0;
}
//
// Created by june0 on 2024-10-13.
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

// Primary template: Not defined for unsupported types
template<typename T>
struct wider;

// Specialization for int
template<>
struct wider<int> {
    using type = long long;
};
template<>
struct wider<long long> {
    using type = __int128;
};

// Specialization for double
template<>
struct wider<double> {
    using type = long double;
};
template<>
struct wider<long double> {
    using type = __float128;
};

// Helper type alias for easier use
template<typename T>
using wider_t = typename wider<T>::type;


// Structure representing the position of the point
template<typename T = int>
struct Point_type {
    using value_type = T;
    T x{}, y{};

    Point_type() = default;

    Point_type(T x, T y) : x(x), y(y) {}

    Point_type operator+(const Point_type &other) const {
        Point_type res(x + other.x, y + other.y);
        return res;
    }
    Point_type operator-(const Point_type &other) const {
        Point_type res(x - other.x, y - other.y);
        return res;
    }
    Point_type operator*(T s) const {
        Point_type res(x * s, y * s);
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
        out << p.x << ' ' << p.y;
        return out;
    }
};

using Point = Point_type<int>;

template<typename T = Point::value_type, typename V = wider_t<T>>
V dist_square(const Point &a, const Point &b) {
    return V(a.x - b.x) * (a.x - b.x) + V(a.y - b.y) * (a.y - b.y);
}

// CounterClockWise algorithm that identifies the direction of the cross product of two vectors(p1->p2, p2->p3).
// Returns +1 when it's counterclockwise, -1 when it's clockwise, 0 when aligned.
template<typename T = Point::value_type, typename V = wider_t<T>>
int CCW(const Point &p1, const Point &p2, const Point &p3) {
    V tmp =  V(p1.x) * p2.y + V(p2.x) * p3.y + V(p3.x) * p1.y
             - V(p1.y) * p2.x - V(p2.y) * p3.x - V(p3.y) * p1.x;
    if (tmp == 0) return 0;
    else if (tmp > 0) return 1;
    else return -1;
}

// Convex Hull algorithm that returns a stack of the indices of the points
// that forms the convex hull(clockwise from top to bottom of the stack).
template<typename T = Point::value_type, typename V = wider_t<T>>
deque<int> convexHull(vector<Point> &v) {
    int n = (int) v.size();
    if (n <= 1) return {};

    sort(all(v));
    deque<int> hull;

    // Lower hull
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && CCW(v[hull[hull.size() - 2]], v[hull.back()], v[i]) <= 0)
            hull.pop_back();
        hull.push_back(i);
    }

    // Upper hull
    int t = (int) hull.size() + 1;
    for (int i = n - 2; i >= 0; i--) {
        while (hull.size() >= t && CCW(v[hull[hull.size() - 2]], v[hull.back()], v[i]) <= 0)
            hull.pop_back();
        hull.push_back(i);
    }

    hull.pop_back(); // Remove the duplicate point
    return hull;
}

// Find two points that represent the diameter of the convex hull of the given set of points.
// (the distance between the two points is maximal of the distances between the points in the given set)
template<typename T = Point::value_type, typename V = wider_t<T>,
        typename Dist_func = function<V(Point,Point)>>
pair<Point,Point> diameterOfConvexHull(vector<Point> &v, Dist_func dist = dist_square) {
    // deque of indices of points that form the convex hull.
    auto convex = convexHull(v);
    int m = (int) convex.size();

    int k = 1;
    pair<Point, Point> best_pair;
    V max_dist = 0;

    // Rotating calipers algorithm
    for (int i = 0; i < m; i++) {
        while (true) {
            V curr_dist = dist(v[convex[i]], v[convex[k]]);
            V next_dist = dist(v[convex[i]], v[convex[(k + 1) % m]]);
            if (next_dist > curr_dist) k = (k + 1) % m;
            else break;
        }
        V d = dist(v[convex[i]], v[convex[k]]);
        if (d > max_dist) {
            max_dist = d;
            best_pair = {v[convex[i]], v[convex[k]]};
        }
    }

    return best_pair;
}

template<typename T = Point::value_type, typename V = wider_t<T>,
        typename Dist_func = function<V(Point,Point)>>
pair<Point,Point> closestPointPair(vector<Point> &v, Dist_func dist = dist_square) {
    sort(all(v));

    auto dnc = [&](auto &&self, int l, int r) -> pair<Point,Point> {
        if (r - l <= 3) {
            pair<Point,Point> res;
            V mx = numeric_limits<V>::max();
            for (int i = l; i <= r; i++) {
                for (int j = i + 1; j <= r; j++) {
                    V d = dist(v[i], v[j]);
                    if (d < mx) {
                        mx = d;
                        res = {v[i], v[j]};
                    }
                }
            }
            return res;
        }

        int m = (l + r) >> 1;
        auto midPoint = v[m];

        auto [l1, l2] = self(self, l, m);
        V dl = dist(l1, l2);
        auto [r1, r2] = self(self, m+1, r);
        V dr = dist(r1, r2);

        V d = min(dist(l1, l2), dist(r1, r2));
        auto best = (dl < dr) ? make_pair(l1, l2) : make_pair(r1, r2);

        // Create a strip of points near the dividing line within distance d
        vector<Point> strip; strip.reserve(r-l+1);
        for (int i = l; i <= r; i++) {
            if (abs(dist(v[i], {midPoint.x, v[i].y})) < d) {
                strip.push_back(v[i]);
            }
        }
        // Sort the strip by y-coordinate for better efficiency
        sort(strip.begin(), strip.end(), [](const Point& a, const Point& b) { return a.y < b.y; });

        // Check for the closest pair in the strip
        V minStripDist = d;
        for (int i = 0; i < (int)strip.size(); i++) {
            for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) < minStripDist; j++) {
                V dStrip = dist(strip[i], strip[j]);
                if (dStrip < minStripDist) {
                    minStripDist = dStrip;
                    best = {strip[i], strip[j]};
                }
            }
        }
        return best;
    };

    return dnc(dnc, 0, v.size() - 1);
}

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<Point> v(n);
    for (auto &[x, y] : v) cin >> x >> y;

    auto euclidean = [](const Point &a, const Point &b) {
        return dist_square(a, b);
    };
    auto manhattan = [](const Point &a, const Point &b) {
        return abs(a.x - b.x) + abs(a.y - b.y);
    };
    auto chebyshev = [](const Point &a, const Point &b) {
        return max(abs(a.x - b.x), abs(a.y - b.y));
    };

    auto mx1 = diameterOfConvexHull(v, euclidean);
    auto mx2 = diameterOfConvexHull(v, manhattan);
    auto mx3 = diameterOfConvexHull(v, chebyshev);
    auto mn1 = closestPointPair(v, euclidean);
    auto mn2 = closestPointPair(v, manhattan);
    auto mn3 = closestPointPair(v, chebyshev);

    cout << euclidean(mx1.first, mx1.second) << endl;
    cout << euclidean(mn1.first, mn1.second) << endl;
    cout << manhattan(mx2.first, mx2.second) << endl;
    cout << manhattan(mn2.first, mn2.second) << endl;
    cout << chebyshev(mx3.first, mx3.second) << endl;
    cout << chebyshev(mn3.first, mn3.second) << endl;

    return 0;
}

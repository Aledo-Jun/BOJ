//
// Created by june0 on 2024-04-18.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
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

#ifdef NLINE_JUDGE // Be careful if problem is about strings.
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

        static bool IsBlank(char c) { return c == ' ' || c == '\t'; }

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
            for (; curr != '\t' && !IsEnd(curr); curr = _ReadChar())
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
            if (write_idx + sz >= SZ) Flush();
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

const int X_MIN = -10, X_MAX = 10;
const int Y_MIN = -20, Y_MAX = 20; // 섬이 -10~10이니 -20~20 밖으로는 안 나갈 듯?
const double STEP = 0.1;
const double eps = 1e-5;
const double INF = 1e100;

double sq(double x) { return x * x; }

// return the radiation per unit-time at the 'pos' of the grid
double radiation(const vector<double>& islands, double x, double y) {
    double res = 0;
    for (const auto& island : islands) {
        double dist_squared = sq(x) + sq(y - island);
        if (dist_squared < eps) return INF;
        res += 1 / dist_squared;
    }
    return res;
}

double y_2dot(const vector<double>& islands, double x, double y, double y_dot) {
    double ds_sq = 1 + sq(y_dot);

    double sum_radiation = 1; // nature radiation of 1
    double sum_first_term = 0; // -> sum(x - (y - island) * y_dot / dist^4)
    double sum_second_term = 0; // -> sum((y - c_i) / dist^4)

    for (const auto& island : islands) {
        double dist_sq = sq(x) + sq(y - island);
        sum_radiation += 1 / dist_sq;
        sum_first_term += (x + (y - island) * y_dot) / sq(dist_sq);
        sum_second_term += (y - island) / sq(dist_sq);
    }

    return 2 * ds_sq * (sum_first_term * y_dot - sum_second_term * ds_sq) / sum_radiation;
}

pair<double,double> RK(const vector<double>& islands, double x, double y, double y_dot) {
    double res = 0;
    for (int i = 0; i < int((X_MAX - X_MIN) / STEP); i++) {
        if (y < Y_MIN || y > Y_MAX) return {INF, y};

        res += STEP * (1 + radiation(islands, x, y)) * std::sqrt(1 + sq(y_dot));

        double k1 = STEP * y_dot;
        double l1 = STEP * y_2dot(islands, x, y, y_dot);
        /*
        double k2 = STEP * (y_dot + l1/2.0);
        double l2 = STEP * y_2dot(islands, x+STEP/2.0, y+k1/2.0, y_dot+l1/2.0);
        double k3 = STEP * (y_dot + l2/2.0);
        double l3 = STEP * y_2dot(islands, x+STEP/2.0, y+k2/2.0, y_dot+l2/2.0);
        double k4 = STEP * (y_dot + l3);
        double l4 = STEP * y_2dot(islands, x+STEP, y+k3, y_dot+l3);
        */
        x += STEP;
        y += k1;  // RK2: y += k2, RK4: y += (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0
        y_dot += l1;  // RK2: y_dot += l2, RK4: y_dot += (l1 + 2.0*l2 + 2.0*l3 + l4)/6.0
    }
    return {res, y};
}

double solve() {
    int n;
    double a, b;
    cin >> n >> a >> b;
    vector<double> islands(n);
    vector<double> initial_y_dot(2); // To find the initial y_dot
    initial_y_dot[0] = -2, initial_y_dot[1] = 2;
    for (auto& e : islands) {
        cin >> e;
        initial_y_dot.emplace_back((e - a) / 10);
    }
    sort(initial_y_dot.begin(), initial_y_dot.end());

    double ans = INF;
    for (int i = 1; i < n + 2; i++) {
        // 초기값에 따라 optimal한 도착지가 어딘지 확인
        double l = initial_y_dot[i - 1], r = initial_y_dot[i];
        double tmp = INF; // initial value needed
        while (std::abs(r - l) > eps) {
            double m = (l + r) / 2;
            const auto& [res, y] = RK(islands, -10, a, m);
            if (y >= b) r = m;
            else l = m;
            tmp = res;
        }
        ans = min(ans, tmp);
    }
    return ans;
}

int32_t main() {
    fastIO;
    int t;
    cin >> t;
    cout << fixed << setprecision(10);
    for (int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": " << solve() << endl;
    }

    return 0;
}
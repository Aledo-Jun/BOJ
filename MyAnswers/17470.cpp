//
// Created by june0 on 2024-10-05.
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

const int delim = 1000;

int32_t main() {
    fastIO;
    int n, m, r, c, t;
    cin >> n >> m >> t;
    matrix<int> ori(n, vector<int>(m)), v, w(m, vector<int>(n));
    for (auto &row : ori) for (auto &cell : row) cin >> cell;

    if (n < 4 || m < 4) {
        r = n, c = m;
        v = ori;
    }
    else {
        r = 4, c = 4;
        v = {{      0,       0 + delim * (m/2 - 1),       0 + delim * m/2,       0 + delim * (m-1)},
             {n/2 - 1, n/2 - 1 + delim * (m/2 - 1), n/2 - 1 + delim * m/2, n/2 - 1 + delim * (m-1)},
             {    n/2,     n/2 + delim * (m/2 - 1),     n/2 + delim * m/2,     n/2 + delim * (m-1)},
             {    n-1,     n-1 + delim * (m/2 - 1),     n-1 + delim * m/2,     n-1 + delim * (m-1)}};
        w = matrix<int>(4, vector<int>(4));
    }

    auto up_down = [&]() {
        for (int i = 0; i < r / 2; i++) {
            swap(v[i], v[r - i - 1]);
        }
    };
    auto left_right = [&]() {
        for (auto &row : v)
            for (int j = 0; j < c / 2; j++) swap(row[j], row[c - j - 1]);
    };
    auto clockwise = [&]() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                w[j][r - i - 1] = v[i][j];
            }
        }
        swap(r, c);
        swap(n, m);
        v.swap(w);
    };
    auto counterclockwise = [&]() {
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                w[c - j - 1][i] = v[i][j];
            }
        }
        swap(r, c);
        swap(n, m);
        v.swap(w);
    };
    auto clockwise_seg = [&]() {
        matrix<int> A(r / 2, vector<int>(c / 2));
        for (int i = 0; i < r / 2; i++)
            for (int j = 0; j < c / 2; j++) A[i][j] = v[i][j];

        for (int i = 0; i < r / 2; i++)
            for (int j = 0; j < c / 2; j++) {
                v[i][j] = v[i + r/2][j];
                v[i + r/2][j] = v[i + r/2][j + c/2];
                v[i + r/2][j + c/2] = v[i][j + c/2];
                v[i][j + c/2] = A[i][j];
            }
    };
    auto counterclockwise_seg = [&]() {
        matrix<int> A(r / 2, vector<int>(c / 2));
        for (int i = 0; i < r / 2; i++)
            for (int j = 0; j < c / 2; j++) A[i][j] = v[i][j];

        for (int i = 0; i < r / 2; i++)
            for (int j = 0; j < c / 2; j++) {
                v[i][j] = v[i][j + c/2];
                v[i][j + c/2] = v[i + r/2][j + c/2];
                v[i + r/2][j + c/2] = v[i + r/2][j];
                v[i + r/2][j] = A[i][j];
            }
    };

    vector<int> cmds(t);
    for (auto &e : cmds) cin >> e;
//    for (int i = 0, j = i + 1; i < t; i = j, j = i + 1) {
//        if (cmds[i] == 1 || cmds[i] == 2) {
//            while (cmds[j] == cmds[i]) {
//                cmds[j] = -1;
//                j++;
//            }
//            if (~(j - i) & 1) cmds[i] = -1;
//        }
//        else if (cmds[i] == 3 || cmds[i] == 4) {
//            int cnt = cmds[i] == 3;
//            while (cmds[j] == 3 || cmds[j] == 4) {
//                if (cmds[j] == 3) cnt++;
//                cmds[j] = -1;
//                j++;
//            }
//            cnt = cnt - (j - i - cnt);
//            if (cnt == 0) cmds[i] = -1;
//            if (cnt > 0) {
//                cnt %= 4;
//                if (cnt == 3) cmds[i] = 4;
//                if (cnt == 2) cmds[i+1] = cmds[i];
//            }
//            if (cnt < 0) {
//                cmds[i] = 4;
//                cnt = -cnt;
//                cnt %= 4;
//                if (cnt == 3) cmds[i] = 3;
//                if (cnt == 2) cmds[i+1] = cmds[i];
//            }
//        }
//        else {
//            int cnt = cmds[i] == 5;
//            while (cmds[j] == 5 || cmds[j] == 6) {
//                if (cmds[j] == 5) cnt++;
//                cmds[j] = -1;
//                j++;
//            }
//            cnt = cnt - (j - i - cnt);
//            if (cnt == 0) cmds[i] = -1;
//            if (cnt > 0) {
//                cnt %= 4;
//                if (cnt == 3) cmds[i] = 6;
//                if (cnt == 2) cmds[i+1] = cmds[i];
//            }
//            if (cnt < 0) {
//                cmds[i] = 6;
//                cnt = -cnt;
//                cnt %= 4;
//                if (cnt == 3) cmds[i] = 5;
//                if (cnt == 2) cmds[i+1] = cmds[i];
//            }
//        }
//    }

    for (const auto &cmd : cmds) {
        switch (cmd) {
            case 1:
                up_down();
                break;
            case 2:
                left_right();
                break;
            case 3:
                clockwise();
                break;
            case 4:
                counterclockwise();
                break;
            case 5:
                clockwise_seg();
                break;
            case 6:
                counterclockwise_seg();
                break;
            default:
                continue;
        }
    }

    if (n < 4 || m < 4) {
        for (const auto &row: v) {
            for (const auto &cell: row) cout << cell << ' ';
            cout << endl;
        }
    } else {
        matrix<int> ans(n, vector<int>(m));

        auto decomp = [&](int x1, int y1, int x2, int y2, int x0, int y0) {
            int X = x0;
            int Y = y0;
            if ((v[x1][y1]%delim < v[x2][y1]%delim) && (v[x1][y1]/delim < v[x1][y2]/delim)) {
                for (int i = v[x1][y1]%delim; i <= v[x2][y1]%delim; i++) {
                    for (int j = v[x1][y1]/delim; j <= v[x1][y2]/delim; j++) {
                        ans[X][Y++] = ori[i][j];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim < v[x2][y1]%delim) && (v[x1][y1]/delim > v[x1][y2]/delim)) {
                for (int i = v[x1][y1]%delim; i <= v[x2][y1]%delim; i++) {
                    for (int j = v[x1][y1]/delim; j >= v[x1][y2]/delim; j--) {
                        ans[X][Y++] = ori[i][j];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim > v[x2][y1]%delim) && (v[x1][y1]/delim < v[x1][y2]/delim)) {
                for (int i = v[x1][y1]%delim; i >= v[x2][y1]%delim; i--) {
                    for (int j = v[x1][y1]/delim; j <= v[x1][y2]/delim; j++) {
                        ans[X][Y++] = ori[i][j];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim > v[x2][y1]%delim) && (v[x1][y1]/delim > v[x1][y2]/delim)) {
                for (int i = v[x1][y1]%delim; i >= v[x2][y1]%delim; i--) {
                    for (int j = v[x1][y1]/delim; j >= v[x1][y2]/delim; j--) {
                        ans[X][Y++] = ori[i][j];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim < v[x1][y2]%delim) && (v[x1][y1]/delim < v[x2][y1]/delim)) {
                for (int i = v[x1][y1]/delim; i <= v[x2][y1]/delim; i++) {
                    for (int j = v[x1][y1]%delim; j <= v[x1][y2]%delim; j++) {
                        ans[X][Y++] = ori[j][i];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim < v[x1][y2]%delim) && (v[x1][y1]/delim > v[x2][y1]/delim)) {
                for (int i = v[x1][y1]/delim; i >= v[x2][y1]/delim; i--) {
                    for (int j = v[x1][y1]%delim; j <= v[x1][y2]%delim; j++) {
                        ans[X][Y++] = ori[j][i];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim > v[x1][y2]%delim) && (v[x1][y1]/delim < v[x2][y1]/delim)) {
                for (int i = v[x1][y1]/delim; i <= v[x2][y1]/delim; i++) {
                    for (int j = v[x1][y1]%delim; j >= v[x1][y2]%delim; j--) {
                        ans[X][Y++] = ori[j][i];
                    }
                    X++;
                    Y = y0;
                }
            }
            else if ((v[x1][y1]%delim > v[x1][y2]%delim) && (v[x1][y1]/delim > v[x2][y1]/delim)) {
                for (int i = v[x1][y1]/delim; i >= v[x2][y1]/delim; i--) {
                    for (int j = v[x1][y1]%delim; j >= v[x1][y2]%delim; j--) {
                        ans[X][Y++] = ori[j][i];
                    }
                    X++;
                    Y = y0;
                }
            }
        };

        decomp(0, 0, 1, 1, 0, 0);
        decomp(0, 2, 1, 3, 0, m/2);
        decomp(2, 0, 3, 1, n/2, 0);
        decomp(2, 2, 3, 3, n/2, m/2);

        for (const auto &row : ans) {
            for (const auto &cell : row) cout << cell << ' ';
            cout << endl;
        }
    }

    return 0;
}

//
// Created by june0 on 2024-05-02.
//

#ifndef BOJ_MO_S_HPP
#define BOJ_MO_S_HPP

#include <vector>
#include <algorithm>

namespace MoTemplate {
    int n, sqrt_n, m;

    struct query {
        int l, r, idx;
        /* Add extra variables */

        bool operator<(const query &other) const {
            if (l / sqrt_n == other.l / sqrt_n)
                return ((l / sqrt_n) & 1) ? r < other.r : r > other.r;
            return l < other.l;
        }
    };

    class Mo {
    private:
        std::vector<int> v;
        std::vector<query> q;
        std::vector<int> ans;
        int res; // if the res can be maintained, use this.

        void add(int i) {
            // Do something
        }
        void del(int i) {
            // Do something
        }
        int solve(int k) {
            // if res cannot be maintained, do this instead.
            int ret = 0;
            // Do something if needed
            return ret;
        }
    public:
        Mo(const std::vector<int>& v, const std::vector<query>& q) : v(v), q(q) {
            std::sort(this->q.begin(), this->q.end());
            ans.resize(q.size());
        }
        void go() {
            res = 0;
            int s = q[0].l, e = s - 1;

            for (const auto &[l, r, idx]: q) {
                while (s > l) add(--s);
                while (e < r) add(++e);
                while (s < l) del(s++);
                while (e > r) del(e--);

                ans[idx] = res;
            }
        }
    };
}

#endif //BOJ_MO_S_HPP

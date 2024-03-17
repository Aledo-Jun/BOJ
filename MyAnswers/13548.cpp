//
// Created by june0 on 2024-03-17.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

//
/// "Premature optimization is the root of all evil." -- Donald Knuth
//

int sqrtN;
struct query {
    int l, r, idx;

    bool operator<(const query& other) const {
        if (l / sqrtN == other.l / sqrtN)
            return (l / sqrtN & 1) ? r < other.r : r > other.r;
        return l < other.l;
    }
};

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v) cin >> e;
    sqrtN = (int) sqrt(n);

    int q;
    cin >> q;
    vector<query> Q(q);
    for (int i = 0; i < q; i++){
        cin >> Q[i].l >> Q[i].r;
        Q[i].l--, Q[i].r--;
        Q[i].idx = i;
    }
    sort(Q.begin(), Q.end());

    const int MAX = 100'000;
    vector<int> cnt(MAX + 1, 0),cnt_cnt(MAX + 1, 0);
    vector<int> ans(q);
    int mx = 0;

    auto add = [&](int x){
        cnt_cnt[cnt[x]]--;
        cnt[x]++;
        cnt_cnt[cnt[x]]++;
        mx = max(mx, cnt[x]);
    };
    auto del = [&](int x){
        if (cnt[x] == mx && cnt_cnt[cnt[x]] == 1) mx--;
        cnt_cnt[cnt[x]]--;
        cnt[x]--;
        cnt_cnt[cnt[x]]++;
    };

    auto [l, r, _] = Q[0];
    for (int i = l; i <= r; i++) {
        add(v[i]);
    }
    for (const auto& [nl, nr, idx]: Q){
        for (int i = l; i < nl; i++) del(v[i]);
        for (int i = nl; i < l; i++) add(v[i]);
        for (int i = r + 1; i <= nr; i++) add(v[i]);
        for (int i = nr + 1; i <= r; i++) del(v[i]);

        ans[idx] = mx;

        l = nl, r = nr;
    }

    for (const auto& e : ans) cout << e << endl;

    return 0;
}
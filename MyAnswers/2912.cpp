//
// Created by june0 on 2024-03-15.
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


int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (auto& e : v) cin >> e;
    int sqrtN = (int) sqrt(n);

    int q, id = 0;
    cin >> q;
    vector<tuple<int,int,int>> query(q);
    for (auto& [l, r, idx]: query) {
        cin >> l >> r;
        l--, r--;
        idx = id++;
    }
    sort(query.begin(), query.end(), [&](const auto& a, const auto& b){
        if (get<0>(a) / sqrtN == get<0>(b) / sqrtN) return get<1>(a) < get<1>(b);
        return get<0>(a) < get<0>(b);
    });

    vector<int> cnt(m + 1), ans(q, -1);
    auto [l, r, _] = query[0];
    for (int i = l; i <= r; i++) cnt[v[i]]++;
    for (const auto& [nl, nr, idx]: query){
        for (int i = l; i < nl; i++) cnt[v[i]]--;
        for (int i = nl; i < l; i++) cnt[v[i]]++;
        for (int i = r + 1; i <= nr; i++) cnt[v[i]]++;
        for (int i = nr + 1; i <= r; i++) cnt[v[i]]--;

        for (int i = 1; i <= m; i++){
            if (cnt[i] > (nr - nl + 1) / 2) {
                ans[idx] = i;
                break;
            }
        }
        l = nl, r = nr;
    }

    for (const auto& e : ans) {
        if (e == -1) cout << "no" << endl;
        else cout << "yes " << e << endl;
    }

    return 0;
}

#ifdef ANOTHER_SOLUTION
/**
 * This solution uses random algorithm
 * Read the comments below
 */
int32_t main() {
    fastIO;
    int n, m;
    cin >> n >> m;
    vector<int> v(n + 1);
    matrix<int> idx(m + 1);
    for (int i = 1; i <= n; i++){
        cin >> v[i];
        idx[v[i]].emplace_back(i);
    }

    int q;
    cin >> q;

    random_device random;
    mt19937 rd(random());

    while (q--){
        int l, r, ans = -1;
        cin >> l >> r;
        for (int i = 0; i < 15; i++) {
            int x = uniform_int_distribution<>(l, r)(rd); // choose random number in [l, r]
            // counts the number of v[x] in range v[l, r]
            int cnt = upper_bound(idx[v[x]].begin(), idx[v[x]].end(), r) - lower_bound(idx[v[x]].begin(), idx[v[x]].end(), l);
            if (cnt > (r - l + 1) / 2) {
                // if exists, it's the answer
                ans = v[x];
                break;
            }
            // the probability that answer exists but not found by random choice is under 2^(-15)
        }
        if (ans != -1)
            cout << "yes " << ans << endl;
        else
            cout << "no" << endl;
    }

    return 0;
}

#endif
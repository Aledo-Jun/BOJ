//
// Created by june0 on 2024-01-31.
//
#include <bits/stdc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define int long long
using namespace std;

int32_t main() {
    fastIO;
    int tc; cin >> tc;
    while (tc--) {
        int n, x;
        cin >> n >> x;
        vector<int> v(n), prefix(n);
        for (auto& e : v) cin >> e;
        prefix[0] = v[0];
        for (int i = 1; i < n; i++) prefix[i] = v[i] + prefix[i - 1];

        vector<pair<int,int>> q;
        q.emplace_back(0, -1);
        int ans = INT_MAX;
        for (int i = 0; i < n; i++){
            int threshold = prefix[i] - x;
            // find the largest element over the threshold, i.e. prev(it)
            auto it = upper_bound(q.begin(), q.end(), make_pair(threshold, 0LL),
                                  [&](const auto& p1, const auto& p2){ return p1.first < p2.first; });

            if (it != q.begin()) ans = min(ans, i - prev(it)->second);

            while (!q.empty() && q.back().first >= prefix[i]) q.pop_back();

            q.emplace_back(prefix[i], i);
        }

        cout << (ans == INT_MAX ? -1 : ans) << endl;
    }

    return 0;
}
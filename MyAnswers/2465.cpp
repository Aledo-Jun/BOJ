//
// Created by june0 on 2024-01-30.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
using namespace std;
using namespace __gnu_cxx;

int32_t main() {
    fastIO;
    int n;
    cin >> n;
    vector<int> v(n);
    for (auto& e : v) cin >> e;
    sort(v.begin(), v.end());

    vector<int> s(n);
    for (auto& e : s) cin >> e;
    reverse(s.begin(), s.end());

    rope<int> rp;
    for (int i = 0; i < n; i++) rp.push_back(i);

    vector<int> ans;
    for (const auto& e : s){
        auto it = rp.mutable_begin();
        advance(it, e);
        int idx = *it;
        rp.erase(it);
        ans.push_back(v[idx]);
    }
    reverse(ans.begin(), ans.end());

    for (const auto& e : ans) cout << e << ' ';

    return 0;
}
//
// Created by june0 on 2024-03-07.
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

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEnd;

    TrieNode() {
        children.clear();
        isEnd = false;
    }
};

void insertWord(TrieNode* root, const string &word) {
    TrieNode *current = root;

    for (char c: word) {
        if (!current->children[c])
            current->children[c] = new TrieNode;

        current = current->children[c];
    }
    current->isEnd = true;
}

using BIT = bitset<2048>;
BIT find_prefix(TrieNode* root, const string& word, const bool name_flag = false){
    TrieNode *current = root;
    BIT res;
    res.reset();

    for (int i = 0; i < word.size(); i++) {
        char c = word[i];

        if (current->children.find(c) == current->children.end())
            break;

        current = current->children[c];

        if (current->isEnd) {
            if (name_flag) res.set(word.size() - 1 - i);
            else res.set(i + 1);
        }
    }

    return res;
}

int32_t main() {
    fastIO;
    int c, n;
    cin >> c >> n;
    auto* colors = new TrieNode;
    auto* names = new TrieNode;
    for (int i = 0; i < c; i++){
        string color;
        cin >> color;
        insertWord(colors, color);
    }
    for (int i = 0; i < n; i++){
        string name;
        cin >> name;
        reverse(name.begin(), name.end());
        insertWord(names, name);
    }

    int t;
    cin >> t;
    while (t--){
        string curr;
        cin >> curr;

        auto indices1 = find_prefix(colors, curr);
        if (indices1.none()) {
            cout << "No" << endl;
            continue;
        }

        reverse(curr.begin(), curr.end());
        auto indices2 = find_prefix(names, curr, true);
        if (indices2.none()) {
            cout << "No" << endl;
            continue;
        }

        if ((indices1 & indices2).any()) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    delete colors;
    delete names;

    return 0;
}
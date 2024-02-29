//
// Created by june0 on 2024-02-29.
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

// Trie data structure for checking the existence of the prefix
// Note : the insertion process should be in sorted order
struct TrieNode {
    TrieNode *children[27]{};

    TrieNode() {
        for (auto &i: children)
            i = nullptr;
    }

    ~TrieNode() {
        for (auto &i: children)
            delete i;
    }
};

void insertWord(TrieNode *root, const string &word) {
    TrieNode *current = root;

    for (char c: word) {
        int index = c - 'a';

        if (current->children[index] == nullptr)
            current->children[index] = new TrieNode();

        current = current->children[index];
    }
    current->children[26] = new TrieNode();
}

bool is_there_only_child(TrieNode *node){
    int cnt = 0;
    for (const auto& child : node->children){
        if (child != nullptr) cnt++;
    }
    return cnt == 1;
}

int32_t main() {
    fastIO;
    int n;
    while (cin >> n){
        vector<string> words(n);
        auto* trie = new TrieNode();
        for (auto& word : words){
            cin >> word;
        }
        sort(words.begin(), words.end());
        for (auto& word : words) insertWord(trie, word);

        int ans = 0;
        for (const auto& word : words){
            int cnt = 1, idx = 0;
            TrieNode* curr = trie->children[word[idx] - 'a'];
            while (idx < word.size() - 1){
                if (is_there_only_child(curr)){
                    curr = curr->children[word[++idx] - 'a'];
                } else {
                    curr = curr->children[word[++idx] - 'a'];
                    cnt++;
                }
            }
            ans += cnt;
        }

        cout << fixed << setprecision(2);
        cout << (lld)ans / n << endl;

        delete trie;
    }

    return 0;
}
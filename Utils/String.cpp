#include <string>
#include <vector>
using ull = unsigned long long;

using namespace std;

namespace string_utils {

    // Trie data structure for checking the existence of the prefix
    // Note : the insertion process should be in sorted order
    struct TrieNode {
        TrieNode* children[10]{};
        bool isEnd;

        TrieNode() {
            for (auto & i : children)
                i = nullptr;
            isEnd = false;
        }
    };

    bool insertWord(TrieNode* root, const string& word) {
        TrieNode* current = root;

        for (char c : word) {
            int index = c - '0';

            if (current->children[index] == nullptr)
                current->children[index] = new TrieNode();

            current = current->children[index];

            if (current->isEnd)
                return true; // Prefix found, return true
        }
        current->isEnd = true;

        return false;
    }

    bool can_be_palindrome(const string& s, int start, int end) {
        while (start < end) {
            if (s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    }

    // Find pattern's partial matches(failure table) for KMP algorithm
    vector<int> getPartialMatch(const string& P){
        ull m = P.length();
        vector<int> pi(m, 0);
        int match = 0;
        for (int i = 1; i < m; i++){
            while (match > 0 && P[i] != P[match])
                match = pi[match - 1];
            if (P[i] == P[match])
                pi[i] = ++match;
        }
        return pi;
    }

    // KMP algorithm to find the position of T's substring that matches P
    vector<int> kmpSearch(const string& T, const string& P){
        ull n = T.length();
        ull m = P.length();
        vector<int> result;
        vector<int> pi = getPartialMatch(P);
        int match = 0;
        for (int i = 0; i < n; i++){
            while (match > 0 && T[i] != P[match])
                match = pi[match - 1];
            if (T[i] == P[match]){
                match++;
                if (match == m){
                    result.push_back(i - m + 1);
                    match = pi[match - 1];
                }
            }
        }
        return result;
    }

}// End string_utils


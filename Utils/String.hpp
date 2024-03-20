#include <string>
#include <vector>
#include <memory>
#include <queue>
using ull = unsigned long long;

using namespace std;

namespace Utils
{
namespace String
{
    // Trie data structure for checking the existence of the prefix
    struct TrieNode {
        TrieNode *children[10]{}; // may adjust size
        int cnt; // how many elements are in this Trie that include *this
        bool isEnd;

        TrieNode() {
            for (auto &i: children)
                i = nullptr;
            isEnd = false;
        }

        void insert(const string& word) {
            TrieNode *current = this;

            for (char c: word) {
                int index = c - '0';

                if (current->children[index] == nullptr)
                    current->children[index] = new TrieNode();

                current = current->children[index];
                current->cnt++;
            }
        }

        void erase(const string& word) {
            TrieNode *current = this;

            for (char c: word) {
                int index = c - '0';
                current = current->children[index];
                current->cnt--;
            }
        }

        int query(const string& word) {
            int n = (int) word.size();
            TrieNode *current = this;

            int result = 0;
            for (int i = 0; i < n; i++) {
                int index = word[i] - '0';
                // Do something
            }
            return result;
        }
    };

 /**
 * Aho-Corasick algorithm for string-searching in linear time
 * @tparam size size of the input character set(default is english alphabet, 26)
 * @tparam base the starting character of the set above(default is 'a')
 */
    template<int size = 26, char base = 'a'>
    class Aho_Corasick {
    private:
        struct TrieNode {
            std::unique_ptr<TrieNode> children[size]{};
            TrieNode* fail;
            bool isEnd;

            TrieNode() : isEnd(false), fail(nullptr) {
                fill(children, children + size, nullptr);
            }

            void insert(const string& word) {
                TrieNode* current = this;
                for (char c: word) {
                    int index = c - base;
                    if (current->children[index] == nullptr)
                        current->children[index] = make_unique<TrieNode>();

                    current = current->children[index].get();
                }
                current->isEnd = true;
            }
        };

        TrieNode* root;
        bool is_initialized = false;

    public:
        void init() {
            queue<TrieNode*> q;
            q.emplace(root);
            root->fail = root;

            while (!q.empty()) {
                auto current = q.front();
                q.pop();
                for (int i = 0; i < size; i++) {
                    auto next = current->children[i].get();
                    if (next == nullptr) continue;

                    if (current == root) next->fail = root;
                    else {
                        auto fail_node = current->fail;
                        while (fail_node != root && fail_node->children[i] == nullptr)
                            fail_node = fail_node->fail;
                        if (fail_node->children[i] != nullptr) fail_node = fail_node->children[i].get();

                        next->fail = fail_node;
                    }
                    if (next->fail->isEnd) next->isEnd = true;

                    q.emplace(next);
                }
            }
        }

        void insert(const string& word) {
            root->insert(word);
        }

        Aho_Corasick() : root(new TrieNode) {}

        bool find(const string& word) {
            if (!is_initialized) {
                init();
                is_initialized = true;
            }
            auto current = root;
            for (const auto& c: word) {
                int index = c - base;
                while (current != root && current->children[index] == nullptr)
                    current = current->fail;
                if (current->children[index] != nullptr) current = current->children[index].get();
                if (current->isEnd) return true;
            }
            return false;
        }
    };

    // Find pattern's partial matches(failure table) for KMP algorithm
    vector<int> getPartialMatch(const string &P) {
        ull m = P.length();
        vector<int> pi(m, 0);
        int match = 0;
        for (int i = 1; i < m; i++) {
            while (match > 0 && P[i] != P[match])
                match = pi[match - 1];
            if (P[i] == P[match])
                pi[i] = ++match;
        }
        return pi;
    }

    // KMP algorithm to find the position of T's substring that matches P
    vector<int> kmpSearch(const string &T, const string &P) {
        ull n = T.length();
        ull m = P.length();
        vector<int> result;
        vector<int> pi = getPartialMatch(P);
        int match = 0;
        for (int i = 0; i < n; i++) {
            while (match > 0 && T[i] != P[match])
                match = pi[match - 1];
            if (T[i] == P[match]) {
                match++;
                if (match == m) {
                    result.push_back(i - m + 1);
                    match = pi[match - 1];
                }
            }
        }
        return result;
    }

} // namespace String
} // namespace Utils
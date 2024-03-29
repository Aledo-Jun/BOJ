#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <functional>
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
     * @tparam IndexSize size of the input character set(default is english alphabet, 26)
     */
     template<int IndexSize = 26>
     class Aho_Corasick {
         using Index_Fn = function<int(unsigned char)>;
     private:
         struct TrieNode {
             TrieNode* children[IndexSize];
             TrieNode* fail;
             int isEndOf;

             TrieNode() : isEndOf(-1), fail(nullptr) {
                 fill(children, children + IndexSize, nullptr);
             }
             ~TrieNode() {
                 for (auto child : children) delete child;
             }

             void insert(const string& word, int& sz, const Index_Fn& index_of) {
                 TrieNode* current = this;
                 for (const auto c: word) {
                     int index = index_of(c);
                     if (current->children[index] == nullptr)
                         current->children[index] = new TrieNode;

                     current = current->children[index];
                 }
                 current->isEndOf = sz++;
             }
         };

         TrieNode* _root_;
         bool is_initialized = false;
         int _size_;
         Index_Fn _index_fn_;

     public:
         explicit Aho_Corasick(Index_Fn index_fn) : _root_(new TrieNode), _size_(0), _index_fn_(std::move(index_fn)) {}

         ~Aho_Corasick() { delete _root_; }

         void init() {
             queue<TrieNode*> q;
             q.emplace(_root_);
             _root_->fail = _root_;

             while (!q.empty()) {
                 auto current = q.front();
                 q.pop();
                 for (int i = 0; i < IndexSize; i++) {
                     auto next = current->children[i];
                     if (next == nullptr) continue;

                     if (current == _root_) next->fail = _root_;
                     else {
                         auto fail_node = current->fail;
                         while (fail_node != _root_ && fail_node->children[i] == nullptr)
                             fail_node = fail_node->fail;
                         if (fail_node->children[i] != nullptr) fail_node = fail_node->children[i];

                         next->fail = fail_node;
                     }
                     if (next->fail->isEndOf != -1)
                         next->isEndOf = next->fail->isEndOf;

                     q.emplace(next);
                 }
             }
         }

         void insert(const string& word) {
             _root_->insert(word, _size_, _index_fn_);
         }

         int count(const string& word) {
             if (!is_initialized) {
                 init();
                 is_initialized = true;
             }

             int res = 0;
             auto current = _root_;
             for (const auto c : word) {
                 int index = _index_fn_(c);
                 while (current != _root_ && current->children[index] == nullptr)
                     current = current->fail;
                 if (current->children[index] != nullptr)
                     current = current->children[index];

                 if (current->isEndOf != -1) {
                     res++;
                 }
             }
             return res;
         }

         void clear() {
             delete _root_;
             _root_ = new TrieNode;
             is_initialized = false;
             _size_ = 0;
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

    /// @Ref <a href="https://gist.github.com/koosaga/44532e5dec947132ee55da0458255e05">koosaga</a>
    class SuffixArray {
    private:
        std::string str;
        int n;

        std::vector<int> ord, nord;
        std::vector<int> cnt, aux; // for counting sort
        std::vector<int> sfx, rev, lcp;

    public:
        explicit SuffixArray(const std::string& s) : str(s), n((int)s.size()),
                                                     ord(n + 1), nord(n + 1),
                                                     cnt(std::max(256, n + 1)), aux(n),
                                                     sfx(n), rev(n), lcp(n)
        {
            int p = 1;
            std::fill(ord.begin(), ord.end(), 0);
            for (int i = 0; i < n; i++) {
                sfx[i] = i;
                ord[i] = (unsigned char)str[i];
            }

            int pnt = 1;
            while (true) {
                std::fill(cnt.begin(), cnt.end(), 0);
                for (int i = 0; i < n; i++)
                    cnt[ord[std::min(i + p, n)]]++;
                for (int i = 1; i <= n || i <= 255; i++)
                    cnt[i] += cnt[i - 1];
                for (int i = n - 1; i >= 0; i--)
                    aux[--cnt[ord[std::min(i + p, n)]]] = i;

                std::fill(cnt.begin(), cnt.end(), 0);
                for (int i = 0; i < n; i++)
                    cnt[ord[i]]++;
                for (int i = 1; i <= n || i <= 255; i++)
                    cnt[i] += cnt[i - 1];
                for (int i = n - 1; i >= 0; i--)
                    sfx[--cnt[ord[aux[i]]]] = aux[i];

                if (pnt == n) break;
                else pnt = 1;

                nord[sfx[0]] = 1;
                for (int i = 1; i < n; i++){
                    if (ord[sfx[i - 1]] != ord[sfx[i]] || ord[sfx[i - 1] + p] != ord[sfx[i] + p])
                        pnt++;
                    nord[sfx[i]] = pnt;
                }
                ord = nord;
                p *= 2;
            }
            for (int i = 0; i < n; i++) rev[sfx[i]] = i;

            // LCP
            int h = 0;
            for (int i = 0; i < n; i++) {
                if (rev[i]) {
                    int prev = sfx[rev[i] - 1];
                    while (str[prev + h] == str[i + h]) h++;
                    lcp[rev[i]] = h;
                }
                h = std::max(h - 1, 0);
            }
        }

        int operator[](int i) { return sfx[i]; }
        std::vector<int> get_lcp() { return lcp; }
    };
} // namespace String
} // namespace Utils
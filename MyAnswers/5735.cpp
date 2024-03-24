//
// Created by june0 on 2024-03-24.
//
#include <bits/stdc++.h>
#include <bits/extc++.h>

#define fastIO ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define endl '\n'
#define all(v) (v).begin(), (v).end()
using namespace std;
using namespace __gnu_cxx;
using ll [[maybe_unused]] = long long;
using ull [[maybe_unused]] = unsigned long long;
using lll [[maybe_unused]] = __int128;
using lld [[maybe_unused]] = long double;
template<typename T> using graph [[maybe_unused]] = vector<vector<pair<int,T>>>;
template<typename T> using matrix [[maybe_unused]] = vector<vector<T>>;

/**
 *  "Premature optimization is the _root_ of all evil."
 *  <sub> Donald Knuth </sub>
 */

vector<int> len_of_pattern;

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
    void insert(const string& word, int idx) {
        _root_->insert(word, idx, _index_fn_);
    }

    int match(const string& word) {
        if (!is_initialized) {
            init();
            is_initialized = true;
        }

        int ret = 0;

        auto current = _root_;
        for (char c : word) {
            int index = _index_fn_(c);
            while (current != _root_ && current->children[index] == nullptr)
                current = current->fail;
            if (current->children[index] != nullptr)
                current = current->children[index];

            if (current->isEndOf != -1) {
                ret++;
                current = _root_;
            }
        }
        return ret;
    }

    void clear() {
        delete _root_;
        _root_ = new TrieNode;
        is_initialized = false;
        _size_ = 0;
    }
};

int32_t main() {
    fastIO;
    string special = "!?.,:;-_'#$%&/=*+(){}[] ";
    unordered_map<char,int> char_set;
    int id = 0;
    for (int i = 0; i < 10; i++) char_set[char('0' + i)] = id++;
    for (int i = 0; i < 26; i++) char_set[char('a' + i)] = id++;
    for (int i = 0; i < 26; i++) char_set[char('A' + i)] = id++;
    for (char c : special) char_set[c] = id++;

    int n, m;
    while (cin >> n >> m){
        if (n == 0) break;

        Aho_Corasick<52 + 10 + 24> solver([&](const char c){
            return char_set[c];
        });

        len_of_pattern.resize(n);
        string s;
        for (int i = 0; i < n; i++){
            cin >> s;
            solver.insert(s);
            len_of_pattern[i] = (int)s.size();
        }
        cin.ignore();
        int ans = 0;
        for (int i = 0; i < m; i++){
            getline(cin, s);
            ans += solver.match(s);
        }
        cout << ans << endl;
    }

    return 0;
}
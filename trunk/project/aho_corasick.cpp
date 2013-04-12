/**
 * @file aho_corasick.cpp
 * @brief 
 * @author 3xian
 * @version 1.2
 */

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

template <typename CharType>
class AhoCorasick
{
public:
    AhoCorasick() {
        clear();
    }

    ~AhoCorasick() {
    }

    void clear() {
        word_count_ = 0;
        root_offset_ = 0;
        nodes_.clear();
        nodes_.push_back(Node());  // root
    }

    int word_count() const {
        return word_count_;
    }

    // it would cover old id when inserting same string
    void insert(const CharType* str, int id) {
        int off = root_offset_;
        for (; *str != '\0'; ++str) {
            const CharType& charactor = *str;
            if (nodes_[off].child.count(charactor) == 0) {
                int new_id = nodes_.size();
                nodes_[off].child[charactor] = new_id;
                nodes_.push_back(Node());
            }
            off = nodes_[off].child[charactor];
        }
        nodes_[off].id = id;
    }
    
    void build_automata() {
        std::queue<int> que;
        que.push(root_offset_);

        while (!que.empty()) {
            int father_offset = que.front();
            const Node& father = nodes_[father_offset];
            que.pop();

            for (ChildIterator it = father.child.begin(); it != father.child.end(); ++it) {
                const CharType& charactor = it->first;
                Node& child = nodes_[it->second];

                if (father_offset == root_offset_) {
                   child.fail_offset = root_offset_;
                } else {
                    int next_offset = father.fail_offset;
                    while (next_offset != None) {
                        const Node& next = nodes_[next_offset];
                        if (next.child.count(charactor) == 0) {
                            next_offset = next.fail_offset;
                            continue;
                        }

                        int next_child_offset = next.get_child(charactor);
                        const Node& next_child = nodes_[next_child_offset];
                        child.fail_offset = next_child_offset;
                        if (child.id == None) {
                            child.id = next_child.id;
                        }
                        break;
                    }

                    if (next_offset == None) {  // no common prefix
                        child.fail_offset = root_offset_;
                    }
                }

                que.push(it->second);
            }
        }
    }

    std::set<int> match(const CharType* str) const {
        std::set<int> result;
        for (int off = root_offset_; *str != '\0'; ++str) {
            const CharType& charactor = *str;
            while (off != root_offset_ && nodes_[off].child.count(charactor) == 0) {
                off = nodes_[off].fail_offset;
            }
            if (nodes_[off].child.count(charactor) == 0) {
                continue;
            }
            off = nodes_[off].get_child(charactor);
            for (int back_off = off; nodes_[back_off].id != None && back_off != root_offset_;
                    back_off = nodes_[back_off].fail_offset) {
                result.insert(nodes_[back_off].id);
            }
        }
        return result;
    }

private:
    static const int None = -1;
    typedef typename std::map<CharType, int> ChildMap;
    typedef typename ChildMap::const_iterator ChildIterator;

    struct Node {
        int id;
        int fail_offset;
        ChildMap child;

        Node() : id(None), fail_offset(None) { }

        int get_child(const CharType ch) const {
            ChildIterator it = child.find(ch);
            if (it != child.end()) {
                return it->second;
            } else {
                return None;
            }
        }
    };

    int word_count_;
    int root_offset_;
    std::vector<Node> nodes_;
};

void show_set(const std::set<int>& st) {
    using std::cout;
    using std::endl;

    for (std::set<int>::const_iterator it = st.begin(); it != st.end(); ++it) {
        cout << "[" << *it << "]";
    }
    cout << endl;
}

int main() {
    AhoCorasick<char> ac;
    ac.insert("she", 1);
    ac.insert("he", 2);
    ac.build_automata();
    show_set(ac.match("he is cool"));
    show_set(ac.match("she is cool"));

    ac.clear();
    ac.insert("she", 1);
    ac.insert("he", 2);
    ac.insert("say", 3);
    ac.insert("shr", 4);
    ac.insert("her", 5);
    ac.build_automata();
    show_set(ac.match("yasherhs"));

    return 0;
}

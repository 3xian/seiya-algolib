#include <vector>
#include <queue>
#include <map>
#include <set>
#include <iostream>

class Aho_Corasick
{
public:
    Aho_Corasick() {
        clear();
    }

    void clear() {
        _node.resize(1);
        _node[Root].id = None;
        _node[Root].fail_off = None;
        _node[Root].child.clear();
        _word_count = 0;
    }

    int word_count() const {
        return _word_count;
    }

    void insert(const char* str, int id) {
        int off = Root;
        for (; *str != '\0'; str++) {
            const char& charactor = *str;
            if (_node[off].child.count(charactor) == 0) {
                _node[off].child[charactor] = _node.size();
                _node.push_back(Node());
                _node.back().id = None;
            }
            off = _node[off].child[charactor];
        }
        _node[off].id = id;
    }
    
	void build_automata() {
        std::queue<int> que;
        que.push(Root);

		while (!que.empty()) {
            int father = que.front();
            que.pop();
            for (std::map<char, int>::const_iterator it = _node[father].child.begin();
                    it != _node[father].child.end(); ++it) {
                char charactor = it->first;
                int child = it->second;
                if (father == Root) {
                    _node[child].fail_off = Root;
                } else {
                    int next = _node[father].fail_off;
                    while (next != None) {
                        if (_node[next].child.count(charactor)) {
                            int next_child = _node[next].child[charactor]; 
                            _node[child].fail_off = next_child;
                            if (_node[child].id == None) {
                                _node[child].id = _node[next_child].id;
                            }
                            break;
                        } else {
                            next = _node[next].fail_off;
                        }
                    }
                    if (next == None) {
                        _node[child].fail_off = Root;
                    }
                }
                que.push(child);
            }
        }
	}

    std::set<int> get_match(const char* str) {
        std::set<int> ret;
        for (int off = Root; *str != '\0'; str++) {
            char charactor = *str;
            while (off != Root && _node[off].child.count(charactor) == 0) {
                off = _node[off].fail_off;
            }
            if (_node[off].child.count(charactor) == 0) {
                continue;
            }
            off = _node[off].child[charactor];
            for (int back_off = off; _node[back_off].id != None && back_off != Root;
                    back_off = _node[back_off].fail_off) {
                ret.insert(_node[back_off].id);
            }
        }
        return ret;
    }

private:
    static const int None = -1;
    static const int Root = 0;

    struct Node {
        int id;
        int fail_off;
        std::map<char, int> child;  // charactor -> offset
    };

    int _word_count;
    std::vector<Node> _node;
};

void show_set(const std::set<int>& st) {
    for (std::set<int>::const_iterator it = st.begin();
            it != st.end(); ++it) {
        std::cout << "[" << *it << "]";
    }
    std::cout << std::endl;
}

int main() {
    Aho_Corasick ac;
    ac.insert("she", 1);
    ac.insert("he", 2);
    ac.build_automata();
    show_set(ac.get_match("he is cool"));
    show_set(ac.get_match("she is cool"));

    ac.clear();
    ac.insert("she", 1);
    ac.insert("he", 2);
    ac.insert("say", 3);
    ac.insert("shr", 4);
    ac.insert("her", 5);
    ac.build_automata();
    show_set(ac.get_match("yasherhs"));

    return 0;
}

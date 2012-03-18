#include <iostream>
#include <cstdio>

template<typename T>
class BinaryTree {
public:
    struct Node {
        Node* _child[2];
        Node* _father;
        int   _direction;
        int   _size;
        T     _value;
        T     _max_value;
        Node(const T& value) : _size(1), _value(value), _max_value(value), _father(NULL) {
            _child[0] = NULL;
            _child[1] = NULL;
        }
        void update() {
            _size = 1;
            _max_value = _value;
            for (int i = 0; i < 2; i++) {
                if (_child[i] != NULL) {
                    _size += _child[i]->_size;
                    if (_max_value < _child[i]->_max_value) {
                        _max_value = _child[i]->_max_value;
                    }
                }
            }
        }
    };
    BinaryTree() {
        _root = NULL;
    }
    ~BinaryTree() {
        clear();
    }
    void clear() {
        destroy(_root);
        _root = NULL;
    }
    int size() const {
        return _root == NULL ? 0 : _root->_size;
    }
    Node* select(int k) const {
        if (k >= size()) {
            return NULL;
        }
        for (Node* p = _root; ; ) {
            int left_size = p->_child[0] == NULL ? 0 : p->_child[0]->_size;
            if (left_size == k) return p;
            if (k < left_size) {
                p = p->_child[0];
            } else {
                k -= left_size + 1;
                p = p->_child[1];
            }
        }
    }
    Node* get_segment(int begin, int end) {
        if (begin >= end or begin >= size()) {
            return NULL;
        }
        if (begin <= 0 && end >= size()) {
            return _root;
        }
        begin--;
        Node* x;
        Node* y;
        if (begin < 0) {
            x = NULL;
        } else {
            x = select(begin);
            bubble(x, NULL);
            if (end >= size()) {
                return x->_child[1];
            }
        }
        y = select(end);
        bubble(y, x);
        return y->_child[0];
    }
    void insert(int k, const T& value) {
        Node* p = select(k);
        Node* q = new Node(value);
        if (p == NULL) {
            link(q, _root, 0);
            _root = q;
        } else {
            link(q, p->_child[0], 0);
            link(p, q, 0);
        }
        bubble(q, NULL);
    }
    bool erase(int x) {
        Node* q = select(x);
        if (q == NULL) {
            return false;
        }
        while (q->_child[0] != NULL) {
            rotate(q->_child[0]);
        }
        link(q->_father, q->_child[1], q->_direction);
        if (_root == q) {
            _root = q->_child[1];
        } else {
            bubble(q->_father, NULL);
        }
        delete q;
        return true;
    }
    void display() {
        display(_root);
    }
    void display(const Node* p) const {
        if (p == NULL) return;
        display(p->_child[0]);
        std::cout << p->_value << ',';
        display(p->_child[1]);
    }
    void bubble(Node* x, Node* y) {
        while (x->_father != y) {
            if (x->_father->_father == y) {
                rotate(x);
            } else if (x->_direction == x->_father->_direction) {
                rotate(x->_father);
                rotate(x);
            } else {
                rotate(x);
                rotate(x);
            }
        }
        x->update();
    }
private:
    void destroy(Node* p) const {
        if (p == NULL) return;
        destroy(p->_child[0]);
        destroy(p->_child[1]);
        delete p;
    }
    void link(Node* a, Node* b, int direction) {
        if (a != NULL) {
            a->_child[direction] = b;
        }
        if (b != NULL) {
            b->_father = a;
            b->_direction = direction;
        }
    }
    void rotate(Node* x) {
        Node* father = x->_father;
        int direction = x->_direction;
        link(father, x->_child[direction ^ 1], direction);
        link(father->_father, x, father->_direction);
        link(x, father, direction ^ 1);
        father->update();
        if (x->_father == NULL) {
            _root = x;
        }
    }
    Node* _root;
};

int main() {
    using namespace std;
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        BinaryTree<int> tree;
        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            tree.insert(i, t);
        }
        for (int i = 0; i < m; i++) {
            char c;
            int x, y;
            scanf("\n%c%d%d", &c, &x, &y);
            if (c == 'U') {
                BinaryTree<int>::Node* p = tree.select(x - 1);
                tree.bubble(p, NULL);
                p->_value = y;
                p->update();
            } else {
                BinaryTree<int>::Node* s = tree.get_segment(x - 1, y);
                printf("%d\n", s->_max_value);
            }
        }
    }
    return 0;
}


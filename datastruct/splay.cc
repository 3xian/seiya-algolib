/**
 * 伸展树维护数组
 * erase没测试过
 * index from 0
 */

struct Splay
{
  struct Node
  {
    int   d;
    Node* c[2];
    Node* p;

    /* info */
    int   size;
    int   value;
    int   mmax;

    Node(int value)
      : size(1), value(value), mmax(value) {
      c[0] = NULL;
      c[1] = NULL;
      p = NULL;
    }

    void update() {
      size = 1;
      mmax = value;
      if (c[0] != NULL) {
        size += c[0]->size;
        mmax = std::max(mmax, c[0]->mmax);
      }
      if (c[1] != NULL) {
        size += c[1]->size;
        mmax = std::max(mmax, c[1]->mmax);
      }
    }
  };

  Node* root;

  Splay() {
    init();
  }

  void init() {
    root = NULL;
  }

  void link(Node* a, Node* b, int d) {
    if (a != NULL) {
      a->c[d] = b;
    }
    if (b != NULL) {
      b->p = a;
      b->d = d;
    }
  }

  void rotate(Node* x) {
    Node* p = x->p;
    int d = x->d;
    link(p, x->c[d ^ 1], d);
    link(p->p, x, p->d);
    link(x, p, d ^ 1);
    p->update();
    if (x->p == NULL) root = x;
  }

  void splay(Node* x, Node* y) {
    while (x->p != y) {
      if (x->p->p == y) rotate(x);
      else x->d == x->p->d ? (rotate(x->p), rotate(x)) : (rotate(x), rotate(x));
    }
    x->update();
  }

  Node* select(int k) const {
    for (Node* t = root; t != NULL; ) {
      int r = (t->c[0] == NULL) ? 0 : t->c[0]->size;
      if (r == k) return t;
      t = t->c[k > r];
      if (k > r) k -= r + 1;
    }
    return NULL;
  }

  Node* get_segment(int l, int r) { // (l, r)
    if (root == NULL) return NULL;
    if (l < 0 && r >= root->size) return root;
    Node* x;
    Node* y;
    if (l < 0) {
      x = NULL;
    } else {
      x = select(l);
      splay(x, NULL);
    }
    if (r >= root->size) {
      return x->c[1];
    } else {
      y = select(r);
      splay(y, x);
    }
    return y->c[0];
  }

  int max(int l, int r) { // get the maximum value in [l, r]
    return get_segment(l - 1, r + 1)->mmax;
  }

  void insert(int x, int k) { // insert before x
    Node* q = new Node(k);
    if (root == NULL) {
      root = q;
    } else if (x == root->size) {
      Node* p = root;
      while (p->c[1] != NULL) p = p->c[1];
      link(p, q, 1);
    } else {
      Node* p = select(x);
      link(q, p->c[0], 0);
      link(p, q, 0);
    }
    splay(q, NULL);
  }

  bool erase(int x) {
    Node* q = select(x);
    if (q == NULL) return false;
    while (q->c[0] != NULL) rotate(q->c[0]);
    link(q->p, q->c[1], q->d);
    if (root == q) root = q->c[1];
    if (q->c[1] != NULL) splay(q->c[1], NULL);
    else if (q->p != NULL) splay(q->p, NULL);
    delete q;
    return true;
  }

  void disp() const {
    _disp(root);
  }

  void _disp(const Node* p) const {
    if (p == NULL) return;
    _disp(p->c[0]);
    printf("%d ", inv[p->value]);
    _disp(p->c[1]);
  }
};

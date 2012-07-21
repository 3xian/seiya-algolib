template<typename T>
struct SBNode {
  int size;
  SBNode<T>* child[2];
  T key;
  SBNode() { }
  SBNode(SBNode<T>* l, SBNode<T>* r, int s, const T& k) : size(s), key(k) {
    child[0] = l;
    child[1] = r;
  }
};

template<typename T>
class SBTree {
 public:
  SBTree();
  ~SBTree();
  int size();
  void insert(const T& key);

 private:
  void maintain(SBNode<T>*& cur, int style) const;
  void rotate(SBNode<T>*& cur, int direct) const;
  void insert(SBNode<T>*& cur, const T& key);

  SBNode<T>* _root;
  SBNode<T>* _null;
};

template<typename T>
SBTree<T>::SBTree() {
  _null= new SBNode<T>();
  _root= _null; 
  _root->child[0] = _null;
  _root->child[1] = _null;
  _root->size= 0;
}

template<typename T>
SBTree<T>::~SBTree() { }

template<typename T>
inline int SBTree<T>::size() {
  return _root->size;
}

template<typename T>
void SBTree<T>::insert(const T& key) {
  insert(_root, key);
}

template<typename T>
inline void SBTree<T>::insert(SBNode<T>*& cur, const T& key){
  if (cur == _null) { cur = new SBNode<T>( _null, _null, 1, key); return; }
  ++cur->size;
  insert(cur->child[key >= cur->key], key);
  maintain(cur, key >= cur->key);
}

template<typename T>
inline void SBTree<T>::rotate(SBNode<T>*& cur, int dir) const {
  SBNode<T>* tmp= cur->child[dir^1];
  cur->child[dir^1]= tmp->child[dir];
  tmp->child[dir]= cur;
  tmp->size = cur->size;
  cur->size = cur->child[0]->size+ cur->child[1]->size+ 1;
  cur = tmp;
}

template<typename T>
inline void SBTree<T>::maintain(SBNode<T>*& cur, int style) const {
  if (cur == _null) return;
  if (cur->child[style]->child[style]->size> cur->child[style^1]->size)
    rotate(cur, style^1);
  else if (cur->child[style]->child[style^1]->size> cur->child[style^1]->size){
    rotate(cur->child[style], style);
    rotate(cur, style^1);
  } else return;
  maintain(cur->child[0], 0);
  maintain(cur->child[1], 1);
  maintain(cur, 0);
  maintain(cur, 1);
}
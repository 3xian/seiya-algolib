template<typename T>
struct SBNode {
  int size;
  T key;
  SBNode<T>* lchild;
  SBNode<T>* rchild;
  SBNode() { }
  SBNode(SBNode<T>* l, SBNode<T>* r, int s, const T& k)
      : lchild(l), rchild(r), size(s), key(k) { }
};

template<typename Type>
class SBTree {
 public:
  SBTree();
  ~SBTree();

  void insert( Type key );
  Type get_rank( int k  ); // [0,size)
  void clear();
  void travel();

 private:
  void left_rotate ( SBNode<Type>*& root );
  void right_rotate( SBNode<Type>*& root );
  void maintain( SBNode<Type>*& root, bool style );
  void insert( SBNode<Type>*& root, Type key );
  void clear ( SBNode<Type>* root );
  void travel( SBNode<Type>* root );

  SBNode<Type>* root;
  SBNode<Type>* _null;
};

template<typename Type>
Type SBTree<Type>::get_rank( int k ){
  SBNode<Type>* tmp= root;
  for( ;; ){
    if( tmp->lchild->size> k ) tmp= tmp->lchild;
    else if( k> tmp->lchild->size ){
      k-= tmp->lchild->size+ 1;
      tmp= tmp->rchild;
    } else break;
  }
  return tmp->key;
}

template<typename Type>
void SBTree<Type>::clear( SBNode<Type>* root ){
  if( root!= _null ){
    clear( root->lchild );
    clear( root->rchild );
    delete root; }
}

template<typename Type>
void SBTree<Type>::clear(){
  clear(root);
  delete _null;
}

template<typename Type>
void SBTree<Type>::travel( SBNode<Type>* root ){
  if ( root!= _null ){
    travel( root->lchild );
    cout << root->key << "  ";
    travel( root->rchild );
  }
}

template<typename Type>
void SBTree<Type>::travel(){
  travel( root );
}

template<typename Type>
void SBTree<Type>::insert( SBNode<Type>*& root, Type key ){
  if( root== _null ){
    root= new SBNode<Type>( _null, _null, 1, key ); return; }
  root->size++;
  if( key< root->key ) insert( root->lchild, key );
  else                 insert( root->rchild, key );
  maintain( root, key>= root->key );
}

template<typename Type>
void SBTree<Type>::insert( Type key ){
  insert( root, key );
}

template<typename Type>
SBTree<Type>::SBTree(){
  _null= new SBNode<Type>();
  root= _null; 
  root->lchild= root->rchild= _null;
  root->size= 0;
}

template<typename Type>
SBTree<Type>::~SBTree(){
  clear();
}

template<typename Type>
inline void SBTree<Type>::left_rotate( SBNode<Type>*& root ){
  SBNode<Type>* tmp= root->rchild;
  root->rchild= tmp->lchild;  tmp->lchild= root;
  tmp->size= root->size;
  root->size= root->lchild->size+ root->rchild->size+ 1;
  root= tmp;
}

template<typename Type>
inline void SBTree<Type>::right_rotate( SBNode<Type>*& root ){
  SBNode<Type>* tmp= root->lchild;
  root->lchild= tmp->rchild;  tmp->rchild= root;
  tmp->size= root->size;
  root->size= root->lchild->size+ root->rchild->size+ 1;
  root= tmp;
}

template<typename Type>
void SBTree<Type>::maintain( SBNode<Type>*& root, bool style ){
  if( root== _null ) return;
  if( !style ){
    if( root->lchild->lchild->size> root->rchild->size )
      right_rotate( root );
    else if( root->lchild->rchild->size> root->rchild->size ){
      left_rotate( root->lchild );
      right_rotate( root );
    }else return;
  } else {
    if( root->rchild->rchild->size> root->lchild->size )
      left_rotate( root );
    else if( root->rchild->lchild->size> root->lchild->size ){
      right_rotate( root->rchild );
      left_rotate( root ); 
    }else return;
  }
  maintain(root->lchild, false);  maintain(root->rchild, true);
  maintain(root, false);          maintain(root, true);
}

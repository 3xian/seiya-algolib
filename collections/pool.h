template <typename T>
class Pool {
 public:
  Pool();
  ~Pool();
  void clear();
  T& get();

 private:
  enum { BLOCK_SIZE = 1024 };
  int _last_offset;
  std::vector<T*> _head;
};

template <typename T>
Pool<T>::Pool() {
  clear();
}

template <typename T>
Pool<T>::~Pool() {
  clear();
}

template <typename T>
void Pool<T>::clear() {
  _last_offset = BLOCK_SIZE;
  for (size_t i = 0; i < _head.size(); i++) { delete [] _head[i]; }
  _head.clear();
}

template <typename T>
inline T& Pool<T>::get() {
  if (_last_offset == BLOCK_SIZE) {
    _last_offset = 0;
    _head.push_back(new T[BLOCK_SIZE]);
  }
  return *(_head.back() + _last_offset++);
}

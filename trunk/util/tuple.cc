template <typename T>
struct Tuple
{
  static const int N = 3;
  T a[N];

  T& operator [](int i) {
    return a[i];
  }

  bool operator <(const Tuple &rhs) const {
    for (int i = 0; i < N; ++i)
      if (a[i] != rhs[i])
        return a[i] < rhs[i];
    return false;
  }
};

template<typename T, int N>
class Tuple {
 public:
  T& operator [](int i) {
    return a[i];
  }

  bool operator <(const Tuple& rhs) const {
    return lexicographical_compare(a, a + N, rhs.a, rhs.a + N);
  }

 private:
  T a[N];
}

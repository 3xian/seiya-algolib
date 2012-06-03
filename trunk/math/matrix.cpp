template <typename T>
class Matrix {
 public:
  Matrix(int row, int col, const T* arr = NULL, const T& mod = T(0))
      : _row(row), _col(col), _mat(new T[row * col]), _mod(mod) {
    for (int i = 0; i < _row; i++) {
      for (int j = 0; j < _col; j++) {
        if (arr == NULL) {
          (*this)[i][j] = 0;
        } else {
          (*this)[i][j] = arr[i * col + j];
        }
      }
    }
  }

  Matrix(const Matrix<T>& other)
      : _row(0), _col(0), _mat(NULL) { *this = other; }

  void operator =(const Matrix<T>& other) {
    if (_mat == NULL || _row * _col != other.row() * other.col()) {
      if (_mat != NULL) delete [] _mat;
      _mat = new T[other.row() * other.col()];
    }

    _row = other.row();
    _col = other.col();
    _mod = other.mod();

    for (int i = 0; i < _row; i++) {
      for (int j = 0; j < _col; j++) {
        (*this)[i][j] = other[i][j];
      }
    }
  }

  ~Matrix() { delete [] _mat; }

  int row() const { return _row; }

  int col() const { return _col; }

  T mod() const { return _mod; }

  T* operator [](int row) const {
    return _mat + row * _col;
  }

  Matrix<T> operator *(const Matrix& other) const {
    assert(_col == other.row());

    Matrix<T> prod(_row, other.col(), NULL, _mod);

    for (int i = 0; i < _row; i++) {
      for (int j = 0; j < other.col(); j++) {
        for (int k = 0; k < _col; k++) {
          prod[i][j] += (*this)[i][k] * other[k][j];
          if (_mod != 0) { prod[i][j] %= _mod; }
        }
      }
    }
    return prod;
  }

  Matrix<T> pow(long long k) const {
    k--;
    Matrix<T> pd(*this);
    Matrix<T> pw(*this);
    while (k > 0) {
      if (k & 1) pd = pd * pw;
      if (k > 1) pw = pw * pw;
      k /= 2;
    }
    return pd;
  }

 private:
  int _row;
  int _col;
  T* _mat;
  T _mod;
};


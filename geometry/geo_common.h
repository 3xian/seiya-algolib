#include <cmath>
#include <limits>
#include <vector>

const double EPS = 1E-5;
const double INF = std::numeric_limits<double>::max();

inline int sign(double x) {
  return x < -EPS ? -1 : x > EPS;
}

template <typename T>
inline int next(const std::vector<T>& vec, size_t i) {
  if (i + 1 < vec.size()) { return i + 1; }
  return 0;
}

template <typename T>
inline int prev(const std::vector<T>& vec, size_t i) {
  if (i > 0) { return i - 1; }
  return vec.size() - 1;
}


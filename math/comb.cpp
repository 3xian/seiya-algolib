int c(int n, int m) {
  return m > 0 ? c(n - 1, m - 1) * n / m : 1;
}

#include <iostream>

int jc(int x) {
  int ret = 1;
  for (int i = 1; i <= x; i++) {
    ret *= i;
  }
  return ret;
}

int c(int n, int m) {
    return m ? c(n - 1, m - 1) * n / m : 1;
}

int foo(int n, int k) {
  if (k > n) {
    return 0;
  }
  if (k == 0) {
    return 1;
  }

  int a = jc(k);
  a *= c(n, k);
  a *= c(n, k);
  return a;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::cout << foo(n, k);
  return 0;
}

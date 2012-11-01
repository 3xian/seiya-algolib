#include <iostream>

int phi(int n) {
  int rez = 1;
  for (int i = 2; (long long)i * i <= n; i++) {
    if (n % i == 0) {
      n /= i;
      rez *= i - 1;
      while (n % i == 0) {
        n /= i;
        rez *= i;
      }
    }
  }
  if (n > 1) {
    rez *= n - 1;
  }
  return rez;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << phi(n);
  return 0;
}

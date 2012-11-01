#include <cstdio>
#include <algorithm>

int get_int() {
  int x;
  scanf("%d", &x);
  return x;
}

int main() {
  int n = get_int();
  int* a = new int[n + 1];
  for (int i = 1; i <= n; i++) { a[i] = 1; }

  for (int i = 1; i <= n; i++) {
    for (int j = i + i; j <= n; j += i) {
      a[j] = a[i] + 1;
    }
  }

  printf("%d\n", *std::max_element(a + 1, a + n + 1));
  for (int i = 1; i <= n; i++) {
    printf("%d ", a[i]);
  }

  delete [] a;
  return 0;
}

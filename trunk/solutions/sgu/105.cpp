#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);

  int m = n / 3 * 2;
  if (n % 3 == 2) m++;
  printf("%d", m);
  return 0;
}

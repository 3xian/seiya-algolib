#include <cstdio>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);

  char* str[m];
  for (int i = 0; i < m; i++) {
    str[i] = new char[101];
    scanf("%s", str[i]);
  }

  n %= m;
  if (n == 0) {
    n = m;
  }
  printf("%s", str[n - 1]);

  for (int i = 0; i < m; i++) {
    delete [] str[i];
  }

  return 0;
}

#include <cstdio>

int main() {
  int n;
  scanf("%d", &n);
  if (n < 9) {
    printf("0");
  } else if (n == 9) {
    printf("8");
  } else {
    printf("72");
    for (int i = 10; i < n; i++) {
      printf("0");
    }
  }
  return 0;
}

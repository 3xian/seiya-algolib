#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

bool need(int* a, int ai, int x, int n) {
  if (n == 0) {
    return true;
  }

  //printf("need n=%d ai=%d x=%d\n", n, ai, x);

  static bool mk[10001];
  memset(mk, 0, x + 1);
  mk[0] = true;
  for (int j = 0; j < n; j++) {
    for (int i = x - a[j]; i >= 0; i--) {
      if (!mk[i]) {
        continue;
      }
      int to = i + a[j];
      if (to <= x) { mk[to] = true; }
    }
    if (mk[x]) {
      return false;
    }
  }
  return true;
}

int main() {
  int n, x;
  scanf("%d%d", &n, &x);
  int* a = new int[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", a + i);
  }

  std::random_shuffle(a, a + n); 
  std::vector<int> ans;

  for (int i = 0; i < n; i++) {
    int cur = a[i];
    std::swap(a[i], a[n - 1]);
    if (need(a, cur, x, n - 1)) {
      ans.push_back(cur);
      x -= cur;
      n--;
      i--;
    } else {
      std::swap(a[i], a[n - 1]);
    }
  }

  printf("%u\n", ans.size());
  for (size_t i = 0; i < ans.size(); i++) {
    printf("%d ", ans[i]);
  }

  return 0;
}

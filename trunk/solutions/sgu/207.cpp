#include <cmath>
#include <iostream>
#include <vector>

double unfair(int x, int y, int k, int m) {
  return fabs((double)x / y - (double)k / m);
}

int main() {
  int n, m, y;
  std::cin >> n >> m >> y;
  std::vector<int> x(n);
  std::vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    std::cin >> x[i];
  }

  int remain = m;
  for (int i = 0; i < n; i++) {
    ans[i] = m * x[i] / y;
    remain -= ans[i];
  }

  //std::cout << remain;
  
  while (remain > 0) {
    int who = -1;
    double max_unfair = 0.0;
    for (int i = 0; i < n; i++) {
      if (ans[i] * y >= x[i] * m) {
        continue;
      }
      double cur_unfair = unfair(x[i], y, ans[i], m);
      if (who < 0 || cur_unfair > max_unfair) {
        who = i;
        max_unfair = cur_unfair;
      }
    }
    ans[who]++;
    remain--;
  }

  for (int i = 0; i < n; i++) {
    std::cout << ans[i] << ' ';
  }

  return 0;
}

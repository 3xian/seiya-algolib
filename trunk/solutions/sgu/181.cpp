#include <iostream>
#include <map>

using namespace std;

int main() {
  long long a;
  int alpha;
  int beta;
  int gamma;
  int m;
  int k;

  cin >> a >> alpha >> beta >> gamma >> m >> k;

  if (k > 0) {
    map<int, int> val;
    map<int, int> pos;

    int i = 1;
    for (/*int i = 1*/; i <= k; i++) {
      a = (a * a * alpha + a * beta + gamma) % m;
      if (pos.count(a)) {
        break;
      }
      pos[a] = i;
      val[i] = a;
    }

    if (i < k) {
      int seg = k - i;
      int mod = seg % (i - pos[a]);
      a = val[pos[a] + mod];
    }
  }

  cout << a;

  return 0;
}

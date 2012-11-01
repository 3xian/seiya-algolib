#include <cstdio>
#include <algorithm>
#include <vector>

class ThreeNum {
 public:
  ThreeNum() { }

  ThreeNum(FILE* fin) {
    for (int i = 0; i < 3; i++) {
      int x;
      fscanf(fin, "%d", &x);
      push_back(x);
    }
  }

  void push_back(int x) {
    _num.push_back(x);
  }

  int median() {
    std::sort(_num.begin(), _num.end());
    return _num[1];
  }

 private:
  std::vector<int> _num;
};

int main() {
  ThreeNum d;
  d.push_back(ThreeNum(stdin).median());
  d.push_back(ThreeNum(stdin).median());
  d.push_back(ThreeNum(stdin).median());
  printf("%d", d.median());

  return 0;
}

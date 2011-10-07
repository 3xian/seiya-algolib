#include <cstring>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#ifdef ONLINE_JUDGE
#define debug(x)
#else
#define debug(x) cout<<"  ... "#x" : "<<(x)<<"\n"
#endif
#define SQ(x) ((x)*(x))
#define PV(i,n) ((i)>0?(i)-1:(n)-1)
#define NX(i,n) ((i)+1<(n)?(i)+1:0)
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template<typename T> void mil(T& a, const T& b) {
  if (a > b) a = b;
}
template<typename T> void mal(T& a, const T& b) {
  if (a < b) a = b;
}
template<typename T> void usort(vector<T>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}
template<typename A, typename B> B conv(const A& i) {
  stringstream s;
  B o;
  s << i, s >> o;
  return o;
}

int main() {
  return 0;
}


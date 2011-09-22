#include <cstring>
#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>
#define PREV(i, n) ((i)>0?(i)-1:(n)-1)
#define NEXT(i, n) ((i)+1<(n)?(i)+1:0)
#ifdef  LOCAL
#define debug(x) cout<<"  ... "#x" : "<<(x)<<"\n"
#else
#define debug(x) 
#endif
using namespace std;
typedef int64_t ll;
typedef pair<int, int> pii;
template <typename T> T sqr(const T& x) { return x * x; }
template <typename T> void mil(T& a, const T& b) { if (a > b) a = b; }
template <typename T> void mal(T& a, const T& b) { if (a < b) a = b; }
template <typename T> void usort(vector<T>& a) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
template <typename A, typename B> B conv(const A& i) { stringstream s; s << i; B o; s >> o; return o; }

int main() {
  return 0;
}

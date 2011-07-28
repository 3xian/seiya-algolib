#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <deque>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

#define umap    tr1::unordered_map
#define uset    tr1::unordered_set
#define pv(i,n) ((i)>0?(i)-1:(n)-1)
#define nx(i,n) ((i)+1<(n)?(i)+1:0)
#ifdef LOCAL
#define LOG(x)   cout<<">> "#x" = "<<(x)<<"\n"
#else
#define LOG(x) 
#endif

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template <typename T> T sqr(const T& x) { return x * x; }
template <typename T> void mil(T& a, const T& b) { if (a > b) a = b; }
template <typename T> void mal(T& a, const T& b) { if (a < b) a = b; }
template <typename T> void usort(vector<T>& a) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
template <typename A, typename B> B conv(const A& i) { stringstream s; s << i; B o; s >> o; return o; }

int main() {
    return 0;
}

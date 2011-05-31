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
#include <string>
#include <vector>
#include <tr1/unordered_map>
#include <tr1/unordered_set>

#define umap    tr1::unordered_map
#define uset    tr1::unordered_set
#define pv(i,n) ((i)>0?(i)-1:(n)-1)
#define nx(i,n) ((i)+1<(n)?(i)+1:0)
#define TT      template<typename T>
#define TAB     template<typename A,typename B>
#define ss(x)   cout<<"DEBUG : "#x" = "<<(x)<<"\n"

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
TT T sqr(const T &x) { return x * x; }
TT T abs(const T &x) { return x < 0 ? -x : x; }
TT void mil(T &a, const T &b) { if (a > b) a = b;}
TT void mal(T &a, const T &b) { if (a < b) a = b;}
TT T gcd(T a, T b) { while (b) { T t = a % b; a = b; b = t; } return a; }
TAB B conv(const A &i) { stringstream s; s << i; B o; s >> o; return o; }
TAB istream& operator >>(istream &i, pair<A, B> &p) { return i >> p.first >> p.second; }
TT void usort(vector<T> &a) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
TT pair<T, T> operator +(const pair<T, T> &a, const pair<T, T> &b) { return pair<T, T>(a.first + b.first, a.second + b.second); }
TT pair<T, T> operator -(const pair<T, T> &a, const pair<T, T> &b) { return pair<T, T>(a.first - b.first, a.second - b.second); }

void york() {
}

int main() {
#ifdef ONLINE_JUDGE
    ios_base::sync_with_stdio(false);
#else
    freopen("1.txt", "r", stdin);
#endif
    york();
    return 0;
}

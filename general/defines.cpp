#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
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
#include <ext/hash_map>

#define say(x)		cout<<"["#x"="<<x<<"]\n"
#define sz(x)		((int)(x).size())
#define itr(x)		typeof((x).begin())
#define each(i,x)	for(itr(x) i=(x).begin();i!=(x).end();++i)
#define pv(i,n)		((i)>0?(i)-1:(n)-1)
#define nx(i,n)		((i)+1<(n)?(i)+1:0)

using namespace std;
using namespace __gnu_cxx;

typedef long long Int64;
typedef pair<int, int> IntInt;

template<typename T> T sq(const T& x) {
	return x * x;
}
template<typename T> void minl(T& a, const T& b) {
	if (a > b)
		a = b;
}
template<typename T> void maxl(T& a, const T& b) {
	if (a < b)
		a = b;
}
template<typename T> void operator +=(vector<T>& a, const T& x) {
	a.push_back(x);
}
template<typename T> void operator +=(set<T>& a, const T& x) {
	a.insert(x);
}
template<typename T> bool operator &(const set<T>& a, const T& x) {
	return a.find(x) != a.end();
}
template<typename A, typename B> istream& operator >>(istream& i, pair<A, B>& v) {
	return i >> v.first >> v.second;
}
IntInt operator +(const IntInt& a, const IntInt& b) {
	return IntInt(a.first + b.first, a.second + b.second);
}
IntInt operator -(const IntInt& a, const IntInt& b) {
	return IntInt(a.first - b.first, a.second - b.second);
}
template<typename T> void usort(vector<T>& a) {
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
}
template<typename T> int index(const vector<T>& a, const T& x) {
	return lower_bound(a.begin(), a.end(), x) - a.begin();
}
template<typename T> T gcd(T a, T b) {
	while (b) {
		T t = a % b;
		a = b;
		b = t;
	}
	return a;
}
Int64 cross(const IntInt& a, const IntInt& b) {
	return (Int64) a.first * b.second - (Int64) b.first * a.second;
}
Int64 dot(const IntInt& a, const IntInt& b) {
	return (Int64) a.first * b.first + (Int64) a.second * b.second;
}
int bitcnt(unsigned x) {
	return __builtin_popcount(x);
}
int bitlow(unsigned x) {
	return __builtin_ffs(x);
}

void york() {
}

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("1.in", "r", stdin);
	int ck = clock();
#endif
	york();
#ifndef ONLINE_JUDGE
	cout << "\n=====\nUsed: " << clock() - ck << " ms\n";
#endif
	return 0;
}

#include <cctype>
#include <climits>
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

#define say(x)		cout<<"["#x"="<<x<<"]\n"
#define itr(x)		typeof((x).begin())
#define pv(i,n)		((i)>0?(i)-1:(n)-1)
#define nx(i,n)		((i)+1<(n)?(i)+1:0)

using namespace std;

int count_bit(unsigned x) { return __builtin_popcount(x); }
int first_bit(unsigned x) { return __builtin_ffs(x); }
template<typename T> T sq(const T& x) { return x * x; }
template<typename T> void minl(T& a, const T& b) { if (a > b) a = b; }
template<typename T> void maxl(T& a, const T& b) { if (a < b) a = b; }
template<typename T> void usort(vector<T>& a) {
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
}
template<typename T> int index(const vector<T>& a, const T& x) {
	return lower_bound(a.begin(), a.end(), x) - a.begin();
}
template<typename T> T gcd(T a, T b) {
	while (b) { T t = a % b; a = b; b = t; }
	return a;
}
template<typename T> pair<T, T> operator + (const pair<T, T>& a, const pair<T, T>& b) {
	return pair<T, T>(a.first + b.first, a.second + b.second);
}
template<typename T> pair<T, T> operator - (const pair<T, T>& a, const pair<T, T>& b) {
	return pair<T, T>(a.first - b.first, a.second - b.second);
}
template<typename A, typename B> istream& operator >> (istream& i, pair<A, B>& v) {
	return i >> v.first >> v.second;
}
template<typename A, typename B> B conv(const A& in) {
	stringstream s; B out; s << in; s >> out;
	return out;
}
long long cross(const pair<int, int>& a, const pair<int, int>& b) {
	return (long long)a.first * b.second - (long long)b.first * a.second;
}
long long dot(const pair<int, int>& a, const pair<int, int>& b) {
	return (long long)a.first * b.first + (long long)a.second * b.second;
}

void york() {
}

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("1.txt", "r", stdin);
	int ck = clock();
#endif 
	york();
#ifndef ONLINE_JUDGE
	cout << "\n=====\nUsed: " << clock() - ck << " ms\n";
#endif
	return 0;
}

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
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define all(x)		(x).begin(),(x).end()
#define each(i,x)	for(typeof((x).begin()) i=(x).begin();i!=(x).end();++i)
#define loop(i,n)	for(int i=0;i<(n);++i)
#define mp(a,b)		make_pair((a),(b))
#define say(x)		cout<<"["#x"="<<x<<"]\n"
#define sz(x)		((int)(x).size())

using namespace std;

namespace york {
	typedef long long llong;
	typedef pair<int, int> ii_t;
	typedef pair<int, double> id_t;
	typedef pair<int, string> is_t;
	typedef pair<double, double> dd_t;
	template<typename T> T sq(const T& x) { return x * x; }
	template<typename T> void minl(T& a, const T& b) { if (a > b) a = b; }
	template<typename T> void maxl(T& a, const T& b) { if (a < b) a = b; }
	template<typename T> void operator += (vector<T>& a, const T& x) { a.push_back(x); }
	template<typename T> void operator += (set<T>& a, const T& x) { a.insert(x); }
	template<typename T> bool operator & (const set<T>& a,const T& x) { return a.find(x) != a.end(); }
	template<typename A, typename B> istream& operator >> (istream& i, pair<A, B>& v) { return i >> v.first >> v.second; }
	ii_t operator + (const ii_t& a,const ii_t& b) { return ii_t(a.first + b.first, a.second + b.second); }
	ii_t operator - (const ii_t& a,const ii_t& b) { return ii_t(a.first - b.first, a.second - b.second); }
	template<typename T> void usort(vector<T>& a) { sort(all(a)); a.erase(unique(all(a)), a.end()); }
	template<typename T> int index(const vector<T>& a, const T& x){ return lower_bound(all(a), x) - a.begin(); }
	template<typename T> T gcd(T a, T b) { while (b) { T t = a % b; a = b; b = t; } return a; }
	llong cross(const ii_t& a, const ii_t& b) { return (llong)a.first * b.second - (llong)b.first * a.second; }
	llong dot(const ii_t& a, const ii_t& b) { return (llong)a.first * b.first + (llong)a.second * b.second; }
#ifdef __GNUC__
	int bitcnt(unsigned x) { return __builtin_popcount(x); }
	int bitlow(unsigned x) { return __builtin_ffs(x); }
#endif

	void run() {
	}
}

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	if (freopen("1.in", "r", stdin) == NULL) {
		cout << "No input file!\n";
		return 0;
	}
	int ck = clock();
#endif
	york::run();
#ifndef ONLINE_JUDGE
	cout << "\n=====\nUsed: " << clock() - ck << " ms\n";
#endif
	return 0;
}

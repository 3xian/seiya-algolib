#include <cassert>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;
typedef long long ll; 
#define x first
#define y second
#define A(x) (x).begin(),(x).end()
#define LOG(x) cout<<#x"="<<x<<"\n"
#define LOG2(x,y) cout<<"("#x"="<<x<<", "#y"="<<y<<")\n"
string str(int i) { char s[16]; sprintf(s,"%d",i); return s; }
template<class T> void uniq(T& v) { sort(A(v)); v.erase(unique(A(v)),v.end()); }

int main() {
    ios::sync_with_stdio(false);
    return 0;
}
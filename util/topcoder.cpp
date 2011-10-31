$BEGINCUT$
$PROBLEMDESC$
$ENDCUT$
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
#define debug(x) cout<<"  ... "#x" : "<<(x)<<"\n"
#define sqr(a) ((a)*(a))
#define uniq(a) sort((a).begin(),(a).end());(a).erase(unique((a).begin(),(a).end()),(a).end())
#define conv(a,b) {stringstream t;t<<a;t>>b;}
#define prev(i,n) ((i)>0?(i)-1:(n-1))
#define next(i,n) ((i)+1<(n)?(i)+1:0)
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
template<typename T> void mil(T& a, const T& b) {if(a>b)a=b;}
template<typename T> void mal(T& a, const T& b) {if(a<b)a=b;}

class $CLASSNAME$
{
public:
  $RC$ $METHODNAME$($METHODPARMS$)
  {
  }
$TESTCODE$};
$BEGINCUT$
int main()
{
  $CLASSNAME$ ___test;
  ___test.run_test(-1);
  return 0;
}
$ENDCUT$
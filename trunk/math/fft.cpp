#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>

#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)

using namespace std;
typedef long long int64;
typedef unsigned int uint;

#define maxn 310010
#define nmaxn 141073

struct comp {
  long double a,b;
  comp(long double a_=0.0,long double b_=0.0):a(a_),b(b_){}
} null;

comp operator +(const comp &a,const comp &b){return comp(a.a+b.a,a.b+b.b);}
comp operator -(const comp &a,const comp &b){return comp(a.a-b.a,a.b-b.b);}
comp operator *(const comp &a,const comp &b){return comp(a.a*b.a-a.b*b.b,a.a*b.b+a.b*b.a);}

char s[maxn];
int n;
comp A[nmaxn],B[nmaxn],C[nmaxn];
const long double pi=acos(-1);
int base[10],M=100000,L=5;

int get(comp *A){
  scanf("%s",s);
  int a=0,p=0,l=0;
  for(int i=strlen(s)-1;i>=0;i--){
    a+=(s[i]-'0')*base[p++];
    if(p==L)    A[l++]=comp(a,0),a=p=0;
  }
  if(a)   A[l++]=comp(a,0);
  return l;
}

void init(){
  base[0]=1;
  REP1(i,L)   base[i]=base[i-1]*10;
  int l=get(A)+get(B);
  for(n=1;n<l;n<<=1);
}

comp p[2][nmaxn];int typ;
inline uint rev(uint a){
  a=((a&0x55555555U)<<1)|((a&0xAAAAAAAAU)>>1);
  a=((a&0x33333333U)<<2)|((a&0xCCCCCCCCU)>>2);
  a=((a&0x0F0F0F0FU)<<4)|((a&0xF0F0F0F0U)>>4);
  a=((a&0x00FF00FFU)<<8)|((a&0xFF00FF00U)>>8);
  a=((a&0x0000FFFFU)<<16)|((a&0xFFFF0000U)>>16);
  return a;
}

void FFT(comp *s,comp *bac,int n){
  int d=log2(n);
  REP(i,n)    s[rev(i)>>(32-d)]=bac[i];
  for(int i=1;i<=d;i++){
    int step=1<<i,v=step>>1,rstep=n/step;
    for(int j=0;j<=n-1;j+=step){
      comp *t=p[typ];
      for(int k=0;k<v;k++,t+=rstep){
        comp d=(*t)*s[k+j+v];
        s[k+j+v]=s[k+j]-d;
        s[k+j]=s[k+j]+d;
      }
    }
  }
}

int64 ans[4*maxn];

void work(){
  init();
  p[0][0]=comp(1,0),p[1][0]=comp(1,0);
  for(int i=1;i<n;i++){
    p[0][i]=comp(cos(2*i*pi/n),sin(2*i*pi/n));
    p[1][i]=comp(cos(2*i*pi/n),-sin(2*i*pi/n));
  }
  typ=0;
  FFT(C,A,n);
  FFT(A,B,n);
  REP(i,n)    A[i]=A[i]*C[i];
  typ=1;
  FFT(C,A,n);
  REP(i,n) ans[i]=C[i].a/n+0.1,A[i]=null,B[i]=null;
  REP(i,n) if(ans[i]>=M)    ans[i+1]+=ans[i]/M,ans[i]%=M;
  while (n>1&&ans[n-1]<=0)   n--;
  printf("%lld",ans[n-1]);
  for(int i=n-2;i>=0;i--)  printf("%05d",(int)ans[i]);
  printf("\n");
}

int main() {
  int casen;
  scanf("%d",&casen);
  while (casen--)  work();
  return 0;
}


#include<bits/stdc++.h>
#define N 2200000
using namespace std;
long long f[N],g[N];
vector<long long> a[N];
int len[N];
int n,m,k;
int b[N];
vector<pair<long long,long long> > h[1010];
namespace IO
{   const int __S=(1<<20)+5;char __buf[__S],*__H,*__T;
    inline char getc()
    {   if(__H==__T) __T=(__H=__buf)+fread(__buf,1,__S,stdin);
        if(__H==__T) return -1;return *__H++;
    }
    template <class __I>inline void read(__I &__x)
    {   char __c=getc(); while(!isdigit(__c)) __c=getc();
        for(__x=0;isdigit(__c);__c=getc()) __x=__x*10+(__c^'0');
    }
    inline void reads(char *__s,int __x=0)
    {   char __c=getc();int __tot=__x-1;
        while(__c<'!'||__c>'~') __c=getc();
        while(__c>='!'&&__c<='~') __s[++__tot]=__c,__c=getc();
        __s[++__tot]='\0';
    }
    char __obuf[__S],*__oS=__obuf,*__oT=__oS+__S-1,__c,__qu[55];int __qr;
    inline void flush(){fwrite(__obuf,1,__oS-__obuf,stdout);__oS=__obuf;}
    inline void putc(char __x){*__oS++ =__x;if(__oS==__oT) flush();}
    template <class __I>inline void print(__I __x)
    {   if(!__x) putc('0');
        while(__x) __qu[++__qr]=__x%10^'0',__x/=10;
        while(__qr) putc(__qu[__qr--]);
    }
    inline void prints(const char *__s,int __x=0)
    {   int __len=strlen(__s+__x);
        for(int __i=__x;__i<__len+__x;__i++) putc(__s[__i]);
    }
    inline void el(){putc('\n');}inline void sp(){putc(' ');}
}using namespace IO;
void solve(int y,int l,int r,int L,int R){
    if(l>r)return;
    int mid=(l+r)>>1;
    f[mid]=10000000000000000LL;
    int MID=mid;
    for(int i=L;i<=R;i++)
        if(i<mid&&mid-i<=len[y])
            if(g[i]+a[y][mid-i]<f[mid]){
                f[mid]=g[i]+a[y][mid-i];
                MID=i;
            }
    solve(y,l,mid-1,L,MID);
    solve(y,mid+1,r,MID,R);
}
int main(){
	freopen("a.in","r",stdin);
	freopen("std.out","w",stdout);
    read(n);
    read(k);
    for(int i=0;i<=k;i++)f[i]=1000000000LL*i;
    for(int i=1;i<=n;i++){
        read(len[i]);
        a[i].resize(len[i]+1);
        for(int j=0;j<=len[i];j++)read(a[i][j]);
        len[i]=min(len[i],k);
        for(int j=1;j<=len[i];j++)a[i][j]+=a[i][j-1];
        for(int j=1;j<=len[i];j++)h[j].push_back(pair<long long,long long>(a[i][j],i));
        a[i][0]=0;
    }
    for(int i=1;i<=k;i++){
        int tot=min(k/i+1,(int)h[i].size());
        nth_element(h[i].begin(),h[i].begin()+tot-1,h[i].end());
        for(int j=0;j<tot;j++)b[h[i][j].second]=1;
    }
    for(int i=1;i<=n;i++)
        if(b[i]){
            for(int j=0;j<=k;j++)g[j]=f[j];
            solve(i,1,k,0,k);
            for(int j=0;j<=k;j++)f[j]=min(f[j],g[j]);
        }
    for(int i=1;i<=k;i++)printf("%lld ",f[i]);
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 1000000007
#define inv2 500000004
using namespace std;
int n,k,l,r,len=1<<17;
int s[1<<17];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void fwt(int *s,int c)
{
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t1=s[i+j],t2=s[i+j+d];
				s[i+j]=(t1+t2)%mod;
				s[i+j+d]=(t1-t2+mod)%mod;
				if(c)
				{
					s[i+j]=(li)s[i+j]*inv2%mod;
					s[i+j+d]=(li)s[i+j+d]*inv2%mod;
				}
			}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d%d%d",&n,&k,&l,&r);
		memset(s,0,sizeof(s));
		for(int i=l;i<=r;i++)
			s[i]=1;
		fwt(s,0);
		for(int i=0;i<len;i++)
			s[i]=qpow(s[i],n);
		fwt(s,1);
		printf("%d\n",s[k]);
	}
	return 0;
}
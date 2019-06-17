#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 1000000007
using namespace std;
int n,q,d,ans,tp;
int l[20],r[20],xx[50];
int cru[50],st[50],cl[50];
int sm[50],pf[50],ed[50];
int f[50];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
const int inv10=qpow(10,mod-2),inv9=qpow(9,mod-2),inv8=qpow(8,mod-2);
void init()
{
	for(int i=1;i<=q;i++)
		xx[i]=l[i],xx[i+q]=r[i];
	sort(xx+1,xx+2*q+1);
	d=unique(xx+1,xx+2*q+1)-xx-1;
	for(int i=1;i<=q;i++)
	{
		l[i]=lower_bound(xx+1,xx+d+1,l[i])-xx;
		r[i]=lower_bound(xx+1,xx+d+1,r[i])-xx;
	}
}
int getf(int x)
{
	return ((li)qpow(inv10,x)*8%mod*inv9%mod+inv9)%mod;
}
void getans()
{
	for(int i=1;i<=d-1;i++)
	{
		if(!cru[i])
			cl[i]=(9-(pf[i-1]-pf[ed[i]-1]))%9;
		pf[i]=(pf[i-1]+cl[i])%9;
	}
	for(int i=1;i<=q;i++)
		if((pf[r[i]-1]-pf[l[i]-1]+9)%9!=0)
			return;
	int tmp=1;
	for(int i=1;i<=d-1;i++)
		if(sm[i]>0)
		{
			int t=f[i];
			if(cl[i]>=1)
				tmp=(li)tmp*(mod+1-t)%mod*inv8%mod;
			else
				tmp=(li)tmp*t%mod;
		}
	ans=(ans+tmp)%mod;

}
void dfs(int d)
{
	if(d>tp)
		return getans(),void();
	for(int i=0;i<=8;i++)
	{
		cl[st[d]]=i;
		dfs(d+1);
	}
}
void solve()
{
	for(int i=1;i<=q;i++)
		sm[l[i]]++,sm[r[i]]--;
	for(int i=1;i<=d;i++)
		sm[i]+=sm[i-1];
	for(int i=1;i<=q;i++)
		cru[l[i]]=1;
	for(int i=1;i<=q;i++)
	{
		cru[r[i]-1]=0;
		ed[r[i]-1]=l[i];
	}
	for(int i=1;i<=d-1;i++)
		if(cru[i])
			st[++tp]=i;
	for(int i=1;i<=d-1;i++)
		f[i]=getf(xx[i+1]-xx[i]);
	// printf("tp:%d\n",tp);
	dfs(1);
	int tmp=qpow(10,n);
	printf("%lld",(li)ans*tmp%mod);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",l+i,r+i),r[i]++;
	init();
	solve();
	return 0;
}
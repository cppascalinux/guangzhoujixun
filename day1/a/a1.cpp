//2019.06.17
//xsy1603 Problem A: Multiple of Nine 将区间离散化,前缀和,枚举区间端点mod9的值,子集dp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 1000000007
using namespace std;
int n,q,d,tp;
int l[20],r[20],xx[40];
int g[33009],f[10][33009];
int fn[40],mp[40];
vector<int> v[40];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
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
	for(int i=1;i<=d;i++)
		fn[i]=i;
	for(int i=1;i<=q;i++)
		fn[fnd(l[i])]=fnd(r[i]);
	for(int i=1;i<=d;i++)
	{
		int fi=fnd(i);
		if(!mp[fi])
			mp[fi]=++tp;
		v[mp[fi]].push_back(i);
	}
}
void getg()
{
	int tmp[40];
	for(int s=0;s<1<<tp;s++)
	{
		int sm=0;
		g[s]=1;
		for(int i=1;i<=tp;i++)
			if(s>>(i-1)&1)
				for(int j=0;j<(int)v[i].size();j++)
					tmp[++sm]=v[i][j];
		sort(tmp+1,tmp+sm+1);
		for(int i=2;i<=sm;i++)
			if(tmp[i]==tmp[i-1]+1)
			{
				int v10=qpow(10,xx[tmp[i]]-xx[tmp[i-1]]);
				g[s]=(li)g[s]*qpow(v10-1+mod,mod-2)%mod*(v10+8)%mod;
			}
	}
}
void solve()
{
	f[0][0]=1;
	for(int i=1;i<=9;i++)
	{
		for(int s=0;s<1<<tp;s++)
		{
			if(i==1&&!(s&1))
				continue;
			for(int t=s;t;t=(t-1)&s)
				f[i][s]=(f[i][s]+(li)f[i-1][s^t]*g[t])%mod;
			f[i][s]=(f[i][s]+(li)f[i-1][s]*g[0])%mod;
		}
	}
	int ans=1,inv9=qpow(9,mod-2);
	for(int i=2;i<=d;i++)
	{
		int v10=qpow(10,xx[i]-xx[i-1]);
		ans=(li)ans*(v10+mod-1)%mod*inv9%mod;
	}
	ans=(li)ans*qpow(10,(n+1-xx[d])+(xx[1]-1))%mod;
	// printf("tp:%d g0:%d g1:%d\n",tp,g[0],g[1]);
	// printf("ans:%d f:%d\n",ans,f[9][(1<<tp)-1]);
	printf("%lld",(li)ans*f[9][(1<<tp)-1]%mod);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	for(int i=1;i<=q;i++)
		scanf("%d%d",l+i,r+i),r[i]++;
	init();
	getg();
	solve();
	return 0;
}
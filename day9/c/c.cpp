#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define li long long
#define mod 998244353
using namespace std;
int n;
int sa[60009],sc[60009];
int qpow(int a,int b)
{
	a%=mod;
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
namespace part1
{
	int mat[3009][3009];
	void gauss()
	{
		for(int i=1;i<=n;i++)
		{
			int t=i;
			for(int j=i+1;j<=n;j++)
				if(mat[j][i])
					t=j;
			for(int k=i;k<=n+1;k++)
				swap(mat[i][k],mat[t][k]);
			int inv=qpow(mat[i][i],mod-2);
			for(int k=i;k<=n+1;k++)
				mat[i][k]=(li)mat[i][k]*inv%mod;
			for(int j=i+1;j<=n;j++)
				for(int k=n+1;k>=i;k--)
					mat[j][k]=(mat[j][k]+mod-(li)mat[j][i]*mat[i][k]%mod)%mod;
		}
		for(int i=n;i>=1;i--)
			for(int j=i+1;j<=n;j++)
				mat[i][n+1]=(mat[i][n+1]+mod-(li)mat[i][j]*mat[j][n+1]%mod)%mod;
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
			mat[i][n+1]=sc[i-1];
		for(int i=1;i<=n;i++)
			mat[1][i]=1;
		for(int i=2;i<=n;i++)
			for(int j=1;j<=n;j++)
				mat[i][j]=(li)mat[i-1][j]*sa[j-1]%mod;
		gauss();
		for(int i=1;i<=n;i++)
			printf("%d ",mat[i][n+1]);
	}
}
namespace part2
{
	void solve()
	{
		// for(int i=1;i<n;i++)
		// 	assert(sc[i]==(li)sc[i-1]*sc[1]%mod);
		int vc=sc[1],det0=1,idet0;
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				det0=(li)det0*(sa[j]-sa[i]+mod)%mod;
		idet0=qpow(det0,mod-2);
		for(int i=0;i<n;i++)
		{
			int det1=det0;
			for(int j=0;j<i;j++)
				det1=(li)det1*qpow(sa[i]-sa[j]+mod,mod-2)%mod*(vc-sa[j]+mod)%mod;
			for(int j=i+1;j<n;j++)
				det1=(li)det1*qpow(sa[j]-sa[i]+mod,mod-2)%mod*(sa[j]-vc+mod)%mod;
			printf("%lld ",(li)det1*idet0%mod);
		}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",sa+i);
	for(int i=0;i<n;i++)
		scanf("%d",sc+i);
	if(n<=300)
		part1::solve();
	else
		part2::solve();
	return 0;
}
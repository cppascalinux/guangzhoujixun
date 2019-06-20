//xsy1605 Problem B: 苹果 枚举不合法位置的个数容斥,f[i][0/1]表示前i个中有奇数/偶数个不合法的方案数,转移时枚举不合法连续段的长度
//因为不合法的a>=2*b,所以不合法连续段长度<=logm,而每一个不合法连续段的答案可以通过O(nlog^2m)的dp预处理得到,总时间复杂度O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 998244353
using namespace std;
int n,m;
int g[29][100009];
int f[100009][2];
void init()
{
	for(int i=1;i<=m;i++)
		g[1][i]=1;
	for(int i=2;i<=20;i++)
	{
		for(int j=1;j<=m;j++)
			for(int k=2*j;k<=m;k+=j)
				g[i][j]=(g[i][j]+g[i-1][k])%mod;
	}
	for(int i=1;i<=20;i++)
		for(int j=1;j<=m;j++)
			g[i][0]=(g[i][0]+g[i][j])%mod;
}
void solve()
{
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=min(i,20);j++)
			for(int k=0;k<=1;k++)
				f[i][k]=(f[i][k]+(li)f[i-j][k^((j-1)&1)]*g[j][0])%mod;
	}
	printf("%d",(f[n][0]-f[n][1]+mod)%mod);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	init();
	solve();
	return 0;
}
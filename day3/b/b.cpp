#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#define mod 998244353
using namespace std;
int n,m;
int f[2][100009];
int st[100009];
void dp()
{
	for(int i=1;i<=m;i++)
		f[1][i]=1;
	for(int i=2;i<=n;i++)
	{
		int sm=0,cur=i&1;
		for(int j=1;j<=m;j++)
			sm=(sm+f[cur^1][j])%mod;
		for(int j=1;j<=m;j++)
		{
			f[cur][j]=sm;
			for(int k=2*j;k<=m;k+=j)
				f[cur][j]=(f[cur][j]-f[cur^1][k]+mod)%mod;
		}
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=m;j++)
	// 		printf("%d ",f[i][j]);
	// 	printf("\n");
	// }
	int ans=0;
	for(int i=1;i<=m;i++)
		ans=(ans+f[n&1][i])%mod;
	map<int,int> mp;
	int sm=0,tp=0;
	for(int i=1;i<=m;i++)
		if(!mp[f[n&1][i]])
			sm++,mp[f[n&1][i]]=1,st[++tp]=i;
	int sm2=0;
	for(int i=1;i<=m;i++)
	{
		if(i==1||m/i!=m/(i-1))
			sm2++;
	}
	for(int i=1;i<=tp;i++)
		printf("%d ",st[i]);
	printf("\nsm:%d sm2:%d\n",sm,sm2);
	printf("%d",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	dp();
	return 0;
}
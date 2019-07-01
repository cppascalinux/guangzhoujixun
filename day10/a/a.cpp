#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define li long long
#define mod 1000000007
using namespace std;
int n,k;
int pm[6000007],f[100000007];
bitset<100000007> vis;
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void solve()
{
	vis[1]=1;
	f[1]=1;
	int tot=0;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
			f[i]=qpow(i,k),pm[++tot]=i;
		for(int j=1;j<=tot&&i*pm[j]<=n;j++)
		{
			int p=i*pm[j];
			vis[p]=1;
			if(i%pm[j]==0)
			{
				f[p]=f[i];
				break;
			}
			else
				f[p]=(li)f[i]*f[pm[j]]%mod;
		}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+f[i])%mod;
	printf("%d",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&k);
	solve();
	return 0;
}
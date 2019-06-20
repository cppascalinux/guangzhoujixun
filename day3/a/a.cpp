#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
li n;
int pm[10000009],phi[10000009],vis[10000009];
void init()
{
	phi[1]=vis[1]=1;
	int m=10000000,tp=0;
	for(int i=2;i<=m;i++)
	{
		if(!vis[i])
			phi[i]=i-1,pm[++tp]=i;
		for(int j=1;j<=tp&&i*pm[j]<=m;j++)
		{
			int nv=i*pm[j];
			vis[nv]=1;
			if(i%pm[j]==0)
			{
				phi[nv]=phi[i]*pm[j];
				break;
			}
			else
				phi[nv]=phi[i]*(pm[j]-1);
		}
	}
	// for(int i=1;i<=100;i++)
	// 	printf("i:%d vis:%d phi:%d\n",i,vis[i],phi[i]);
}
void solve()
{
	li ans=0;
	for(int i=1;(li)i*i<=n;i++)
		ans+=(n/((li)i*i))*phi[i];
	printf("%lld",ans*2-n);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%lld",&n);
	init();
	solve();
	return 0;
}
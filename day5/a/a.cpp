#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n,q;
int s[200009];
li f[2009][2009][2];
void init()
{
	memset(f,0x80,sizeof(f));
	f[0][0][0]=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=n;j++)
			f[i][j][0]=max(f[i-1][j][0],f[i-1][j][1]);
		for(int j=1;j<=n;j++)
			f[i][j][1]=max(f[i][j][1],f[i-1][j-1][0]+s[i]);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",s+i);
	init();
	scanf("%d",&q);
	for(int i=1,a;i<=q;i++)
	{
		scanf("%d",&a);
		printf("%lld\n",max(f[n][a][0],f[n][a][1]));
	}
	return 0;
}
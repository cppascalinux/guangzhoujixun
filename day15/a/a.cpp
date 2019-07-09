#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define ldb long double
using namespace std;
int n;
int v[100009],w[100009];
li sv[100009],sw[100009];
namespace part1
{
	void solve()
	{
		
	}
}
namespace part2
{
	void solve()
	{
		int ml=0;
		for(int i=1;i<=n;i++)
			if(sv[i]*2>=sv[n])
			{
				ml=i;
				break;
			}
		ldb pt=((ldb)sv[n]/2-sv[ml-1])/v[ml];
		printf("1\n%d %.10lf\n",ml,(double)pt);
		printf("%d\n",ml);
		for(int i=1;i<=ml;i++)
			printf("%d ",i);
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
	{
		scanf("%d%d",v+i,w+i);
		sv[i]=sv[i-1]+v[i],sw[i]=sw[i-1]+w[i];
	}
	if(n<=16)
		part1::solve();
	else
		part2::solve();
	return 0;
}
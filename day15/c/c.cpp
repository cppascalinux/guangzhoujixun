#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define li long long
#define int long long
using namespace std;
int n,cnt;
int ban[2009];
int l[2009],r[2009];
signed main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%lld",&n);
	for(int a,b,c,i=1;i<=n;i++)
	{
		scanf("%lld%lld",&a,&b);
		if(a==1)
		{
			scanf("%lld",&c);
			l[++cnt]=b;
			r[cnt]=c;
		}
		else if(a==2)
		{
			if(b+1<=cnt)
				ban[b+1]=1;
		}
		else
		{
			scanf("%lld",&c);
			li ans=-1;
			for(int j=1;j<=cnt;j++)
				if(!ban[j]&&l[j]<b&&r[j]>c)
					ans=max(ans,(li)((li)b-l[j])*((li)r[j]-c));
			printf("%lld\n",ans);
		}	
	}
	return 0;
}
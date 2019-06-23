#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,q;
char s[500009];
int v[500009],mnl[2009],mnr[2009];
void solve(int l,int r)
{
	int tp=0;
	for(int i=l;i<=r;i++)
		v[++tp]=(s[i]=='C'?1:-1);
	int sm=0;
	mnl[0]=mnr[tp+1]=0;
	for(int i=1;i<=tp;i++)
	{
		sm+=v[i];
		mnl[i]=max(mnl[i-1],sm>=0?0:-sm);
	}
	sm=0;
	for(int i=tp;i>=1;i--)
	{
		sm+=v[i];
		mnr[i]=max(mnr[i+1],sm>=0?0:-sm);
	}
	int ans=0;
	for(int i=0;i<=tp;i++)
		ans=max(ans,mnl[i]+mnr[i+1]);
	printf("%d\n",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%s",&n,s+1);
	scanf("%d",&q);
	for(int i=1,a,b;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		solve(a,b);
	}
	return 0;
}
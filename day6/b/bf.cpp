#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
struct pt
{
	int x,y;
	pt(){}
	pt(int a,int b){x=a,y=b;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	li operator ^(pt p){return (li)x*p.y-(li)y*p.x;}
};
int n,m;
pt wt[409],bl[409];
int sgn(li x)
{
	return x>0?1:-1;
}
li cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
void solve()
{
	li ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			pt p=wt[i],q=wt[j];
			for(int k=1;k<=m;k++)
				for(int l=k+1;l<=m;l++)
				{
					pt a=bl[k],b=bl[l];
					if(sgn(cross(a,p,q))!=sgn(cross(b,p,q))&&sgn(cross(p,a,b))!=sgn(cross(q,a,b)))
						ans++;
				}
		}
	printf("%lld",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&wt[i].x,&wt[i].y);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&bl[i].x,&bl[i].y);
	solve();
	return 0;
}
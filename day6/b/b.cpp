#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<bitset>
#define li long long
#define bst bitset<409> 
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
li ans;
pt wt[409],bl[409];
int sp1[409][409],sp2[409][409];
bst sb[809];
li cross(pt o,pt a,pt b)
{
	return (a-o)^(b-o);
}
void init()
{
	for(int i=1;i<=n+m;i++)
	{
		pt p=i<=n?wt[i]:bl[i-n];
		for(int j=1;j<=n;j++)
			if((p^wt[j])>0)
				sb[i][j]=1;
	}
}
void solve0()
{
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int sm=0;
			for(int k=1;k<=m;k++)
				if(cross(bl[k],wt[i],wt[j])>0)
					sm++;
			ans+=sm*(m-sm);
		}
}
void solve1()
{
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
		{
			int sm=0,a=i+n,b=j+n;
			pt p=bl[i],q=bl[j];
			if((p^q)<0)
				swap(p,q),swap(a,b);
			bst sp=sb[a]&(~sb[b]);
			for(int k=1;k<=n;k++)
				if(sp[k])
				{
					if(cross(wt[k],p,q)>0)
						sm++;
				}
			sp1[i][j]=sp1[j][i]=sm;
		}
	// printf("sp1:\n");
	// for(int i=1;i<=m;i++)
	// {
	//  for(int j=1;j<=m;j++)
	//      printf("%d ",sp1[i][j]);
	//  printf("\n");
	// }
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int sm=0,a=i,b=j+n;
			pt p=wt[i],q=bl[j];
			if((p^q)<0)
				swap(p,q),swap(a,b);
			bst sp=sb[a]&(~sb[b]);
			for(int k=1;k<=n;k++)
				if(k!=i&&sp[k])
				{
					pt o=wt[k];
					if(cross(o,p,q)>0)
						sm++;
				}
			sp2[i][j]=sm;
		}
	// printf("sp2:\n");
	// for(int i=1;i<=n;i++)
	// {
	//  for(int j=1;j<=m;j++)
	//      printf("%d ",sp2[i][j]);
	//  printf("\n");
	// }
}
void solve2()
{
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
		{
			int a=i+n,b=j+n,sgn1=1;
			pt np=bl[i],nq=bl[j];
			if((np^nq)<0)
				sgn1=-1,swap(np,nq),swap(a,b);
			bst sp=sb[a]&(~sb[b]);
			for(int k=1;k<=n;k++)
			{
				int sm=0;
				int sgn2=sb[j+n][k]?1:-1,sgn3=sb[i+n][k]?-1:1;
				sm=sgn1*sp1[i][j]+sgn2*sp2[k][j]+sgn3*sp2[k][i];
				sm=abs(sm);
				if(sp[k]&&cross(wt[k],np,nq)>0)
					sm--;
				// printf("i:%d j:%d k:%d sm:%d\n",i,j,k,sm);
				ans-=sm;
			}
		}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&wt[i].x,&wt[i].y);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&bl[i].x,&bl[i].y);
	init();
	solve0();//63ms
	solve1();//390ms
	solve2();//170ms
	printf("%lld",ans);
	return 0;
}

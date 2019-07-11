#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,m,q;
int mat[509][509][4];
int st[1000009];
int dp[4][2]={{-1,0},{0,-1},{1,0},{0,1}};
void solve(int sx,int sy,int d)
{
	int tp=0;
	int nx=sx,ny=sy,sd=d;
//  st[++tp]=mat[nx][ny][d];
	while(1)
	{
		nx+=dp[d][0],ny+=dp[d][1];
	//  printf("tp:%d nx:%d ny:%d\n",tp,nx,ny),fflush(stdout);
	//  assert(nx>=0&ny>=0);
		int nd=-1;
		for(int i=3;i<=6;i++)
			if(mat[nx][ny][(d+i)%4])
			{
				nd=(d+i)%4;
				break;
			}
	//  assert(nd!=-1);
		d=nd;
		st[++tp]=mat[nx][ny][d];
		// printf("nx:%d ny:%d d:%d\n",nx,ny,d);
	//  assert(tp<=1000000);
		if(nx==sx&&ny==sy&&d==sd)
			break;
	}
	sort(st+1,st+tp+1);
	int ans=0,lp=0;
	st[tp+1]=-1;
	for(int i=1;i<=tp;i++)
	{
		if(st[i]!=st[i+1])
			ans=max(ans,i-lp),lp=i;
	}
	printf("%d\n",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		for(int j=0,a;j<=m;j++)
		{
			scanf("%d",&a);
			mat[i-1][j][2]=mat[i][j][0]=a;
		}
	}
	for(int i=0;i<=n;i++)
	{
		for(int j=1,a;j<=m;j++)
		{
			scanf("%d",&a);
			mat[i][j-1][3]=mat[i][j][1]=a;
		}
	}
	for(int i=1,a,x1,y1,x2,y2,b;i<=q;i++)
	{
		scanf("%d%d%d%d%d",&a,&x1,&y1,&x2,&y2);
		if(x1>x2||y1>y2)
			swap(x1,x2),swap(y1,y2);
		if(a==1)
		{
			if(x1==x2)
				mat[x1][y1][3]=mat[x2][y2][1]=0;
			else
				mat[x1][y1][2]=mat[x2][y2][0]=0;
		}
		else
		{
			scanf("%d",&b);
			if(x1==x2)
			{
				if(b==0)
					solve(x2,y2,1);
				else
					solve(x1,y1,3);
			}
			else
			{
				if(b==0)
					solve(x1,y1,2);
				else
					solve(x2,y2,0);
			}
		}
	}
	return 0;
}
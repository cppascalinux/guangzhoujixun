#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n=1000,m=778,tp,cnt;
int mat[1009][1009],cl[1009][1009];
int dp[5][2]={{},{1,0},{-1,0},{0,1},{0,-1}};
int buc[10];
pii st[10];
int dw[5][3][2]={{},{{0,0},{-1,0},{0,-1}},{{0,0},{-1,0},{0,1}},{{0,0},{1,0},{0,-1}},{{0,0},{1,0},{0,1}}};
void dfs(int x,int y,int num)
{
	st[++tp]=pii(x,y);
	cl[x][y]=-1;
	for(int i=1;i<=4;i++)
	{
		int nx=x+dp[i][0],ny=y+dp[i][1];
		if(nx>=1&&nx<=n&&ny>=1&&ny<=m)
		{
			if(mat[nx][ny]==num&&!cl[nx][ny])
				dfs(nx,ny,num);
			else if(cl[nx][ny]>=1)
				buc[cl[nx][ny]]=1;
		}
	}
}
void getans()
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!cl[i][j]&&mat[i][j])
			{
				tp=0;
				memset(buc,0,sizeof(buc));
				dfs(i,j,mat[i][j]);
				int c=0;
				for(int i=1;i<=9;i++)
					if(!buc[i])
					{
						c=i;
						break;
					}
				for(int k=1;k<=tp;k++)
					cl[st[k].fi][st[k].se]=c;
			}
}
void fil(int sx,int sy,int ex,int ey)
{
	int tn=ex-sx+1,tm=ey-sy+1;
	if(tn%6==0)
	{
		for(int i=sx;i<=ex;i+=6)
		{
			if(tm%2==0)
			{
				for(int j=sy;j<=ey;j+=2)
				{
					for(int k=i;k<=i+5;k+=3)
					{
						mat[k][j]=mat[k][j+1]=mat[k+1][j]=++cnt;
						mat[k+1][j+1]=mat[k+2][j]=mat[k+2][j+1]=++cnt;
					}
				}
			}
			else
			{
				for(int k=i;k<=i+5;k+=2)
				{
					mat[k][sy]=mat[k][sy+1]=mat[k+1][sy]=++cnt;
					mat[k][sy+2]=mat[k+1][sy+1]=mat[k+1][sy+2]=++cnt;
				}
				for(int j=sy+3;j<=ey;j+=2)
				{
					for(int k=i;k<=i+5;k+=3)
					{
						mat[k][j]=mat[k][j+1]=mat[k+1][j]=++cnt;
						mat[k+1][j+1]=mat[k+2][j]=mat[k+2][j+1]=++cnt;
					}
				}
			}
		}
	}
	else
	{
		for(int i=sy;i<=ey;i+=6)
		{
			if(tn%2==0)
			{
				for(int j=sx;j<=ex;j+=2)
				{
					for(int k=i;k<=i+5;k+=3)
					{
						mat[j][k]=mat[j+1][k]=mat[j][k+1]=++cnt;
						mat[j+1][k+1]=mat[j][k+2]=mat[j+1][k+2]=++cnt;
					}
				}
			}
			else
			{
				for(int k=i;k<=i+5;k+=2)
				{
					mat[sx][k]=mat[sx+1][k]=mat[sx][k+1]=++cnt;
					mat[sx+2][k]=mat[sx+1][k+1]=mat[sx+2][k+1]=++cnt;
				}
				for(int j=sx+3;j<=ex;j+=2)
				{
					for(int k=i;k<=i+5;k+=3)
					{
						mat[j][k]=mat[j+1][k]=mat[j][k+1]=++cnt;
						mat[j+1][k+1]=mat[j][k+2]=mat[j+1][k+2]=++cnt;
					}
				}
			}
		}
	}
}
int tmd[20][20],vis[20][20];
int bf(int d,int mxd,int tn,int tm,int lx,int ly)
{
	if(d>mxd)
		return 1;
	for(int i=lx;i<=tn;i++)
		for(int j=1;j<=tm;j++)
			if(!vis[i][j])
			{
				vis[i][j]=1;
				for(int k=1;k<=4;k++)
				{
					int fg=1;
					for(int l=1;l<=2;l++)
					{
						int nx=i+dw[k][l][0],ny=j+dw[k][l][1];
						if(nx<1||nx>tn||ny<1||ny>tm||vis[nx][ny])
							fg=0;
					}
					if(!fg)
						continue;
					for(int l=1;l<=2;l++)
					{
						int nx=i+dw[k][l][0],ny=j+dw[k][l][1];
						vis[nx][ny]=d;
					}
					if(bf(d+1,mxd,tn,tm,i,j))
						return 1;
					for(int l=1;l<=2;l++)
					{
						int nx=i+dw[k][l][0],ny=j+dw[k][l][1];
						vis[nx][ny]=0;
					}
				}
				vis[i][j]=0;
			}
	return 0;
}
int main()
{
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
	fil(1,1,990,m);
	fil(991,1,n,768);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&mat[i][j]);
	getans();
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=1;j<=m;j++)
	// 		printf("%d ",cl[i][j]);
	// 	printf("\n");
	// }
	for(int i=m;i>=1;i--)
	{
		for(int j=1;j<=n;j++)
			printf("%d",cl[j][i]);
		printf("\n");
	}
	return 0;
}
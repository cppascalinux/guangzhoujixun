#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m;
char s[509];
int v[509][509];
int dp[5][2]={{},{1,0},{-1,0},{0,1},{0,-1}};
//n or m equals to 1
namespace part1
{
	int s[509];
	pii ans[509];
	int out[509][509];
	void solve()
	{
		int inv=0;
		if(n==1)
		{
			for(int i=1;i<=m;i++)
				s[i]=v[1][i];
		}
		else
		{
			for(int i=1;i<=n;i++)
				s[i]=v[i][1];
			swap(n,m);
			inv=1;
		}
		int lst=1,tp=0;
		for(int i=1;i<=m;i++)
		{
			if(s[i+1]==0&&s[i]==1)
				ans[++tp]=pii(lst,i);
			else if(s[i+1]==1&&s[i]==0)
				lst=i+1;
		}
		for(int i=1;i<=tp;i++)
			for(int j=ans[i].fi;j<=ans[i].se;j++)
				out[i][j]=1;
		printf("%d\n",tp);
		for(int i=1;i<=tp;i++)
		{
			printf("+\n");
			for(int j=1;j<=m;j++)
			{
				printf("%d",out[i][j]);
				if(inv)
					printf("\n");
			}
			if(!inv)
				printf("\n");
		}
	}
}
//only one or two connected block of 1
namespace part2
{
	int vis[509][509],sm;
	void dfs(int cl,int x,int y)
	{
		vis[x][y]=cl;
		for(int i=1;i<=4;i++)
		{
			int nx=x+dp[i][0],ny=y+dp[i][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&v[nx][ny]&&!vis[nx][ny])
				dfs(cl,nx,ny);
		}
	}
	int judge()
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(v[i][j]&&!vis[i][j])
					dfs(++sm,i,j);
		return sm<=2;
	}
	void solve()
	{
		printf("%d\n",sm);
		for(int i=1;i<=sm;i++)
		{
			printf("+\n");
			for(int j=1;j<=n;j++)
			{
				for(int k=1;k<=m;k++)
					printf("%d",(int)(vis[j][k]==i));
				printf("\n");
			}
		}
	}
}
//one connected block of 0 connects all blocks of 1
namespace part3
{
	int vis1[509][509],vis0[509][509];
	int buc[25009],st[1000009],tp,smp,sm0,sm1;
	void dfs1(int cl,int x,int y)
	{
		vis1[x][y]=cl;
		for(int i=1;i<=4;i++)
		{
			int nx=x+dp[i][0],ny=y+dp[i][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&v[nx][ny]&&!vis1[nx][ny])
				dfs1(cl,nx,ny);
		}
	}
	void dfs0(int cl,int x,int y)
	{
		vis0[x][y]=cl;
		for(int i=1;i<=4;i++)
		{
			int nx=x+dp[i][0],ny=y+dp[i][1];
			if(nx>=1&&nx<=n&&ny>=1&&ny<=m)
			{
				if(v[nx][ny])
				{
					int cl1=vis1[nx][ny];
					if(!buc[cl1])
						smp++;
					buc[cl1]=1;
					st[++tp]=cl1;
				}
				else if(!vis0[nx][ny])
					dfs0(cl,nx,ny);
			}
			// if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!v[nx][ny]&&!vis0[nx][ny])
			//  dfs0(cl,nx,ny);
		}
	}
	int judge()
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(v[i][j]&&!vis1[i][j])
					dfs1(++sm1,i,j);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				if(!v[i][j]&&!vis0[i][j])
				{
					dfs0(++sm0,i,j);
					// printf("smp:%d tp:%d\n",smp,tp);
					if(smp==sm1)
						return 1;
					for(int i=1;i<=tp;i++)
						buc[st[i]]=0;
					tp=smp=0;
				}
		return 0;
	}
	void solve()
	{
		printf("2\n+\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",(int)(v[i][j]||vis0[i][j]==sm0));
			printf("\n");
		}
		printf("-\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",(int)(vis0[i][j]==sm0));
			printf("\n");
		}
	}
}
//other situations
namespace part4
{
	int ans1[509][509],ans2[509][509],ans3[509][509];
	void solve()
	{
		int inv=0;
		if(n>m)
		{
			inv=1;
			for(int i=1;i<=n;i++)
				for(int j=1;j<i;j++)
					swap(v[i][j],v[j][i]);
			swap(n,m);
		}
		for(int i=1;i<=n;i++)
			ans1[i][1]=1,ans2[i][m]=1;
		for(int i=1;i<=n;i++)
			for(int j=2;j<=m-1;j++)
			{
				if(i&1)
				{
					ans1[i][j]=1;
					if(v[i][j])
						ans2[i][j]=1;
				}
				else
				{
					ans2[i][j]=1;
					if(v[i][j])
						ans1[i][j]=1;
				}
			}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				ans3[i][j]=1;
		for(int i=1;i<=n;i++)
		{
			if(v[i][1])
				ans3[i][1]=0;
			if(v[i][m])
				ans3[i][m]=0;
		}
		if(inv)
		{
			for(int i=1;i<=m;i++)
				for(int j=1;j<i;j++)
					swap(ans1[i][j],ans1[j][i]),swap(ans2[i][j],ans2[j][i]),swap(ans3[i][j],ans3[j][i]);
			swap(n,m);
		}
		printf("3\n+\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",ans1[i][j]);
			printf("\n");
		}
		printf("+\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",ans2[i][j]);
			printf("\n");
		}
		printf("-\n");
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=m;j++)
				printf("%d",ans3[i][j]);
			printf("\n");
		}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	int sm=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			v[i][j]=s[j]-'0',sm+=v[i][j];
	}
	if(!sm)
		return printf("0"),0;
	if(n==1||m==1)
		return part1::solve(),0;
	if(part2::judge())
		return part2::solve(),0;
	if(part3::judge())
		return part3::solve(),0;
	part4::solve();
	return 0;
}
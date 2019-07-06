#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define db double
using namespace std;
int n,m,q,sm0;
int r[1009],c[1009];
int st[10],vis[10];
int frm[31][31][5],cl[31][31][5];
int dp[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
db sml;
void init()
{
	for(int i=0;i<=n;i++)
		frm[i][0][1]=frm[i][0][3]=frm[i][0][4]=-1;
	for(int i=0;i<=n;i++)
		frm[i][m][1]=frm[i][m][3]=frm[i][m][4]=-1;
	for(int i=0;i<=m;i++)
		frm[0][i][0]=frm[0][i][2]=frm[0][i][4]=-1;
	for(int i=0;i<=m;i++)
		frm[n][i][0]=frm[n][i][2]=frm[n][i][4]=-1;
}
void solve()
{
	sm0++;
	// if(st[1]!=2||st[2]!=1||st[3]!=3)
	// 	return;
	memcpy(cl,frm,sizeof(cl));
	for(int i=1;i<=q;i++)
	{
		int x=st[i];
		int cx=r[x],cy=c[x];
		// printf("i:%d x:%d cx:%d cy:%d\n",i,x,cx,cy);
		if(cl[cx][cy][4])
			continue;
		for(int j=0;j<=4;j++)
			cl[cx][cy][j]=x;
		for(int j=0;j<=3;j++)
		{
			cx=r[x],cy=c[x];
			int d=j;
			while(1)
			{
				cx+=dp[d][0],cy+=dp[d][1];
				sml++;
				if((cx==0||cx==n)&&(cy==0||cy==m))
					break;
				if(cl[cx][cy][4])
				{
					int nd=0;
					for(int k=0;k<=3;k++)
						if(cl[cx][cy][(d+k)%4])
						{
							nd=(d+k)%4;
							break;
						}
					d=nd;
				}
				else
					cl[cx][cy][4]=cl[cx][cy][d]=cl[cx][cy][d^2]=x;
			}
		}
		// printf("i:%d sml:%lf\n",i,sml);
	}
}
void dfs(int d)
{
	if(d>q)
		return solve(),void();
	for(int i=1;i<=q;i++)
		if(!vis[i])
		{
			vis[i]=1;
			st[d]=i;
			dfs(d+1);
			vis[i]=0;
		}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&q);
	init();
	for(int i=1;i<=q;i++)
		scanf("%d%d",r+i,c+i);
	dfs(1);
	// printf("sml:%lf sm0:%d\n",sml,sm0);
	printf("%.10lf",sml/sm0);
	return 0;
}
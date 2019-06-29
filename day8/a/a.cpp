#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define chmx(a,b) (a<b?(a=b,1):0)
using namespace std;
struct node
{
	int id,len,typ;
	node(){}
	node(int a,int b,int c){id=a,len=b,typ=c;}
};
int n,m,tot;
int sz[10009];
int hd[10009],eg[20009],nxt[20009];
int f[10009][509][3];
void clr()
{
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j][0]=f[i][j][1]=f[i][j][2]=0;
	for(int i=1;i<=n;i++)
		hd[i]=0;
	tot=0;
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs(int x,int fa)
{
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
			dfs(eg[i],x),sz[x]+=sz[eg[i]];
	int mx=1;
	memset(f[x],0xC0,sizeof(f[x]));
	f[x][0][0]=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			int y=eg[i];
			mx=min(mx+sz[eg[i]],m);
			for(int j=mx;j>=1;j--)
			{
				f[x][j][2]=max(f[x][j][2],f[x][j][1]+f[y][1][1]);
				for(int k=min(sz[eg[i]],j);k>=1;k--)
				{
					f[x][j][0]=max(f[x][j][0],f[x][j-k][0]+max(f[y][k][0],max(f[y][k][1],f[y][k][2])));
					f[x][j][1]=max(f[x][j][1],f[x][j-k][1]+max(f[y][k][0],max(f[y][k][1],f[y][k][2])));
					f[x][j][2]=max(f[x][j][2],f[x][j-k][2]+max(f[y][k][0],max(f[y][k][1],f[y][k][2])));
					f[x][j][1]=max(f[x][j][1],f[x][j-k][0]+f[y][k][1]+1);
					f[x][j][2]=max(f[x][j][2],f[x][j-k][1]+f[y][k+1][1]);
				}
			}
		}
	if(sz[x]==1)
		f[x][1][1]=1;
}
void getans()
{
	// for(int i=1;i<=n;i++)
	// 	for(int j=0;j<=m;j++)
	// 		printf("i:%d j:%d 0:%d 1:%d 2:%d\n",i,j,f[i][j][0],f[i][j][1],f[i][j][2]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	while(n)
	{
		for(int i=1,a,b;i<=n-1;i++)
		{
			scanf("%d%d",&a,&b);
			ins(a,b),ins(b,a);
		}
		dfs(1,0);
		getans();
		clr();
		scanf("%d%d",&n,&m);
	}
	return 0;
}
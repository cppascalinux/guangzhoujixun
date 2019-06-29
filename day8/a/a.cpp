//2019.06.29
//xsy1610 Problem A: Paths in Tree 这道题可以树形dp:f[i,j,0/1/2]表示i的子树中,选择j条路径,其中i未选/选了且可以传给父亲/选了且不能传给父亲的最大总长度
//可以暴力转移,可以证明时间复杂度是O(nm),考虑如何输出方案:首先肯定要记录每一个状态的前缀,但由于每一个状态的前缀本身会变化,因此需要
//把每一次添加一个儿子之后得到的每一个状态的前驱都暴力存在一个序列中,同时记录每个节点对应的区间,寻找答案的时候就从1号点开始dfs,每次将点染色
//并遍历这个点对应的前驱的区间,向下继续dfs,最后看每个点周围的同色点,个数<=2的一定就是路径端点,扫一遍,记录后输出即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define chmx(a,b) (a<b?(a=b,1):0)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
struct node
{
	short len1,id,len2;
	char typ1,typ2,bel;
	node(){}
	node(int a,int b,int c,int d,int e,int f){len1=a,typ1=b,id=c,len2=d,typ2=e,bel=f;}
};
int n,m,tot,tme,smcl;
int sz[10009];
int hd[10009],eg[20009],nxt[20009];
int f[10009][509][3];
int edp[10009],stp[10009];
node pre[20009][509][3];
int tcp[10009];
pii ans[10009];
void clr()
{
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j][0]=f[i][j][1]=f[i][j][2]=0;
	for(int i=1;i<=n;i++)
		hd[i]=tcp[i]=0;
	for(int i=1;i<=smcl;i++)
		ans[i]=pii(0,0);
	tme=tot=0;
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
	stp[x]=tme+1;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			int y=eg[i];
			mx=min(mx+sz[eg[i]],m);
			tme++;
			for(int j=mx;j>=1;j--)
			{
				for(int k=0;k<=2;k++)
					pre[tme][j][k]=node(j,k,0,0,0,0);
				if(chmx(f[x][j][2],f[x][j][1]+f[y][1][1]))
					pre[tme][j][2]=node(j,1,y,1,1,1);
				for(int k=min(sz[eg[i]],j);k>=1;k--)
				{
					for(int l=0;l<=2;l++)
					{
						if(chmx(f[x][j][0],f[x][j-k][0]+f[y][k][l]))
							pre[tme][j][0]=node(j-k,0,y,k,l,0);
						if(chmx(f[x][j][1],f[x][j-k][1]+f[y][k][l]))
							pre[tme][j][1]=node(j-k,1,y,k,l,0);
						if(chmx(f[x][j][2],f[x][j-k][2]+f[y][k][l]))
							pre[tme][j][2]=node(j-k,2,y,k,l,0);
					}
					if(chmx(f[x][j][1],f[x][j-k][0]+f[y][k][1]+1))
						pre[tme][j][1]=node(j-k,0,y,k,1,1);
					if(chmx(f[x][j][2],f[x][j-k][1]+f[y][k+1][1]))
						pre[tme][j][2]=node(j-k,1,y,k+1,1,1);
				}
			}
		}
	edp[x]=tme;
	if(sz[x]==1)
		f[x][1][1]=1;
}
void getans(int x,int cl,int len,int typ)
{
	// printf("x:%d cl:%d len:%d typ:%d\n",x,cl,len,typ),fflush(stdout);
	if(!x)
		return;
	if(typ>=1)
		tcp[x]=cl;
	for(int i=edp[x];i>=stp[x];i--)
	{
		node t=pre[i][len][typ];
		if(t.bel)
			getans(t.id,cl,t.len2,t.typ2);
		else
			getans(t.id,++smcl,t.len2,t.typ2);
		len=t.len1,typ=t.typ1;
		if(!len)
			break;
	}
}
void solve()
{
	// for(int i=1;i<=n;i++)
	// 	for(int j=0;j<=m;j++)
	// 		printf("i:%d j:%d 0:%d 1:%d 2:%d\n",i,j,f[i][j][0],f[i][j][1],f[i][j][2]);
	int mx=0,stk=0;
	for(int i=0;i<=2;i++)
		if(chmx(mx,f[1][m][i]))
			stk=i;
	printf("%d\n%d\n",f[1][m][stk],m);
	getans(1,smcl=1,m,stk);
	for(int i=1;i<=n;i++)
		if(tcp[i])
		{
			int sm=0;
			for(int j=hd[i];j;j=nxt[j])
				if(tcp[eg[j]]==tcp[i])
					sm++;
			// assert(sm<=2);
			if(sm<=1)
			{
				if(!ans[tcp[i]].fi)
					ans[tcp[i]].fi=ans[tcp[i]].se=i;
				else
					ans[tcp[i]].se=i;
			}
		}
	for(int i=1;i<=smcl;i++)
		if(ans[i].fi)
			printf("%d %d\n",ans[i].fi,ans[i].se);
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
		solve();
		clr();
		scanf("%d%d",&n,&m);
	}
	return 0;
}
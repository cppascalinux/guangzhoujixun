//2019.07.03
//xsy1613 Problem A: Oriental Puzzle 考虑有解的充要条件:所有的点双联通分量构成的圆方树是一条链,且1和n位于链的两端.考虑用一个splay去维护所有点之间的高度大小关系
//首先将1-n的一条路径放入splay中,然后按深度从小到大去计算每一个点双中点的顺序,根据返祖边祖先和父亲的大小关系来确定当前链的高度大小关系,在splay上dfs即可确定边的指向
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<vector>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,m,tme,cnt;
pii re[300009];
int dfn[100009],low[100009],ft[100009],itk[100009];
int dep[100009],st[100009];
int ch[100009][2],f[100009];
int vis[100009];
int kts[100009];
vector<int> g[100009];
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==ch[y][1],dy=y==ch[z][1];
	f[x]=z;
	f[y]=x;
	f[ch[x][dx^1]]=y;
	ch[z][dy]=x;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
}
void splay(int x,int fa)
{
	while(f[x]!=fa)
	{
		int y=f[x],z=f[y],dx=x==ch[y][1],dy=y==ch[z][1];
		if(z!=fa)
			rotate(dx!=dy?x:y);
		rotate(x);
	}
}
void ins(int x,int y)//insert y after x
{
	splay(x,0);
	if(!ch[x][1])
		ch[x][1]=y,f[y]=x;
	else
	{
		int p=ch[x][1];
		while(ch[p][0])
			p=ch[p][0];
		ch[p][0]=y,f[y]=p;
	}
	splay(y,0);
}
int cmp(int x,int y)//if x is less than y
{
	splay(x,0);
	splay(y,x);
	return ch[x][1]==y;
}
void dfs(int x,int fa)
{
	ft[x]=fa;
	dep[x]=dep[fa]+1;
	dfn[x]=low[x]=++tme;
	st[tme]=x;
	itk[x]=1;
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=fa)
		{
			int u=g[x][i];
			if(!dfn[u])
			{
				dfs(u,x);
				low[x]=min(low[x],low[u]);
			}
			else if(itk[u])
				low[x]=min(low[x],dfn[u]);
		}
	itk[x]=0;
}
void get(int x,int y)//get a ring from x to father of y
{
	kts[++cnt]=x;
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=ft[x])
		{
			int u=g[x][i];
			if(dfn[u]<y)
				return kts[++cnt]=u,void();
			if(low[u]<y&&!vis[u]&&ft[u]==x)
				return get(u,y),void();
		}
}
int cal(int x)//calculate bcc of x
{
	for(int i=0;i<(int)g[x].size();i++)
		if(g[x][i]!=ft[x]&&!vis[g[x][i]]&&ft[g[x][i]]==x)
		{
			int u=g[x][i];
			if(low[u]>=dfn[x])
				return 0;
			cnt=0;
			get(u,dfn[x]);
			kts[0]=x;
			if(cmp(x,kts[cnt]))
			{
				for(int i=1;i<=cnt-1;i++)
					ins(kts[i-1],kts[i]),vis[kts[i]]=1;
			}
			else
			{
				for(int i=cnt-1;i>=1;i--)
					ins(kts[i+1],kts[i]),vis[kts[i]]=1;
			}
		}
	return 1;
}
void getans(int x)
{
	if(ch[x][0])
		getans(ch[x][0]);
	vis[x]=++tme;
	if(ch[x][1])
		getans(ch[x][1]);
}
bool cpm(int x,int y)
{
	return dep[x]<dep[y];
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		g[a].pb(b),g[b].pb(a);
		re[i]=pii(a,b);
	}
	dfs(1,0);
	if(!dfn[n])
		return printf("No"),0;
	for(int i=n,j=ft[i];j;i=j,j=ft[j])
		ins(i,j),vis[i]=vis[j]=1;
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d ft:%d dfn:%d low:%d vis:%d\n",i,ft[i],dfn[i],low[i],vis[i]);
	sort(st+1,st+tme+1,cpm);
	for(int i=1;i<=tme;i++)
		if(!cal(st[i]))
			return printf("No"),0;
	for(int i=1;i<=m;i++)
		if(!vis[re[i].fi]||!vis[re[i].se])
			return printf("No"),0;
	tme=0;
	splay(1,0);
	getans(1);
	printf("Yes\n");
	for(int i=1;i<=m;i++)
	{
		if(vis[re[i].fi]<vis[re[i].se])
			swap(re[i].fi,re[i].se);
		printf("%d %d\n",re[i].fi,re[i].se);
	}
	return 0;
}
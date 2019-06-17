#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
#define li long long
using namespace std;
int n,m,tot,mn,rt,tp;
int hd[100009],eg[200009],nxt[200009];
int sz[100009],vis[100009];
int buc[100009],st[100009];
int dis[100009];
li ans[100009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void getrt(int x,int fa,int siz)
{
	sz[x]=1;
	int mx=0;
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa&&!vis[eg[i]])
		{
			getrt(eg[i],x,siz);
			mx=max(mx,sz[eg[i]]);
			sz[x]+=sz[eg[i]];
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
		mn=mx,rt=x;
}
void dfs(int x,int fa,int l)
{
	dis[x]=l;
	st[++tp]=x;
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]]&&eg[i]!=fa)
			dfs(eg[i],x,l+1);
}
void cal(int x,int l,int sgn)
{
	tp=0;
	dfs(x,0,l);
	for(int i=1;i<=tp;i++)
		buc[dis[st[i]]]++;
	for(int i=1;i<=tp;i++)
	{
		int x=st[i];
		if(dis[x]<=4)
		{
			buc[dis[x]]--;
			ans[x]+=sgn*buc[4-dis[x]];
			buc[dis[x]]++;
		}
	}
	for(int i=1;i<=tp;i++)
		buc[dis[st[i]]]=0;
}
void solve(int x,int siz)
{
	vis[x]=1;
	cal(x,0,1);
	for(int i=hd[x];i;i=nxt[i])
		if(!vis[eg[i]])
		{
			cal(eg[i],1,-1);
			int nsz=sz[eg[i]]>sz[x]?siz-sz[x]:sz[eg[i]];
			mn=inf;
			getrt(eg[i],0,nsz);
			solve(rt,nsz);
		}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b),ins(b,a);
	}
	mn=inf;
	getrt(1,0,n);
	solve(rt,n);
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
//2019.06.27
//xsy1609 Problem B: Tree 考虑一下如果A是一条链该如何维护:可以先将所有询问离线,然后按右端点从小到大扫描,用线段树去维护左端点中点数-边数的最小值min和最小值
//的个数cnt,再去维护当前左端点所对应的总答案sum,还要维护两个懒标记lazymin和lazysum,每次右端点x+1,首先将1-x的min都+1,然后看右端点在B中对应的所有相邻点v
//如果v在A中在x的左侧,那么就要将1-v的min-1,将所有相邻点都扫描完之后,需要将1-x中所有min为1的左端点的sum+1,考虑如何实现:首先将所有min=1的区间的sum+=cnt,
//lazysum++,然后标记下传的时候,先下传lazymin标记,然后看如果左儿子的min=当前点的min,则将标记传给左儿子,右儿子同理(因为当前点的lazymin标记不会改变
//区间内min的相对大小关系,说明左儿子的min曾经=1),本质就是维护历史最小值(1)的出现次数,也可以直接维护:min,cnt,hmin,hcnt,lazymin,hlazymin,hlazymincnt
//标记下传的时候用htag和min去更新hcnt,询问的时候直接查询区间内sum/hcnt的和
//然后考虑在A为一棵树怎么做:如果u和v的lca=u或v,那么可以使用类似的扫描线,只不过变成了子树加,树链查询,可以使用树链剖分
//然后考虑如何处理lca!=u,v的部分:首先算出u-lca,v-lca的答案,然后考虑跨过lca的答案:在lca的轻子树中暴力dfs,遇到一个u时,询问v的答案,回溯时撤销修改即可
//总时间复杂度为O(nlog^2n)
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
#define li long long
using namespace std;
struct node
{
	int u,v,id;
	node(){}
	node(int a,int b,int c){u=a,v=b,id=c;}
};
int n,m,tme;
vector<int> ta[100009],tb[100009];
int dep[100009],sz[100009],top[100009],son[100009];
int dfn[100009],ed[100009];
int f[100009][17];
int mn[400009],cn[400009],lzmn[400009],lzsm[400009];
li sm[400009];
li ans[100009];
vector<node> qry[100009];
vector<pii> gta[100009];
int vis[100009];
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	sz[x]=1;
	f[x][0]=fa;
	for(int i=1;i<=16;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=0;i<(int)ta[x].size();i++)
	{
		int y=ta[x][i];
		if(y!=fa)
		{
			dfs1(y,x);
			if(sz[y]>sz[son[x]])
				son[x]=y;
			sz[x]+=sz[y];
		}
	}
}
void dfs2(int x,int tp)
{
	top[x]=tp;
	ed[x]=dfn[x]=++tme;
	if(son[x])
	{
		dfs2(son[x],tp);
		ed[x]=max(ed[x],ed[son[x]]);
	}
	for(int i=0;i<(int)ta[x].size();i++)
	{
		int y=ta[x][i];
		if(y!=f[x][0]&&y!=son[x])
		{
			dfs2(y,y);
			ed[x]=max(ed[x],ed[y]);
		}
	}
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
	for(int i=0;i<=16;i++)
		if(l>>i&1)
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=16;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	sm[a]=sm[la]+sm[ra];
	mn[a]=min(mn[la],mn[ra]);
	cn[a]=0;
	if(mn[a]==mn[la])
		cn[a]+=cn[la];
	if(mn[a]==mn[ra])
		cn[a]+=cn[ra];
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	if(lzmn[a])
	{
		int v=lzmn[a];
		lzmn[a]=0;
		mn[la]+=v,mn[ra]+=v;
		lzmn[la]+=v,lzmn[ra]+=v;
	}
	if(lzsm[a])
	{
		int v=lzsm[a];
		lzsm[a]=0;
		if(mn[a]==mn[la])
		{
			sm[la]+=v*cn[la];
			lzsm[la]+=v;
		}
		if(mn[a]==mn[ra])
		{
			sm[ra]+=v*cn[ra];
			lzsm[ra]+=v;
		}
	}
}
void build(int a,int l,int r)
{
	if(l==r)
		return cn[a]=1,void();
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a);
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return mn[a]+=val,lzmn[a]+=val,void();
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
void setsm(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		if(mn[a]==1)
		{
			sm[a]+=val*cn[a];
			lzsm[a]+=val;
		}
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	setsm(a<<1,l,mid,ll,rr,val);
	setsm(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
li ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		return 0;
	if(l>=ll&&r<=rr)
		return sm[a];
	down(a);
	int mid=(l+r)>>1;
	return ask(a<<1,l,mid,ll,rr)+ask(a<<1|1,mid+1,r,ll,rr);
}
li getsm(int x,int y)
{
	li ans=0;
	int fx=top[x],fy=top[y];
	while(fx!=fy)
	{
		if(dep[fx]<dep[fy])
			swap(x,y),swap(fx,fy);
		ans+=ask(1,1,n,dfn[fx],dfn[x]);
		x=f[fx][0],fx=top[x];
	}
	if(dfn[x]>dfn[y])
		swap(x,y);
	ans+=ask(1,1,n,dfn[x]+1,dfn[y]);
	return ans;
}
void dfs4(int x,int fa,int mndfn,int mxdfn,int lca)
{
	//changes
	vis[x]=1;
	add(1,1,n,1,n,1);
	for(int i=0;i<(int)tb[x].size();i++)
	{
		int y=tb[x][i];
		if(vis[y])
			add(1,1,n,1,n,-1);
		else if(dfn[y]>=mndfn&&dfn[y]<=mxdfn)
			add(1,1,n,dfn[y],ed[y],-1);
	}
	setsm(1,1,n,1,n,1);
	//getans
	for(int i=0;i<(int)gta[x].size();i++)
		ans[gta[x][i].se]+=getsm(gta[x][i].fi,lca);
	//dfs
	for(int i=0;i<(int)ta[x].size();i++)
		if(ta[x][i]!=fa)
			dfs4(ta[x][i],x,mndfn,mxdfn,lca);
	//undo changes
	setsm(1,1,n,1,n,-1);
	for(int i=0;i<(int)tb[x].size();i++)
	{
		int y=tb[x][i];
		if(vis[y])
			add(1,1,n,1,n,1);
		else if(dfn[y]>=mndfn&&dfn[y]<=mxdfn)
			add(1,1,n,dfn[y],ed[y],1);
	}
	add(1,1,n,1,n,-1);
	vis[x]=0;
}
void dfs3(int x,int fa)
{
	for(int i=0;i<(int)ta[x].size();i++)
		if(ta[x][i]!=fa)
			dfs3(ta[x][i],x);
	add(1,1,n,dfn[x],ed[x],1);
	for(int i=0;i<(int)tb[x].size();i++)
	{
		int y=tb[x][i];
		if(dfn[y]>=dfn[x]&&dfn[y]<=ed[x])
			add(1,1,n,dfn[y],ed[y],-1);
	}
	// printf("x:%d--------------------\n",x);
	setsm(1,1,n,dfn[x],ed[x],1);
	// printf("sm:%lld\n",sm[1]);
	for(int i=0;i<(int)qry[x].size();i++)
	{
		node t=qry[x][i];
		// printf("t.u:%d t.v:%d t.id:%d\n",t.u,t.v,t.id);
		ans[t.id]=getsm(t.v,x)+1;
		if(t.u!=x)
			gta[t.v].pb(pii(t.u,t.id));
	}
	for(int i=0;i<(int)ta[x].size();i++)
		if(ta[x][i]!=fa&&ta[x][i]!=son[x])
			dfs4(ta[x][i],x,dfn[x],dfn[ta[x][i]]-1,x);
	for(int i=0;i<(int)qry[x].size();i++)
		gta[qry[x][i].v].clear();
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		ta[a].pb(b),ta[b].pb(a);
	}
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		tb[a].pb(b),tb[b].pb(a);
	}
	dfs1(1,0);
	dfs2(1,1);
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d sz:%d son:%d top:%d dfn:%d ed:%d\n",i,sz[i],son[i],top[i],dfn[i],ed[i]);
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(dfn[a]>dfn[b])
			swap(a,b);
		int lca=getlca(a,b);
		qry[lca].pb(node(a,b,i));
	}
	build(1,1,n);
	dfs3(1,0);
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
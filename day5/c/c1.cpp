//2019.06.25
//xsy1607 Problem C 将原串和所有单词一起建AC自动机,fij表示trie上i号点所代表的串的子串中,左端点为j的单词的价值总和,对于每个点用可持久化fhq treap维护j的答案,
//考虑每个点答案的组成部分,首先是他自身代表的串,然后长度<=len[fail]的单词可以由fail直接合并过来,而长度>len[fail]的单词可以由trie上的父亲合并过来
//因为一定不存在长度>len[fail]的以i为右端点的单词(否则fail会更长)所以这样做是对的,按bfs序合并即可保证每个点的fail和父亲都已经算过
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
#define pb push_back
using namespace std;
int n,m,q,opt,cnt,tot,lst;
char s0[200009],t0[200009];
int pp[200009];
int o[400009][27],fil[400009],dep[400009];
int ord[400009],fa[400009];
vector<int> vp[400009];
int rt[400009];
int sz[20000009],ch[20000009][2],v[20000009];
li sm[20000009];
void add0()
{
	int cur=0;
	for(int i=1;i<=n;i++)
	{
		int p=s0[i];
		if(!o[cur][p])
			o[cur][p]=++tot;
		dep[o[cur][p]]=dep[cur]+1;
		fa[o[cur][p]]=cur;
		cur=o[cur][p];
		pp[i]=cur;
	}
}
void add1(int l,int val)
{
	int cur=0;
	for(int i=1;i<=l;i++)
	{
		int p=t0[i];
		if(!o[cur][p])
			o[cur][p]=++tot;
		dep[o[cur][p]]=dep[cur]+1;
		fa[o[cur][p]]=cur;
		cur=o[cur][p];
	}
	vp[cur].pb(val);
}
void getfail()
{
	queue<int> q;
	q.push(0);
	int tp=0;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		if(x)
			ord[++tp]=x;
		for(int i=1;i<=26;i++)
			if(o[x][i])
			{
				if(x)
					fil[o[x][i]]=o[fil[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[fil[x]][i];
	}
	// for(int i=0;i<=tot;i++)
	//  printf("%d fail:%d fa:%d\n",i,fil[i],fa[i]);
}
int cln(int x)
{
	int y=++cnt;
	sz[y]=sz[x];
	ch[y][0]=ch[x][0],ch[y][1]=ch[x][1];
	v[y]=v[x];
	sm[y]=sm[x];
	return y;
}
int newnode(int val)
{
	int x=++cnt;
	v[x]=sm[x]=val;
	sz[x]=1;
	return x;
}
void update(int x)
{
	int lx=ch[x][0],rx=ch[x][1];
	sz[x]=sz[lx]+sz[rx]+1;
	sm[x]=sm[lx]+sm[rx]+v[x];
}
pii split(int x,int k)
{
	if(!x)
		return pii(0,0);
	if(x<=lst)
		x=cln(x);
	int lsz=sz[ch[x][0]];
	if(k<=lsz)
	{
		pii t=split(ch[x][0],k);
		ch[x][0]=t.se;
		update(x);
		return pii(t.fi,x);
	}
	else
	{
		pii t=split(ch[x][1],k-lsz-1);
		ch[x][1]=t.fi;
		update(x);
		return pii(x,t.se);
	}
}
int mrg(int x,int y)
{
	if(!x||!y)
		return x+y;
	if(rand()%(sz[x]+sz[y])<sz[x])
	{
		if(x<=lst)
			x=cln(x);
		ch[x][1]=mrg(ch[x][1],y);
		update(x);
		return x;
	}
	else
	{
		if(y<=lst)
			y=cln(y);
		ch[y][0]=mrg(x,ch[y][0]);
		update(y);
		return y;
	}
}
void ins(int x)
{
	pii t1=split(rt[x],1);
	// printf("x:%d sz:%d\n",x,vp[x].size());
	for(int i=0;i<(int)vp[x].size();i++)
		v[t1.fi]+=vp[x][i],sm[t1.fi]+=vp[x][i];
	rt[x]=mrg(t1.fi,t1.se);
}
void solve()
{
	for(int i=1;i<=tot;i++)
	{
		int x=ord[i];
		lst=cnt;
		// printf("i:%d x:%d\n",i,x);
		if(fil[x])
		{
			pii t=split(rt[fa[x]],dep[x]-dep[fil[x]]);
			rt[x]=mrg(t.fi,rt[fil[x]]);
		}
		else
			rt[x]=mrg(rt[fa[x]],newnode(0));
		ins(x);
	}
}
li getans(int l,int r)
{
	lst=cnt;
	int p=pp[r];
	pii t1=split(rt[p],l-1);
	// printf("l:%d r:%d p:%d sz:%d\n",l,r,p,sz[t1.se]);
	return sm[t1.se];
	cnt=lst;
}
void dfs(int x)
{
	if(!x)
		return;
	// down(x);
	dfs(ch[x][0]);
	printf("x:%d v:%d sm:%lld\n",x,v[x],sm[x]);
	dfs(ch[x][1]);
}
void dbg()
{
	for(int i=0;i<=tot;i++)
	{
		printf("i:%d-------------------------------\n",i);
		dfs(rt[i]);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	srand(20020618);
	scanf("%d%d%d",&n,&m,&opt);
	scanf("%s",s0+1);
	for(int i=1;i<=n;i++)
		s0[i]-='a'-1;
	add0();
	for(int i=1,a;i<=m;i++)
	{
		scanf("%s%d",t0+1,&a);
		int l=strlen(t0+1);
		for(int j=1;j<=l;j++)
			t0[j]-='a'-1;
		add1(l,a);
	}
	getfail();
	solve();
	// dbg();
	li lans=0;
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		li a,b;
		scanf("%lld%lld",&a,&b);
		if(opt)
			a^=lans,b^=lans;
		printf("%lld\n",lans=getans(a,b));
	}
	return 0;
}

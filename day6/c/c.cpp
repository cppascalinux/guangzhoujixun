//2019.06.24
//xsy1608 Problem C: 子串排列 先对原串反串建sam,然后将所有区间定位到parent树上,两个区间的lcp长度就是树上的lca深度,不难发现一个性质:将所有点按照dfs序排序之后,
//l和r的lca=[l,r)中i和i+1的lca中深度最浅的一个,有了这个性质之后如何处理询问:每次在将所有询问拿出来建一棵虚树,对于每个子树维护字典序最大的lca深度序列,每次将一个点
//所有儿子按照序列字典序从大到小排序,然后合并到重儿子上(用deque维护序列),考虑正确性:除非一个点是子树内的最后一个点,否则它的后一个点一定也在子树内,因为跳出这个
//dfs序区间后答案肯定不会变优(由前面的性质可知),时间复杂度:比较两个序列字典序大小的时间复杂度为O(min(l1,l2)),每个序列比较次数是它在快排结构中的深度<=logn
//所以单层复杂度为logn*轻子树大小和,总时间复杂度为n*log^2n
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<deque>
#include<cassert>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define pf push_front
using namespace std;
int n,m,lst=1,cnt=1,tme;
char s[200009];
int pos[200009];
int o[400009][27],lnk[400009],len[400009];
vector<int> mt[400009];
int f[400009][19],dep[400009],dfn[400009];
int lp[200009],rp[200009];
vector<int> qry[400009],vt[400009];
pii ps[400009];
int st[400009];
int sz[400009],son[400009];
deque<int> qs[400009];
void add(int c,int id)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	pos[id]=cur;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			lnk[cln]=lnk[q];
			len[cln]=len[p]+1;
			memcpy(o[cln],o[q],27<<2);
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void clrv(vector<int> &v)
{
	vector<int> tmp;
	tmp.swap(v);
}
void clrq(deque<int> &v)
{
	deque<int> tmp;
	tmp.swap(v);
}
void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	dfn[x]=++tme;
	f[x][0]=fa;
	// printf("x:%d fa:%d len:%d\n",x,fa,len[x]);
	for(int i=1;i<=18;i++)
		f[x][i]=f[f[x][i-1]][i-1];
	for(int i=0;i<(int)mt[x].size();i++)
		dfs1(mt[x][i],x);
}
int getlca(int a,int b)
{
	if(dep[a]<dep[b])
		swap(a,b);
	int l=dep[a]-dep[b];
	for(int i=0;i<=18;i++)
		if(l>>i&1)
			a=f[a][i];
	if(a==b)
		return a;
	for(int i=18;i>=0;i--)
		if(f[a][i]!=f[b][i])
			a=f[a][i],b=f[b][i];
	return f[a][0];
}
int getp(int l,int r)
{
	int ls=r-l+1,x=pos[r];
	for(int i=18;i>=0;i--)
		if(len[f[x][i]]>=ls)
			x=f[x][i];
	return x;
}
void build(pii *s,int l)
{
	sort(s+1,s+l+1);
	int tp=0;
	for(int i=1;i<=l;i++)
	{
		if(s[i].se==s[i-1].se)
			continue;
		int x=s[i].se;
		if(!tp)
		{
			st[++tp]=x;
			continue;
		}
		int lca=getlca(x,st[tp]);
		// printf("x:%d lca:%d\n",x,lca),fflush(stdout);
		while(tp>1&&dfn[lca]<=dfn[st[tp-1]])
		{
			vt[st[tp-1]].pb(st[tp]);
			tp--;
		}
		if(lca!=st[tp])
		{
			vt[lca].pb(st[tp]);
			st[tp]=lca;
		}
		st[++tp]=x;
	}
	while(tp>1)
	{
		vt[st[tp-1]].pb(st[tp]);
		tp--;
	}
}
void dfs2(int x)
{
	sz[x]=qry[x].size();
	sz[0]=-1,son[x]=0;
	for(int i=0;i<(int)vt[x].size();i++)
	{
		int p=vt[x][i];
		dfs2(p);
		if(sz[p]>sz[son[x]])
			son[x]=p;
		sz[x]+=sz[p];
	}
	// clrv(vt[x]);
}
bool cmp(int a,int b)
{
	int l=min(qs[a].size(),qs[b].size());
	for(int i=0;i<l;i++)
		if(qs[a][i]!=qs[b][i])
			return qs[a][i]>qs[b][i];
	return qs[a].size()>qs[b].size();
}
void dfs3(int x)
{
	sort(qry[x].begin(),qry[x].end(),greater<int>());
	if(!son[x])
	{
		if(qry[x].size())
			qs[x].insert(qs[x].begin(),qry[x].begin()+1,qry[x].end());
		clrv(qry[x]);
		return;
	}
	for(int i=0;i<(int)vt[x].size();i++)
	{
		int p=vt[x][i];
		dfs3(p);
	}
	assert(vt[x].size()>0);
	sort(vt[x].begin(),vt[x].end(),cmp);
	// printf("x:%d | ",x);
	// for(int i=0;i<(int)vt[x].size();i++)
	// 	printf("%d ",vt[x][i]);
	// printf("\n");
	int np=0;
	for(int i=0;i<(int)vt[x].size();i++)
		if(vt[x][i]==son[x])
			np=i;
	clrq(qs[x]);
	qs[x].swap(qs[son[x]]);
	for(int i=np-1;i>=0;i--)
	{
		qs[x].pf(len[x]);
		qs[x].insert(qs[x].begin(),qs[vt[x][i]].begin(),qs[vt[x][i]].end());
		clrq(qs[vt[x][i]]);
	}
	for(int i=np+1;i<(int)vt[x].size();i++)
	{
		qs[x].pb(len[x]);
		qs[x].insert(qs[x].end(),qs[vt[x][i]].begin(),qs[vt[x][i]].end());
		clrq(qs[vt[x][i]]);
	}
	qs[x].insert(qs[x].end(),qry[x].begin(),qry[x].end());
	clrv(qry[x]);
	clrv(vt[x]);
}
void solve(int tot)
{
	int tp=0;
	for(int i=1;i<=tot;i++)
	{
		int t=getp(lp[i],rp[i]);
		// printf("l:%d r:%d t:%d\n",lp[i],rp[i],t);
		qry[t].pb(rp[i]-lp[i]+1);
		ps[++tp]=pii(dfn[t],t);
	}
	// printf("\n\n"),fflush(stdout);
	ps[++tp]=pii(1,1);
	build(ps,tp);
	dfs2(1);
	dfs3(1);
	for(int i=0;i<(int)qs[1].size();i++)
		printf("%d ",qs[1][i]);
	printf("\n");
	clrq(qs[1]);
	// for(int i=1;i<=cnt;i++)
	// {
	// 	// clrv(vt[i]);
	// 	clrv(qry[i]);
	// 	// clrq(qs[i]);
	// }
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%s",&n,&m,s+1);
	for(int i=n;i>=1;i--)
		add(s[i]-'a'+1,n-i+1);
	for(int i=2;i<=cnt;i++)
		mt[lnk[i]].pb(i);
	dfs1(1,0);
	for(int i=1,a;i<=m;i++)
	{
		scanf("%d",&a);
		for(int j=1;j<=a;j++)
		{
			scanf("%d%d",lp+j,rp+j);
			lp[j]=n-lp[j],rp[j]=n-rp[j],swap(lp[j],rp[j]);
		}
		solve(a);
	}
	return 0;
}
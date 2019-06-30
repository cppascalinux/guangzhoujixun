//2019.06.30
//xsy1610 首先对于只有一棵树的情况,答案显然是C(n,4),因为每一个叶子的四元组都只有一种划分方法,那么只需求出在两棵树内都存在的划分方案的种数即可
//考虑计算两棵树中都有的划分方案:首先对T1和T2分别dfs,求出他们的dfs序,然后开一个矩阵,如果x在T1中的dfs序为a,在T2中的dfs序为b,那么就把(a,b)位置设为1
//再将矩阵做一遍前缀和,这样预处理完之后就可以O(1)查询在T1中dfs序区间为[l1,r1],在T2中dfs序为[l2,r2]的点的个数
//然后考虑如何去统计在两棵树中都存在的四元划分:枚举T1中的边(u1,v1),T2中的边(u2,v2),考虑去统计划分ab|cd,其中路径(a,b)和路径(c,d)无交,令u1,u2分别是
//a,b在T1,T2中的LCA(以v1,v2为根的前提下),那么只需要统计有多少点在v1,v2的子树中都出现了,这个可以在矩阵中直接查询,以及多少点在u1,u2的子树中出现了,还要求点对
//位于不同子树中,这个可以容斥,再拿组合数算一算即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define li long long
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,tme,m;
vector<int> t1[2009],t2[2009];
int dfn1[2009],ed1[2009],dfn2[2009],ed2[2009];
int dep1[2009],dep2[2009];
int sm[1009][1009];
pii e1[4009],e2[4009];
void dfs1(int x,int fa)
{
	if(x<=n)
		dfn1[x]=ed1[x]=++tme;
	else
		dfn1[x]=ed1[x]=tme+1;
	dep1[x]=dep1[fa]+1;
	for(int i=0;i<(int)t1[x].size();i++)
		if(t1[x][i]!=fa)
		{
			dfs1(t1[x][i],x);
			ed1[x]=max(ed1[x],ed1[t1[x][i]]);
		}
}
void dfs2(int x,int fa)
{
	if(x<=n)
		dfn2[x]=ed2[x]=++tme;
	else
		dfn2[x]=ed2[x]=tme+1;
	dep2[x]=dep2[fa]+1;
	for(int i=0;i<(int)t2[x].size();i++)
		if(t2[x][i]!=fa)
		{
			dfs2(t2[x][i],x);
			ed2[x]=max(ed2[x],ed2[t2[x][i]]);
		}
}
void init()
{
	for(int i=1;i<=n;i++)
		sm[dfn1[i]][dfn2[i]]++;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			sm[i][j]+=sm[i-1][j]+sm[i][j-1]-sm[i-1][j-1];
}
int getsm(int l1,int r1,int l2,int r2)
{
	return sm[r1][r2]-sm[l1-1][r2]-sm[r1][l2-1]+sm[l1-1][l2-1];
}
int gett(int f1,int x1,int f2,int x2)
{
	int g1=dep1[x1]>dep1[f1],g2=dep2[x2]>dep2[f2];
	if(g1&&g2)
		return getsm(dfn1[x1],ed1[x1],dfn2[x2],ed2[x2]);
	if(g1&&!g2)
		return getsm(dfn1[x1],ed1[x1],1,dfn2[f2]-1)+getsm(dfn1[x1],ed1[x1],ed2[f2]+1,n);
	if(!g1&&g2)
		return getsm(1,dfn1[f1]-1,dfn2[x2],ed2[x2])+getsm(ed1[f1]+1,n,dfn2[x2],ed2[x2]);
	return getsm(1,dfn1[f1]-1,1,dfn2[f2]-1)+getsm(1,dfn1[f1]-1,ed2[f2]+1,n)+
			getsm(ed1[f1]+1,n,1,dfn2[f2]-1)+getsm(ed1[f1]+1,n,ed2[f2]+1,n);
}
int cb2(int x)
{
	return (x*(x-1))>>1;
}
void solve()
{
	li ans=0;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
		{
			int x1=e1[i].fi,f1=e1[i].se,x2=e2[j].fi,f2=e2[j].se;
			int sm1=cb2(gett(x1,f1,x2,f2));
			int s1[3],s2[3],tp1=0,tp2=0;
			for(int k=0;k<(int)t1[x1].size();k++)
				if(t1[x1][k]!=f1)
					s1[++tp1]=t1[x1][k];
			for(int k=0;k<(int)t2[x2].size();k++)
				if(t2[x2][k]!=f2)
					s2[++tp2]=t2[x2][k];
			int sm2=cb2(gett(f1,x1,f2,x2));
			for(int k=1;k<=2;k++)
			{
				sm2-=cb2(gett(x1,s1[k],f2,x2));
				sm2-=cb2(gett(f1,x1,x2,s2[k]));
			}
			for(int k=1;k<=2;k++)
				for(int l=1;l<=2;l++)
					sm2+=cb2(gett(x1,s1[k],x2,s2[l]));
			ans+=(li)sm1*sm2;
		}
	li out=(li)n*(n-1)*(n-2)*(n-3)/12;
	printf("%lld",out-ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b;i<=2*n-3;i++)
	{
		scanf("%d%d",&a,&b);
		t1[a].pb(b),t1[b].pb(a);
		if(a>n&&b>n)
			e1[++m]=pii(a,b),e1[++m]=pii(b,a);
	}
	m=0;
	for(int i=1,a,b;i<=2*n-3;i++)
	{
		scanf("%d%d",&a,&b);
		t2[a].pb(b),t2[b].pb(a);
		if(a>n&&b>n)
			e2[++m]=pii(a,b),e2[++m]=pii(b,a);
	}
	dfs1(1,0);
	tme=0;
	dfs2(1,0);
	init();
	solve();
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<cassert>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n;
vector<int> t1[300009],t2[300009];
pii e1[300009],e2[300009];
int dep[300009],fail[300009],st[300009];
int cl[300009],nf[300009];
map<int,int> o[300009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
int solve(int s)
{
	queue<int> q;
	memset(dep,0,(n+1)<<2);
	dep[s]=1,q.push(s);
	int tp=0;
	while(!q.empty())
	{
		int x=q.front();
		st[++tp]=x;
		q.pop();
		for(int i=0;i<(int)t1[x].size();i++)
			if(!dep[t1[x][i]])
			{
				dep[t1[x][i]]=dep[x]+1;
				q.push(t1[x][i]);
			}
	}
	memset(fail,0,(n+1)<<2);
	for(int i=1;i<=n-1;i++)
	{
		int u=e2[i].fi,v=e2[i].se;
		if(dep[u]==dep[v])
			return 0;
		if(dep[u]>dep[v])
			fail[u]=v;
		else
			fail[v]=u;
	}
	// printf("s:%d----------------------------\n",s);
	for(int i=2;i<=n;i++)
		if(!fail[st[i]])
			return 0;
	int cnt=0;
	cl[s]=0;
	for(int i=2;i<=n;i++)
	{
		int x=st[i];
		if(fail[x]==s)
			cl[x]=++cnt;
		else
			cl[x]=cl[fail[x]];
	}
	for(int i=1;i<=n;i++)
		o[i].clear();
	for(int i=1;i<=n;i++)
	{
		int x=st[i];
		for(int j=0;j<(int)t1[x].size();j++)
			if(dep[x]<dep[t1[x][j]])
				o[x][cl[t1[x][j]]]=t1[x][j];
	}
	nf[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int x=q.front();
		// printf("x:%d\n",x),fflush(stdout);
		q.pop();
		for(map<int,int>::iterator it=o[x].begin();it!=o[x].end();it++)
		{
			int j=nf[x];
			while(j&&j!=s&&!o[j].count(it->fi))
				j=nf[j];
			if(x!=s)
				nf[it->se]=o[j].count(it->fi)?o[j][it->fi]:s;
			else
				nf[it->se]=s;
			q.push(it->se);
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("%d| dep:%d| fail:%d| st:%d cl:%d nf:%d\n",i,dep[i],fail[i],st[i],cl[i],nf[i]),fflush(stdout);
	for(int i=1;i<=n;i++)
		if(fail[i]!=nf[i])
			return 0;
	printf("%d\n",s);
	for(int i=1;i<=n-1;i++)
	{
		int u=e1[i].fi,v=e1[i].se;
		if(dep[u]<dep[v])
			swap(u,v);
		printf("%d ",cl[u]);
	}
	return 1;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	rd(n);
	for(int i=1,a,b;i<=n-1;i++)
	{
		rd(a),rd(b);
		t1[a].pb(b),t1[b].pb(a);
		e1[i]=pii(a,b);
	}
	for(int i=1,a,b;i<=n-1;i++)
	{
		rd(a),rd(b);
		t2[a].pb(b),t2[b].pb(a);
		e2[i]=pii(a,b);
	}
	// if(n>2000)
	// 	return solve(1),0;
	for(int i=1;i<=n;i++)
		if(solve(i))
			return 0;
	// assert(0);
	return 0;
}
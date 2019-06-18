#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,stp,ans;
vector<pii> v[400009],tmp[100009];
int f[1000009],h[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(ll>rr||l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return v[a].insert(v[a].end(),tmp[val].begin(),tmp[val].end()),void();
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
}
void init()
{
	for(int i=0;i<=100000;i++)
	{
		add(1,0,100001,0,i-1,i);
		add(1,0,100001,i+1,100001,i);
	}
}
int fnd(int x)
{
	return x==f[x]?x:fnd(f[x]);
}
void dfs(int a,int l,int r,int sm,int d)
{
	int tp=0;
	for(int i=0;i<(int)v[a].size();i++)
	{
		int fu=fnd(v[a][i].fi),fv=fnd(v[a][i].se);
		if(fu==fv)
			continue;
		sm--;
		if(h[fu]<h[fv])
			swap(fu,fv);
		bkf[d][++tp]=fv;
		bkh[d][tp]=pii(fu,h[fu]);
		f[fv]=fu;
		h[fu]=max(h[fu],h[fv]+1);
	}
	if(l==r)
	{
		if(!sm)
			return ans=l,stp=1,void();
	}
	else
	{
		int mid=(l+r)>>1;
		dfs(a<<1,l,mid,sm,d+1);
		if(stp)
			return;
		dfs(a<<1|1,mid+1,r,sm,d+1);
		if(stp)
			return;
	}
	for(int i=1;i<=tp;i++)
	{
		f[bkf[d][i]]=bkf[d][i];
		h[bkh[d][i].fi]=bkh[d][i].se;
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b),rd(c);
		if(a==b)
			continue;
		tmp[c].push_back(pii(a,b));
	}
	init();
	for(int i=1;i<=n;i++)
		f[i]=i,h[i]=1;
	dfs(1,0,100001,n-1,1);
	printf("%d",ans);
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define mod 1000000007
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,l,tot;
int w[1000009],v[2000009];
int hd[1000009],eg[1000009],nxt[1000009];
int dep[1000009],sz[1000009],son[1000009];
int f[50][1000009];
int ans[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	dep[x]=1;
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i],x);
		if(sz[eg[i]]>sz[son[x]])
			son[x]=eg[i];
		sz[x]+=sz[eg[i]];
		dep[x]=max(dep[x],dep[eg[i]]+1);
	}
}
void dfs2(int x,int d)
{
	if(son[x])
		dfs2(son[x],d);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=son[x])
		{
			memset(f[d+1],0,min(dep[eg[i]]+1,l+1)<<2);
			f[d+1][0]=1;
			dfs2(eg[i],d+1);
			for(int j=1;j<=min(dep[eg[i]],l);j++)
				f[d][j]=(f[d][j]+f[d+1][j])%mod;
		}
	f[d][l-w[x]+1]=(f[d][l-w[x]+1]+f[d][l-w[x]])%mod;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	rd(n),rd(m),rd(l);
	for(int i=2,a;i<=n;i++)
		rd(a),ins(a,i);
	for(int i=1;i<=n;i++)
		rd(w[i]);
	for(int i=1;i<=m;i++)
		rd(v[i]);
	dfs1(1,0);
	// printf("dep1:%d\n",dep[1]);
	for(int i=1;i<=m;i++)
	{
		w[(i-1)%n+1]=v[i];
		memset(f[1],0,min(dep[1]+1,l+1)<<2);
		f[1][0]=1;
		dfs2(1,1);
		ans[i]=f[1][l];
	}
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d ans:%d\n",i,ans[i]);
	int out=0;
	for(int i=1;i<=m;i++)
		out=(out+(li)i*ans[i])%mod;
	printf("%d",out);
	return 0;
}
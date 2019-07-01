//2019.07.01
//xsy1612 Problem B: 种树 首先发现每个点的父亲的编号都小于它自己,又发现是在从1到n依次修改,因此访问到一个点的时候,它到根的链上的都已经修改过
//并且它的子树内的dp值一定未修改,因此可以令f[x,i]表示x到根的路径上,构成序列1-i的方案数,g[x,i]表示x的子树内,构成序列i-n的方案数,那么经过
//x的序列的方案可以表示为f[w[x],i-1]*g[w[x],i+1],修改x的权值的时候,减去旧的贡献,加上新的贡献,考虑如何在一遍dfs内求出每个点需要求的f和g,
//首先f可以用新的权值去更新,再在回溯的时候撤销修改,但g就不能这样做,但是可以在dfs一个点之前记下g的值,回溯前再记下g的值,这样两个值相减得到的就是
//子树内g的值,然后再用旧的w[x]去更新g即可,这样就可以得到每次修改对于答案的贡献,至于初始答案,可以一遍dfs,只维护f,求出每个点为末尾的序列个数,加在一起即可
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
int hd[1000009],eg[1000009],nxt[1000009];
int w[1000009],v[2000009];
int f[1000009],g[1000009];
int pw[1000009];
int out[3000009];
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
void dfs0(int x,int &ans)
{
	if(w[x]==l)
		ans=(ans+f[l-1])%mod;
	f[w[x]]=(f[w[x]]+f[w[x]-1])%mod;
	for(int i=hd[x];i;i=nxt[i])
		dfs0(eg[i],ans);
	f[w[x]]=(f[w[x]]+mod-f[w[x]-1])%mod;
}
void dfs1(int x,int st)
{
	int bff=f[w[x]-1],aff=f[pw[x]-1];
	int bfg0=g[w[x]+1],afg0=g[pw[x]+1];
	f[pw[x]]=(f[pw[x]]+f[pw[x]-1])%mod;
	for(int i=hd[x];i;i=nxt[i])
		dfs1(eg[i],st);
	int bfg1=g[w[x]+1],afg1=g[pw[x]+1];
	if(w[x]!=l)
		bfg1=(bfg1+mod-bfg0)%mod;
	if(pw[x]!=l)
		afg1=(afg1+mod-afg0)%mod;
	// printf("x:%d bff:%d aff:%d bfg:%d afg:%d\n",x,bff,aff,bfg1,afg1);
	int ans=0;
	ans=(ans-(li)bff*bfg1%mod+mod)%mod;
	ans=(ans+(li)aff*afg1)%mod;
	out[st+x]=ans;
	f[pw[x]]=(f[pw[x]]+mod-f[pw[x]-1])%mod;
	g[w[x]]=(g[w[x]]+bfg1)%mod;
	w[x]=pw[x];
}
void solve()
{
	int tme=(m-1)/n+1;
	f[0]=1;
	dfs0(1,out[0]);
	for(int i=1;i<=tme;i++)
	{
		for(int j=1;j<=n;j++)
			pw[j]=(i-1)*n+j<=m?v[(i-1)*n+j]:w[j];
		memset(g,0,(l+1)<<2);
		g[l+1]=1;
		int st=(i-1)*n;
		dfs1(1,st);
		for(int j=1;j<=n;j++)
			out[j+st]=(out[j+st]+out[j+st-1])%mod;
	}
	// f[0]=1;
	// for(int i=1;i<=m;i++)
	// {
	// 	w[(i-1)%n+1]=v[i];
	// 	dfs0(1,out[i]);
	// }
	int ans=0;
	// for(int i=1;i<=m;i++)
	// 	printf("i:%d out:%d\n",i,out[i]);
	for(int i=1;i<=m;i++)
		ans=(ans+(li)out[i]*i)%mod;
	printf("%d",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	rd(n),rd(m),rd(l);
	for(int i=2,a;i<=n;i++)
		rd(a),ins(a,i);
	for(int i=1;i<=n;i++)
		rd(w[i]);
	for(int i=1;i<=m;i++)
		rd(v[i]);
	solve();
	return 0;
}
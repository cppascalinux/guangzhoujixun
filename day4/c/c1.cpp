//2019.06.22
//xsy1606 Problem C: 对于透过大规模仪式进行之恋爱生物间共名的实践与其粉碎方式 静态的问题可以使用分治FFT解决,考虑在一条链上怎么做,不难发现分治的过程构成了一颗线段树
//每次将区间的bi乘以ci,可以在线段树上打标记,并且标记可以合并,合并左右区间的答案时可以暴力FFT,这样不难证明单次修改的时间复杂度为O(nlogn),总时间复杂度为O(nmlogn+nlog^2n)
//树上的修改直接套一个树剖就行,每次先暴力修改,然后区间合并的时候打标记,最后dfs一遍一起合并
//单次修改时间复杂度O(nlognloglogn)(LCA说是O(nlogn))(我不会证),或者使用全局平衡二叉树,时间复杂度O(nlogn)(我不会写)
//卡常数..把FFT的取模改成加减法之后AC(本来还以为是vector的锅qwq)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pb push_back
#define li long long
#define mod 998244353
#define vi vector<int>
using namespace std;
int n,m,opt,tot,tme,len,lst;
int va[100009],vb[100009],vk[100009];
int hd[100009],eg[100009],nxt[100009];
int dep[100009],ft[100009],sz[100009],son[100009];
int dfn[100009],id[100009],top[100009];
int rt[2][270009],mp[270009];
vi f[400009];
int lz[400009],vis[400009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void dfs1(int x,int fa)
{
	ft[x]=fa;
	dep[x]=dep[fa]+1;
	sz[x]=1;
	for(int i=hd[x];i;i=nxt[i])
	{
		dfs1(eg[i],x);
		if(sz[eg[i]]>sz[son[x]])
			son[x]=eg[i];
		sz[x]+=sz[eg[i]];
	}
}
void dfs2(int x,int t)
{
	top[x]=t;
	dfn[x]=++tme,id[tme]=x;
	if(son[x])
		dfs2(son[x],t);
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=son[x])
			dfs2(eg[i],eg[i]);
}
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init(int l)
{
	int bit=0;
	while(1<<bit<l)
		bit++;
	len=1<<bit;
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,(mod-1)/len);
	for(int i=2;i<len;i++)
		rt[0][i]=(li)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
	for(int i=1;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(vi &s,int c)
{
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1,sp=len/l;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(li)s[i+j+d]*rt[c][sp*i]%mod,p=s[i+j];
				s[i+j+d]=p-t<0?p-t+mod:p-t;
				s[i+j]=p+t>=mod?p+t-mod:p+t;
			}
	}
	if(c)
	{
		int inv=qpow(len,mod-2);
		for(int i=0;i<len;i++)
			s[i]=(li)s[i]*inv%mod;
	}
}
void update(int a,int l,int r)
{
	int la=a<<1,ra=a<<1|1;
	vi sl=f[la],sr=f[ra];
	int tl=r-l+2;
	init(tl);
	sl.resize(len),sr.resize(len),f[a].resize(len);
	fft(sl,0),fft(sr,0);
	for(int i=0;i<len;i++)
		f[a][i]=(li)sl[i]*sr[i]%mod;
	fft(f[a],1);
	// f[a].resize(tl);
}
void down(int a)
{
	if(lz[a]==1)
		return;
	int la=a<<1,ra=a<<1|1,val=lz[a];
	for(int i=0,ml=1;i<(int)f[la].size();i++,ml=(li)ml*val%mod)
		f[la][i]=(li)f[la][i]*ml%mod;
	for(int i=0,ml=1;i<(int)f[ra].size();i++,ml=(li)ml*val%mod)
		f[ra][i]=(li)f[ra][i]*ml%mod;
	lz[la]=(li)lz[la]*val%mod;
	lz[ra]=(li)lz[ra]*val%mod;
	lz[a]=1;
}
void build(int a,int l,int r)
{
	lz[a]=1;
	if(l==r)
		return f[a].pb(va[id[l]]),f[a].pb(vb[id[l]]),void();
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a,l,r);
}
void mul(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		for(int i=0,ml=1;i<(int)f[a].size();i++,ml=(li)ml*val%mod)
			f[a][i]=(li)f[a][i]*ml%mod;
		lz[a]=(li)lz[a]*val%mod;
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	mul(a<<1,l,mid,ll,rr,val);
	mul(a<<1|1,mid+1,r,ll,rr,val);
	vis[a]=1;
	// update(a);
}
void dfs(int a,int l,int r)
{
	if(l==r||!vis[a])
		return;
	vis[a]=0;
	int mid=(l+r)>>1;
	down(a);
	dfs(a<<1,l,mid);
	dfs(a<<1|1,mid+1,r);
	update(a,l,r);
}
void modify(int x,int val)
{
	int fx=top[x];
	while(x)
	{
		mul(1,1,n,dfn[fx],dfn[x],val);
		x=ft[fx],fx=top[x];
	}
}
void getans()
{
	int ans=0;
	// printf("f1.size():%d\n",(int)f[1].size()),fflush(stdout);
	for(int i=0;i<=n;i++)
		ans=(ans+(li)f[1][i]*vk[i])%mod;
	printf("%d\n",lst=ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&opt);
	for(int i=1;i<=n;i++)
		scanf("%d%d",va+i,vb+i);
	for(int i=0;i<=n;i++)
		scanf("%d",vk+i);
	for(int i=2,a;i<=n;i++)
	{
		scanf("%d",&a);
		ins(a,i);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,n);
	getans();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(opt)
			a^=lst,b^=lst;
		modify(a,b);
		dfs(1,1,n);
		// for(;a;a=ft[a])
		// 	vb[a]=(li)vb[a]*b%mod;
		// build(1,1,n);
		getans();
	}
	return 0;
}
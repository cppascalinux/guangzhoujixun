//2019.06.26
//xsy1608 Problem A: 购物 令f[i,j]表示前i家商店买了j个物品的最小价值,转移f[i+1,j]=min(f[i,j],min(f[i][k]+sum[j-k])),经打表发现
//最优取值的k关于j是单调的,可以使用决策单调性分治优化dp,时间复杂度O(nklogk),然后不难发现,将所有商店按照a[0]+a[1]排序后,取前k小值,则剩余商店一定不会
//只买一件物品(如果有的话,那么前k个里一定有未访问的商店,在那个商店中买答案一定不会变差),同理,将剩下的商店按照a[0]+a[1]+a[2]排序,取前k/2小的值...
//这样一共取出klogk个商店,那么其他的商店一定都是无用的,对这klogk个商店跑决策单调性分治即可,时间复杂度O(k^2log^2k)
//分治的时候记得只去dp合法状态..不然算出来不合法区域的决策点是假的,可能导致合法区域的dp值也变成假的
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pb push_back
#define li long long
#define pli pair<li,int>
#define fi first
#define se second
#define inf 0x7F7F7F7F7F7F7F7FLL
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,smp;
vector<li> sm[2000009];
vector<int> pos[2000009];
int sz[2000009];
vector<pli> sv[2000009];
int vis[2000009],st[2000009];
li f[2][1009];
template<class T>
void rd(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void init()
{
	for(int i=1;i<=m;i++)
	{
		int sm=min(sz[i],(m-1)/i+1);
		nth_element(sv[i].begin(),sv[i].begin()+sm-1,sv[i].end());
		for(int j=0;j<sm;j++)
		{
			int x=sv[i][j].se;
			vis[x]=1;
			for(int k=1;k<(int)pos[x].size();k++)
			{
				sz[k]--;
				sv[k][pos[x][k]].fi=inf;
			}
		}
	}
	for(int i=1;i<=n;i++)
		if(vis[i])
			st[++smp]=i;
	// printf("smp:%d\n",smp);
}
void dp(int id,int cur,int lp,int rp,int lk,int rk)
{
	if(lp>rp)
		return;
	if(lk==rk)
	{
		for(int i=lp;i<=rp;i++)
		{
			int v=lk;
			v=max(v,i-(int)sm[id].size()+1);
			v=min(v,i-1);
			f[cur][i]=min(f[cur][i],f[cur^1][v]+sm[id][i-v]);
		}
		return;
	}
	int mid=(lp+rp)>>1,mk=0;
	li mn=inf;
	for(int i=max(lk,mid-(int)sm[id].size()+1);i<=min(rk,mid-1);i++)
	{
		li nsm=f[cur^1][i]+sm[id][mid-i];
		if(nsm<=mn)
			mn=nsm,mk=i;
	}
	f[cur][mid]=min(f[cur][mid],mn);
	dp(id,cur,lp,mid-1,lk,mk);
	dp(id,cur,mid+1,rp,mk,rk);
}
void solve()
{
	memset(f,0x7F,sizeof(f));
	f[0][0]=0;
	int cur=0,mxlen=0;
	for(int i=1;i<=smp;i++)
	{
		cur=i&1;
		mxlen=min(mxlen+(int)sm[st[i]].size()-1,m);
		for(int j=0;j<=m;j++)
			f[cur][j]=f[cur^1][j];
		dp(st[i],cur,1,mxlen,0,mxlen-1);
	}
	for(int i=1;i<=m;i++)
		printf("%lld ",f[cur][i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1,a;i<=n;i++)
	{
		rd(a);
		sm[i].resize(a+1);
		pos[i].resize(a+1);
		for(int j=0;j<=a;j++)
			rd(sm[i][j]);
		for(int j=1;j<=a;j++)
		{
			sm[i][j]+=sm[i][j-1];
			sv[j].pb(pli(sm[i][j],i));
			pos[i][j]=(int)sv[j].size()-1;
			sz[j]++;
		}
	}
	init();
	solve();
	return 0;
}
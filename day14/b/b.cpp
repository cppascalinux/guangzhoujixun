//2019.07.08
//xsy1617 Problem B: 货币 首先对于每一个位置i,求出他的值的下一次出现位置nxti,设fr表示r为右端点时的左端点最大值,不难发现f[r]=min{i|nxt[i]>r},同时fr单调增
//于是发现对于每一个i,fj=i对应的j构成一个区间[l,r],每次修改就是将两种颜色合并,可以启发式合并,每次修改一个点的颜色只会改变2个点的nxt值,可以使用set维护
//修改一个点的nxt值会将[l,r]分裂为若干段,最多产生1段的合并,那么至多只会分裂O(n)次,于是可以暴力在线段树上二分,找到对应的i,然后在线段树上区间修改即可
//时间复杂度O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<cassert>
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define fi first
#define se second
#define mid ((l+r)>>1)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,typ;
int pre[100009],nxt[100009],cl[100009];
int mx[400009],mn[400009],lzmn[400009];
set<int> s[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	mx[a]=max(mx[la],mx[ra]);
	mn[a]=min(mn[la],mn[ra]);
}
void down(int a,int l,int r)
{
	int la=a<<1,ra=a<<1|1;
	if(lzmn[a])
	{
		int t=lzmn[a];
		lzmn[la]=lzmn[ra]=t;
		mn[la]=l-t+1;
		mn[ra]=mid+1-t+1;
		lzmn[a]=0;
	}
}
void build(int a,int l,int r)
{
	if(l==r)
	{
		mx[a]=n+1;
		mn[a]=l;
		return;
	}
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a);
}
void setmx(int a,int l,int r,int pos,int val)
{
	if(l==r)
		return mx[a]=val,void();
	down(a,l,r);
	if(pos<=mid)
		setmx(a<<1,l,mid,pos,val);
	else
		setmx(a<<1|1,mid+1,r,pos,val);
	update(a);
}
void setmn(int a,int l,int r,int ll,int rr,int val)
{
	if(ll>rr||l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return mn[a]=l-val+1,lzmn[a]=val,void();
	down(a,l,r);
	setmn(a<<1,l,mid,ll,rr,val);
	setmn(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
int getmx(int a,int l,int r,int ll,int rr)
{
	if(ll>rr||l>rr||r<ll)
		return 0;
	if(l>=ll&&r<=rr)
		return mx[a];
	down(a,l,r);
	return max(getmx(a<<1,l,mid,ll,rr),getmx(a<<1|1,mid+1,r,ll,rr));
}
int getmn(int a,int l,int r,int ll,int rr)
{
	if(ll>rr||l>rr||r<ll)
		return inf;
	if(l>=ll&&r<=rr)
		return mn[a];
	int t0=mn[a];
	down(a,l,r);
	update(a);
	// printf("mn0:%d mn1:%d\n",t0,mn[a]);
	// assert(t0==mn[a]);
	return min(getmn(a<<1,l,mid,ll,rr),getmn(a<<1|1,mid+1,r,ll,rr));
}
int fnd(int a,int l,int r,int val)
{
	if(l==r)
		return l;
	down(a,l,r);
	int la=a<<1,ra=a<<1|1;
	if(mx[la]>val)
		return fnd(la,l,mid,val);
	return fnd(ra,mid+1,r,val);
}
void modify(int x,int nx0,int nx1)
{
	setmx(1,1,n+1,x,nx1);
	int lp=x==1?1:getmx(1,1,n+1,1,x-1);
	if(nx1>=nx0)
		return setmn(1,1,n+1,lp,nx1-1,x),void();
	// printf("x:%d lp:%d\n",x,lp);
	while(lp<=nx0-1)
	{
		int p=fnd(1,1,n+1,lp);
		setmn(1,1,n+1,lp,nxt[p]-1,p);
		lp=nxt[p];
		// printf("p:%d lp:%d\n",p,lp),fflush(stdout);
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d| nxt:%d\n",i,nxt[i]),fflush(stdout);
}
void mrg(int a,int b)
{
	if(s[a].size()<s[b].size())
		swap(a,b);
	for(int i:s[b])
	{
		cl[i]=a;
		auto it1=s[a].insert(i).fi;
		auto it2=it1;
		if(++it2!=s[a].end())
		{
			pre[*it2]=i;
			int t=nxt[i];
			// printf("i:%d it2:%d\n",i,*it2),fflush(stdout);
			// for(int i=1;i<=n;i++)
			// 	printf("i:%d| nxt:%d\n",i,nxt[i]),fflush(stdout);
			modify(i,t,nxt[i]=*it2);
		}
		if(it1!=s[a].begin())
		{
			it1--;
			pre[i]=*it1;
			int t=nxt[*it1];
			// printf("it1:%d i:%d\n",*it1,i),fflush(stdout);
			// for(int i=1;i<=n;i++)
			// 	printf("i:%d| nxt:%d\n",i,nxt[i]),fflush(stdout);
			modify(*it1,t,nxt[*it1]=i);
		}
	}
	s[b].clear();
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	rd(n),rd(m),rd(typ);
	for(int i=1;i<=n;i++)
		cl[i]=i,pre[i]=0,nxt[i]=n+1,s[i].insert(i);
	build(1,1,n+1);
	int lans=0,avr=n;
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		a=(a-1+typ*lans)%n+1,b=(b-1+typ*lans)%n+1;
		a=cl[a],b=cl[b];
		if(a!=b)
			mrg(a,b);
		while(avr>1&&pre[avr])
			avr--;
		// printf("i:%d avr:%d-------------------------------\n",i,avr);
		// for(int j=1;j<=n;j++)
		// 	printf("i:%d| pre:%d| nxt:%d| mx:%d| mn:%d\n",j,pre[j],nxt[j],getmx(1,1,n+1,j,j),getmn(1,1,n+1,j,j));
		printf("%d\n",lans=getmn(1,1,n+1,avr,n));
	}
	return 0;
}
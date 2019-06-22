//2019.06.22
//xsy1606 Problem B: 革命性宣传计划之始末与阶级性愤怒 一个区间合法当且仅当将左括号视为2,右括号视为-1时每个前缀的和>=0,右括号同理
//预处理每个左括号能到达的最靠右的右括号以及每个右端点能到达的最靠左的左括号的位置,可以使用前缀和+单调栈
//扫描线,用线段树维护答案,sa表示i作为左端点的总答案,sb表示区间合法的左端点的数量,lz表示区间加的懒标记
//感觉和joisc2019 两根天线 有点相似..
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
#define pb push_back
using namespace std;
int n,m;
char s[300009];
int pf[300009];
int rm[300009],lm[300009];
pii st[300009];
int sb[1200009],lz[1200009];
li sa[1200009];
vector<int> ed[300009];
vector<pii> qry[300009];
li ans[300009];
void init()
{
	for(int i=1;i<=n;i++)
		pf[i]=pf[i-1]+(s[i]=='('?2:-1);
	int tp=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]==')')
		{
			while(tp&&pf[i]<st[tp].se)
				rm[st[tp--].fi]=i-1;
		}
		else
			st[++tp]=pii(i,pf[i-1]);
	}
	while(tp)
		rm[st[tp--].fi]=n;
	for(int i=n;i>=1;i--)
		pf[i]=pf[i+1]+(s[i]==')'?2:-1);
	for(int i=n;i>=1;i--)
	{
		if(s[i]=='(')
		{
			while(tp&&pf[i]<st[tp].se)
				lm[st[tp--].fi]=i+1;
		}
		else
			st[++tp]=pii(i,pf[i+1]);
	}
	while(tp)
		lm[st[tp--].fi]=1;
	// for(int i=1;i<=n;i++)
	// 	printf("lm:%d rm:%d\n",lm[i],rm[i]);
}
void added()
{
	for(int i=1;i<=n;i++)
		if(s[i]=='(')
			ed[rm[i]+1].pb(i);
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1,t=lz[a];
	sa[la]+=(li)t*sb[la],sa[ra]+=(li)t*sb[ra];
	lz[la]+=t,lz[ra]+=t;
	lz[a]=0;
}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	sa[a]=sa[la]+sa[ra];
	sb[a]=sb[la]+sb[ra];
}
void build(int a,int l,int r)
{
	if(l==r)
		return sb[a]=(s[l]=='('),void();
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a);
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return sa[a]+=sb[a]*val,lz[a]+=val,void();
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	update(a);
}
void sett(int a,int l,int r,int pos,int val)
{
	if(l==r)
		return sb[a]=val,void();
	down(a);
	int mid=(l+r)>>1;
	if(pos<=mid)
		sett(a<<1,l,mid,pos,val);
	else
		sett(a<<1|1,mid+1,r,pos,val);
	update(a);
}
li ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		return 0;
	if(l>=ll&&r<=rr)
		return sa[a];
	down(a);
	int mid=(l+r)>>1;
	return ask(a<<1,l,mid,ll,rr)+ask(a<<1|1,mid+1,r,ll,rr);
}
void solve()
{
	build(1,1,n);
	// printf("sb:%d\n",sb[1]);
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)ed[i].size();j++)
			sett(1,1,n,ed[i][j],0);
		if(s[i]==')')
			add(1,1,n,lm[i],i,1);
		for(int j=0;j<(int)qry[i].size();j++)
			ans[qry[i][j].se]=ask(1,1,n,qry[i][j].fi,i);
	}
	// printf("sa:%lld\n",sa[1]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	scanf("%s",s+1);
	init();
	added();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		qry[b].pb(pii(a,i));
	}
	solve();
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
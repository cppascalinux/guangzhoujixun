//2019.06.23
//xsy1607 Problem B 考虑暴力如何做:将区间中的元素都拿出来,从后向前扫,遇到后缀和<0的,就将那个位置的元素删除,答案++,然后在从前向后扫,答案加上前缀和的最小值
//考虑一下这样做的正确性:只考虑后缀的话,一定会删除(后缀和的min的绝对值)个元素,而这样贪心可以保证每一个删除的位置都是尽量靠前的,对于前缀的限制的贡献是最大的
//考虑一下用线段树维护:先把所有询问按右端点从大到小排序,用线段树维护区间前缀和的最小值,再用一个栈维护所有<0的位置,每次rp+1,若rp为-1,则加入栈中,否则弹出栈顶
//(若栈为空则不用操作),对栈操作的同时在线段树上区间+1/-1,询问就是查询区间最小值,减去l-1的前缀和,加上栈的大小之类的东西
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#define inf 0x7F7F7F7F
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
int n,m;
char s[500009];
vector<pii> q[500009];
int ans[500009];
int st[500009],sm[500009];
int mn[2000009],lz[2000009];
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	lz[la]+=lz[a],lz[ra]+=lz[a];
	mn[la]+=lz[a],mn[ra]+=lz[a];
	lz[a]=0;
}
void add(int a,int l,int r,int ll,int rr,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return lz[a]+=val,mn[a]+=val,void();
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,val);
	add(a<<1|1,mid+1,r,ll,rr,val);
	mn[a]=min(mn[a<<1],mn[a<<1|1]);
}
int ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		return inf;
	if(l>=ll&&r<=rr)
		return mn[a];
	down(a);
	int mid=(l+r)>>1;
	return min(ask(a<<1,l,mid,ll,rr),ask(a<<1|1,mid+1,r,ll,rr));
}
void solve()
{
	for(int i=1;i<=n;i++)
	{
		sm[i]=sm[i-1]+s[i];
		add(1,0,n,i,i,sm[i]);
	}
	int tp=0;
	for(int i=1;i<=n;i++)
	{
		if(s[i]==1&&tp)
			add(1,0,n,st[tp--],n,-1);
		else if(s[i]==-1)
			add(1,0,n,st[++tp]=i,n,1);
		// printf("i:%d tp:%d\n",i,tp);
		for(int j=0;j<(int)q[i].size();j++)
			ans[q[i][j].se]=(tp-(lower_bound(st+1,st+tp+1,q[i][j].fi)-st)+1)+abs(min(0,ask(1,0,n,q[i][j].fi,i)-ask(1,0,n,q[i][j].fi-1,q[i][j].fi-1)));
	}
	for(int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]=(s[i]=='C'?1:-1);
	scanf("%d",&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		q[b].pb(pii(a,i));
	}
	solve();
	return 0;
}
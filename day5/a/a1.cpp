//2019.06.22
//xsy1607 Problem A 考虑每次选的个数+1,一定是将某一个类似于01010的连续段的颜色翻转,用set维护所有连续段,用并查集维护左右端点即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#define li long long
using namespace std;
struct node
{
	int l,r;
	li val;
	node(){}
	node(int a,int b,li c){l=a,r=b,val=c;}
	bool operator <(const node &p) const
	{
		return val==p.val?l<p.l:val>p.val;
	}
};
int n,m;
int v[200009];
li sm0[200009],sm1[200009];
int fl[200009],fr[200009];
li ans[200009];
int fndl(int x)
{
	return x==fl[x]?x:fl[x]=fndl(fl[x]);
}
int fndr(int x)
{
	return x==fr[x]?x:fr[x]=fndr(fr[x]);
}
void solve()
{
	set<node> s;
	for(int i=1;i<=n;i++)
	{
		fl[i]=fr[i]=i;
		s.insert(node(i,i,v[i]));
	}
	int mx=(n+1)/2;
	for(int i=1;i<=mx;i++)
	{
		// printf("i:%d \n",i);
		node t=*s.begin();
		s.erase(*s.begin());
		ans[i]=ans[i-1]+t.val;
		int lm=fndl(t.l-1),rm=fndr(t.r+1);
		li nt=-t.val;
		if(lm)
			fr[t.l-1]=rm;
		if(rm)
			fl[t.r+1]=lm;
		fl[t.l]=lm,fr[t.r]=rm;
		if(lm)
		{
			li v0=sm0[t.l-1]-sm0[lm-1],v1=sm1[t.l-1]-sm1[lm-1];
			if(lm&1)
				swap(v0,v1);
			s.erase(node(lm,t.l-1,v0-v1));
			nt+=v0-v1;
		}
		if(rm)
		{
			li v0=sm0[rm]-sm0[t.r],v1=sm1[rm]-sm1[t.r];
			if(rm&1)
				swap(v0,v1);
			s.erase(node(t.r+1,rm,v0-v1));
			nt+=v0-v1;
		}
		// printf("nt:%lld\n",nt);
		if(lm&&rm)
			s.insert(node(lm,rm,nt));
		// for(int j=1;j<=n;j++)
		// 	printf("j:%d lm:%d rm:%d\n",j,fndl(j),fndr(j));
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i);
	for(int i=1;i<=n;i++)
	{
		sm0[i]=sm0[i-1],sm1[i]=sm1[i-1];
		if(i&1)
			sm1[i]+=v[i];
		else
			sm0[i]+=v[i];
	}
	solve();
	scanf("%d",&m);
	for(int i=1,a;i<=m;i++)
	{
		scanf("%d",&a);
		printf("%lld\n",ans[a]);
	}
	return 0;
}
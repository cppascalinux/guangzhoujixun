//2019.06.29
//xsy1611 Problem A: 购物 首先这个强制在线是假的,可以直接确定每个物品的存活时间区间,放到线段树上,然后按先序遍历确定每一个叶子的答案,
//当第一次访问到一个物品时,就把他的w和v xor lastans,处理询问之前将l和r xor lastans, 总时间复杂度O(nmlogn),但跑的比正解还快
//正解:考虑一种类似于定期重构的算法:设置一个位置x,对于[lp,x]中的每一个i,都维护一个[i,x]的背包,对于(x,rp]再维护一个背包
//每次加入一个物品,则直接在右边的背包中插入,删除一个物品,若lp<=x,则直接扔掉左边的一个背包,否则将x设为r,扔掉右边的背包,并暴力重新计算左侧的背包
//这样每个物品只会被在左侧和右侧分别添加一次,时间复杂度均摊O(nm),处理询问的时候用单调队列求出[l,r]的max即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define li long long
#define mod 1000000007
#define pil pair<int,li>
#define fi first
#define se second
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,typ,lst,lp=1,rp=0,cur=0;
int w[100009],v[100009];
li fl[100009][509],fr[509],h[509];
pil que[1009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void addr(int id)
{
	int tw=w[id],tv=v[id];
	memcpy(h,fr,sizeof(h));
	for(int j=0;j<m;j++)
	{
		int np=j+tw>=m?j+tw-m:j+tw;
		fr[np]=max(h[np],h[j]+tv);
	}
}
void rebuild()
{
	memset(fr,0xC0,sizeof(fr));
	fr[0]=0;
	memcpy(fl[rp+1],fr,sizeof(fr));
	cur=rp;
	for(int i=rp;i>=lp;i--)
	{
		int tw=w[i],tv=v[i];
		li *fl1=fl[i],*fl0=fl[i+1];
		for(int j=0;j<m;j++)
		{
			int np=j+tw>=m?j+tw-m:j+tw;
			fl1[np]=max(fl0[np],fl0[j]+tv);
		}
	}
}
li getans(li *fl,li *fr,int l,int r)
{
	int ft=1,bk=0;
	int cl=l,cr=r;
	li ans=-1;
	for(int i=l+1;i<=r;i++)
	{
		while(bk>=ft&&fr[i]>=que[bk].se)
			bk--;
		que[++bk]=pil(i,fr[i]);
	}
	for(int i=m-1;i>=0;i--)
	{
		cr++,cl++;
		int np=cr>=m?cr-m:cr;
		while(bk>=ft&&fr[np]>=que[bk].se)
			bk--;
		while(bk>=ft&&que[ft].fi<cl)
			ft++;
		que[++bk]=pil(cr,fr[np]);
		ans=max(ans,que[ft].se+fl[i]);
	}
	return ans;
}
void solve()
{
	memset(fr,0xC0,sizeof(fr));
	fr[0]=0;
	memcpy(fl[1],fr,sizeof(fr));
	for(int i=1,a,b,c,d,e;i<=n;i++)
	{
		rd(a),rd(b),rd(c);
		// assert(lst==0);
		b^=lst,c^=lst;
		if(a==1)
		{
			rd(d),rd(e);
			d^=lst,e^=lst;
			rp++;
			w[rp]=b,v[rp]=c;
			addr(rp);
			li ans=getans(fl[lp],fr,d,e);
			if(ans>=0&&typ)
				lst=ans%mod;
			printf("%lld\n",ans);
		}
		else
		{
			lp++;
			if(lp>cur)
				rebuild();
			li ans=getans(fl[lp],fr,b,c);
			if(ans>=0&&typ)
				lst=ans%mod;
			printf("%lld\n",ans);
		}
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	rd(n),rd(m),rd(typ);
	solve();
	return 0;
}
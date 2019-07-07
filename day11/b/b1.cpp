//2019.07.06
//xsy1613 Problem B: Inserting Lines 最开始以为行和列是相互独立的,然后可以用两个平衡树分别维护行和列;但实际上只有当询问的点是原来就有的点时才是对的,对于新插入的点
//无法确定是行插入的还是列插入的.考虑将询问分为三种情况:原来就有的点,行插入的点和列插入的点,发现后插入的行/列会对之前插入的行/列的位置产生影响,于是考虑用一棵线段树去
//维护操作序列,每个点维护区间内的所有行/列,区间合并的时候,暴力归并,同时算上右儿子对左儿子的影响(只有当左右区间都满的时候才会去合并),查询的时候,在线段树上二分去找
//最晚加入的,包含查询位置的行/列,使用了一种特殊的二分技巧:自底向上,再自顶向下,在线段树的每一个节点上二分查找,如果找到了,就继续向儿子二分;否则把询问的行/列减去
//线段树节点内在他之前的行/列的个数,继续向前二分(类似于zkw线段树),如果一直到头都找不到,那说明是原来就有的点 时间复杂度O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,bit=17;
int ful[270009];
vector<int> v[2][270009];
void mrg(int a)
{
	int la=a<<1,ra=a<<1|1;
	if(ful[la]&&ful[ra]&&!ful[a])
	{
		ful[a]=1;
		for(int k=0;k<=1;k++)
		{
			vector<int> &va=v[k][a],&vl=v[k][la],&vr=v[k][ra];
			int lp=0,rp=0,adl=0,szl=vl.size(),szr=vr.size();
			while(lp<szl&&rp<szr)
			{
				if(vl[lp]+adl<vr[rp])
					va.pb(vl[lp++]+adl);
				else
					adl++,va.pb(vr[rp++]);
			}
			while(lp<szl)
				va.pb(vl[lp++]+adl);
			while(rp<szr)
				va.pb(vr[rp++]);
		}
	}
}
void add(int pos,int typ,int val)
{
	int p=pos+(1<<bit)-1;
	ful[p]=1;
	if(typ!=-1)
		v[typ][p].pb(val);
	for(p>>=1;p;p>>=1)
		mrg(p);
}
pii ask(int pos,int qx,int qy)
{
	int p;
	for(p=pos+(1<<bit);p;p>>=1)
		if(p&1)
		{
			int a=p^1;
			vector<int> &v0=v[0][a],&v1=v[1][a];
			int pos0=lower_bound(v0.begin(),v0.end(),qx)-v0.begin();
			int pos1=lower_bound(v1.begin(),v1.end(),qy)-v1.begin();
			int n0=(pos0<(int)v0.size()&&v0[pos0]==qx);
			int n1=(pos1<(int)v1.size()&&v1[pos1]==qy);
			if(n0||n1)
				break;
			qx-=pos0,qy-=pos1;
		}
	if(!p)
		return pii(qx,qy);
	int a;
	for(a=p^1;a<1<<bit;)
	{
		int la=a<<1,ra=a<<1|1;
		vector<int> &v0=v[0][ra],&v1=v[1][ra];
		int pos0=lower_bound(v0.begin(),v0.end(),qx)-v0.begin();
		int pos1=lower_bound(v1.begin(),v1.end(),qy)-v1.begin();
		int n0=(pos0<(int)v0.size()&&v0[pos0]==qx);
		int n1=(pos1<(int)v1.size()&&v1[pos1]==qy);
		if(n0||n1)
			a=ra;
		else
			qx-=pos0,qy-=pos1,a=la;
	}
	vector<int> &v0=v[0][a],&v1=v[1][a];
	int pos0=lower_bound(v0.begin(),v0.end(),qx)-v0.begin();
	int pos1=lower_bound(v1.begin(),v1.end(),qy)-v1.begin();
	int n0=(pos0<(int)v0.size()&&v0[pos0]==qx);
	int n1=(pos1<(int)v1.size()&&v1[pos1]==qy);
	int pa=a-(1<<bit)+1;
	// assert(n0||n1);
	if(n0)
		return pii(pa,qy);
	else
		return pii(qx,pa);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	int lp=0,lq=0;
	for(int i=1,a,b,c;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		b+=lp+lq;
		if(a==2)
			add(i,0,b);
		else if(a==1)
			add(i,1,b);
		else
		{
			scanf("%d",&c);
			c+=lp-lq;
			add(i,-1,0);
			pii t=ask(i,b,c);
			printf("%d %d\n",lp=t.fi,lq=t.se);
		}
	}
	return 0;
}
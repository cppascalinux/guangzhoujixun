//2019.07.05
//xsy1614 Problem C: 比赛 首先不难推出至多只有一个人会发动技能,然后又发现发动技能的人一定满足i=ai,那么考虑每个人发动技能后是否必胜,发现当且仅当他发动技能后
//x为i,且后面的每一个人都无法通过发动技能使自己获胜,于是令fi表示当x为i-xi时,i发动技能是否必胜,发现fi=1,当且仅当所有j-aj=i的fj都=0,发现转移构成了一课树
//i向i-ai连边,于是每次可以暴力树形dp,时间复杂度O(n^2),然后带修改就意味着一个点要换父亲,考虑link/cut的时候怎么做,就是要把当前点到根路径的一个前缀的dp值翻转
//首先access这个点,然后不难发现需要翻转的点的虚儿子的dp值一定都为0,于是可以在access的时候去更新每个点的虚儿子的dp值的和,然后修改的时候在splay上二分
//找到要修改的部分,然后子树打标记即可,询问时,若根的dp值为1,则直接输出根,否则用一个set去维护所有深度为1的,dp值也为1的点,找到set中的最小元素即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#include<cassert>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define nrt(x) (x==lc(f[x])||x==rc(f[x]))
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int s[300009],ft[300009];
int f[300009],ch[300009][2],v[300009],vtp[300009],sm[300009],si[300009];
int sz[300009],lz[300009],st[300009];
set<int> d1;
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void down(int x)
{
	if(lz[x])
	{
		lz[lc(x)]^=1,lz[rc(x)]^=1;
		v[lc(x)]^=1,v[rc(x)]^=1;
		vtp[lc(x)]^=1,vtp[rc(x)]^=1;
		lz[x]=0;
	}
}
void update(int x)
{
	down(x);
	sm[x]=sm[lc(x)]+sm[rc(x)]+(si[x]==0);
	sz[x]=sz[lc(x)]+sz[rc(x)]+1;
	vtp[x]=lc(x)?vtp[lc(x)]:v[x];
}
void rotate(int x)
{
	int y=f[x],z=f[y],dx=x==rc(y),dy=y==rc(z);
	if(nrt(y))
		ch[z][dy]=x;
	f[x]=z;
	f[y]=x;
	f[ch[x][dx^1]]=y;
	ch[y][dx]=ch[x][dx^1];
	ch[x][dx^1]=y;
	update(y);
	update(x);
}
void splay(int x)
{
	int y,z,tp=0;
	for(y=x;nrt(y);y=f[y])
		st[++tp]=y;
	st[++tp]=y;
	for(;tp>=1;tp--)
		down(st[tp]);
	while(nrt(x))
	{
		y=f[x],z=f[y];
		int dx=x==rc(y),dy=y==rc(z);
		if(nrt(y))
			rotate(dx!=dy?x:y);
		rotate(x);
	}
}
void access(int x)
{
	// printf("x:%d\n",x);
	for(int y=0;x;y=x,x=f[x])
	{
		splay(x);
		down(x);
		if(rc(x))
		{
			// down(rc(x));
			// update(rc(x));
			// printf("rc:%d vtp:%d lcrc:%d\n",rc(x),vtp[rc(x)],lc(rc(x)));
			si[x]+=vtp[rc(x)];
		}
		if(y)
			si[x]-=vtp[y];
		rc(x)=y;
		update(x);
	}
}
void modify(int x)
{
	// printf("x:%d sz:%d sm:%d si:%d f:%d\n",x,sz[x],sm[x],si[x],f[x]);
	if(sm[x]==sz[x])
		v[x]^=1,vtp[x]^=1,lz[x]^=1;
	else
	{
		int p=x;
		while(p)
		{
			down(p);
			if(sm[rc(p)]!=sz[rc(p)])
				p=rc(p);
			else if(si[p])
				break;
			else
				p=lc(p);
		}
		splay(p);
		// printf("p:%d rcp:%d lc:%d\n",p,rc(p),lc(p));
		if(rc(p))
			v[rc(p)]^=1,vtp[rc(p)]^=1,lz[rc(p)]^=1;
	}
}
void recal(int y,int typ)
{
	// assert(y);
	splay(1);
	if(sz[1]==1)
	{
		if(!typ)
			d1.erase(y);
		else if(v[y]&&f[y]==1)
			d1.insert(y);
	}
	else
	{
		down(1);
		int p=ch[1][1];
		while(ch[p][0])
			down(p),p=ch[p][0];
		if(v[p])
			d1.insert(p);
		else
			d1.erase(p);
		splay(p);
	}
}
void cut(int x,int y)//y is son of x
{
	// printf("x:%d y:%d\n",x,y);
	// printf("cut\n"),fflush(stdout);
	access(x);
	splay(x);
	splay(y);
	f[y]=0;
	// printf("six:%d\n",si[x]);
	si[x]-=vtp[y];
	// printf("six:%d\n",si[x]);
	update(x);
	if(vtp[y])
		modify(x);
	recal(y,0);
}
void lnk(int x,int y)//link y to son of x
{
	// printf("link\n"),fflush(stdout);
	access(x);
	splay(x);
	splay(y);
	if(vtp[y])
		/* printf("x:%d y:%d\n",x,y), */modify(x);
	f[y]=x;
	si[x]+=vtp[y];
	update(x);
	recal(y,1);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		sz[i]=v[i]=sm[i]=vtp[i]=1;
	for(int i=1;i<=n;i++)
	{
		rd(s[i]);
		if(i>=s[i]+1&&s[i])
			ft[i]=i-s[i],lnk(ft[i],i);
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	access(i);
	// 	splay(i);
	// 	printf("i:%d ft:%d v:%d vtp:%d si:%d sm:%d\n",i,ft[i],v[i],vtp[i],si[i],sm[i]);
	// }
	// access(2);
	// printf("si2:%d\n",si[2]);
	splay(1);
	if(v[1])
		printf("%d\n",0);
	else
		printf("%d\n",*d1.begin()-1);
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		a++;
		if(ft[a])
			cut(ft[a],a);
		s[a]=b;
		ft[a]=0;
		if(a>=s[a]+1&&s[a])
			ft[a]=a-s[a],lnk(ft[a],a);
		splay(1);
		if(v[1])
			printf("%d\n",0);
		else
			printf("%d\n",*d1.begin()-1);
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	splay(i);
	// 	printf("i:%d ft:%d v:%d si:%d\n",i,ft[i],v[i],si[i]);
	// }
	return 0;
}
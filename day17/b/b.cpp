//2019.07.14
//xsy1619 Problem B: TarjanLusa 令x表示毒的总层数,y表示毒雾的层数,z表示总伤害,那么每一个区间都是对于x,y,z的线性变换,可以使用线段树去维护矩阵乘,就有50pts
//不难发现,区间修改a,c只会对线性变换的常数项产生影响,因此可以记录a,c区间加的贡献系数,然后打上懒标记即可,(区间合并的时候非常麻烦,因为本质就是把矩阵乘法拆开来写)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define li long long
#define mod 1000000007
using namespace std;
struct node
{
	int x1,x2,x3,x4,x5;
	int y1,y2;
	int z1,z2,z3,z4,z5;
};
char *p1,*p2,buffer[10000009];
int n,m;
int va[100009],vb[100009],vc[100009];
node v[400009];
int ta[400009],tc[400009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
node mrg(node la,node ra)
{
	node ans;
	ans.x1=(li)la.x1*ra.x1%mod;
	ans.x2=((li)la.x2*ra.x1+ra.x2)%mod;
	ans.x3=((li)la.x3*ra.x1+ra.x3+(li)la.y1*ra.x2)%mod;
	ans.x4=((li)la.x4*ra.x1+ra.x4)%mod;
	ans.x5=((li)la.x5*ra.x1+ra.x5+(li)la.y2*ra.x2)%mod;
	ans.y1=(la.y1+ra.y1)%mod;
	ans.y2=(la.y2+ra.y2)%mod;
	ans.z1=(la.z1+(li)ra.z1*la.x1)%mod;
	ans.z2=(la.z2+(li)ra.z1*la.x2+ra.z2)%mod;
	ans.z3=(la.z3+ra.z3+(li)ra.z1*la.x3+(li)ra.z2*la.y1)%mod;
	ans.z4=(la.z4+(li)ra.z1*la.x4+ra.z4)%mod;
	ans.z5=(la.z5+(li)ra.z1*la.x5+ra.z5+(li)ra.z2*la.y2)%mod;
	return ans;
}
void pusha(int a,int val)
{
	ta[a]=(ta[a]+val)%mod;
	v[a].x3=(v[a].x3+(li)val*v[a].x4)%mod;
	v[a].z3=(v[a].z3+(li)val*v[a].z4)%mod;
}
void pushc(int a,int val)
{
	tc[a]=(tc[a]+val)%mod;
	v[a].x3=(v[a].x3+(li)val*v[a].x5)%mod;
	v[a].y1=(v[a].y1+(li)val*v[a].y2)%mod;
	v[a].z3=(v[a].z3+(li)val*v[a].z5)%mod;
}
void down(int a)
{
	int la=a<<1,ra=a<<1|1;
	if(ta[a])
	{
		pusha(la,ta[a]);
		pusha(ra,ta[a]);
		ta[a]=0;
	}
	if(tc[a])
	{
		pushc(la,tc[a]);
		pushc(ra,tc[a]);
		tc[a]=0;
	}
}
void build(int a,int l,int r)
{
	if(l==r)
	{
		v[a].x1=vb[l];
		v[a].x2=vb[l];
		v[a].x3=((li)va[l]*vb[l]-1)%mod;
		v[a].x4=vb[l];
		v[a].x5=0;
		v[a].y1=vc[l];
		v[a].y2=1;
		v[a].z1=vb[l];
		v[a].z2=vb[l];
		v[a].z3=(li)va[l]*vb[l]%mod;
		v[a].z4=vb[l];
		v[a].z5=0;
		return;
	}
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	v[a]=mrg(v[a<<1],v[a<<1|1]);
}
void add(int a,int l,int r,int ll,int rr,int typ,int val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
	{
		if(typ==1)
			pusha(a,val);
		else
			pushc(a,val);
		return;
	}
	down(a);
	int mid=(l+r)>>1;
	add(a<<1,l,mid,ll,rr,typ,val);
	add(a<<1|1,mid+1,r,ll,rr,typ,val);
	v[a]=mrg(v[a<<1],v[a<<1|1]);
}
node ask(int a,int l,int r,int ll,int rr)
{
	if(l>rr||r<ll)
		assert(0);
	if(l>=ll&&r<=rr)
		return v[a];
	down(a);
	int mid=(l+r)>>1;
	if(rr<=mid)
		return ask(a<<1,l,mid,ll,rr);
	if(ll>=mid+1)
		return ask(a<<1|1,mid+1,r,ll,rr);
	return mrg(ask(a<<1,l,mid,ll,rr),ask(a<<1|1,mid+1,r,ll,rr));
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(va[i]),rd(vb[i]),rd(vc[i]);
	build(1,1,n);
	for(int i=1,typ,l,r,t,c;i<=m;i++)
	{
		rd(typ),rd(l),rd(r);
		if(typ==1)
			printf("%d\n",ask(1,1,n,l,r).x3);
		else if(typ==2)
			printf("%d\n",ask(1,1,n,l,r).z3);
		else
		{
			rd(t),rd(c);
			add(1,1,n,l,r,t,c);
		}
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define li long long
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m,va,vb;
int s[200009];
li sm[800009],mx[800009],mn[800009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
	// scanf("%d",&x);

}
void update(int a)
{
	int la=a<<1,ra=a<<1|1;
	sm[a]=sm[la]+sm[ra];
	mx[a]=max(mx[la],mx[ra]+sm[la]);
	mn[a]=min(mn[la],mn[ra]+sm[la]);
}
void build(int a,int l,int r)
{
	if(l==r)
	{
		sm[a]=s[l];
		mx[a]=max(0,s[l]);
		mn[a]=min(0,s[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	update(a);
}
void setv(int a,int l,int r,int pos,int val)
{
	if(l==r)
	{
		sm[a]=val;
		mx[a]=max(0,val);
		mn[a]=min(0,val);
		return;
	}
	int mid=(l+r)>>1;
	if(pos<=mid)
		setv(a<<1,l,mid,pos,val);
	else
		setv(a<<1|1,mid+1,r,pos,val);
	update(a);
}
li ask(int a,int l,int r,int mxv,int curv)
{
	if(l==r)
	{
		li nv=curv+sm[a];
		nv=min(nv,(li)mxv),nv=max(nv,0LL);
		return nv;
	}
	int la=a<<1,ra=a<<1|1,mid=(l+r)>>1;
	if(mx[ra]-mn[ra]>=mxv)
		return ask(ra,mid+1,r,mxv,curv);
	li lv=ask(la,l,mid,mxv,curv);
	if(lv+mx[ra]>=mxv)
		return mxv-(mx[ra]-sm[ra]);
	if(lv+mn[ra]<=0)
		return sm[ra]-mn[ra];
	return lv+sm[ra];
}
void dfs(int a,int l,int r)
{
	printf("l:%d r:%d sm:%lld mx:%lld mn:%lld\n",l,r,sm[a],mx[a],mn[a]);
	if(l<r)
	{
		int mid=(l+r)>>1;
		dfs(a<<1,l,mid);
		dfs(a<<1|1,mid+1,r);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	rd(n),rd(va),rd(vb);
	for(int i=1;i<=n;i++)
	{
		rd(s[i]);
		if(!(i&1))
			s[i]=-s[i];
		// printf("i:%d si:%d\n",i,s[i]);
	}
	build(1,1,n);
	// dfs(1,1,n);
	rd(m);
	for(int i=1,a,b,c;i<=m;i++)
	{
		rd(a),rd(b);
		if(a==1)
			va=b;
		else if(a==2)
			vb=b;
		else
		{
			rd(c);
			if(b&1)
				s[b]=c;
			else
				s[b]=-c;
			setv(1,1,n,b,s[b]);
		}
		// printf("i:%d===========================================\n",i);
		// dfs(1,1,n);
		printf("%lld\n",ask(1,1,n,va+vb,va));
	}
	return 0;
}
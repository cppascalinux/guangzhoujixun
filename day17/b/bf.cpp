#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define li long long
#define mod 1000000007
using namespace std;
struct mat
{
	int v[4][4];
	mat(){memset(v,0,sizeof(v));}
	mat(int s[16]){for(int i=0;i<4;i++) for(int j=0;j<4;j++) v[i][j]=s[i*4+j];}
	mat operator *(mat p)
	{
		mat ans;
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				ans.v[i][j]=((li)v[i][0]*p.v[0][j]+(li)v[i][1]*p.v[1][j]+(li)v[i][2]*p.v[2][j]+(li)v[i][3]*p.v[3][j])%mod;
		return ans;
	}
	void output()
	{
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
				printf("%d ",v[i][j]);
			printf("\n");
		}
	}
};
char *p1,*p2,buffer[10000009];
int n,m;
int va[100009],vb[100009],vc[100009];
mat sm[400009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void build(int a,int l,int r)
{
	if(l==r)
	{
		int s[16]={vb[l],vb[l],0,(int)(((li)va[l]*vb[l]-1)%mod),0,1,0,vc[l],
					vb[l],vb[l],1,(int)((li)va[l]*vb[l]%mod),0,0,0,1};
		sm[a]=mat(s);
		return;
	}
	int mid=(l+r)>>1;
	build(a<<1,l,mid);
	build(a<<1|1,mid+1,r);
	sm[a]=sm[a<<1|1]*sm[a<<1];
}
void ask(int a,int l,int r,int ll,int rr,mat &ans)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return ans=ans*sm[a],void();
	int mid=(l+r)>>1;
	ask(a<<1|1,mid+1,r,ll,rr,ans);
	ask(a<<1,l,mid,ll,rr,ans);
}
void setv(int a,int l,int r,int pos,mat v)
{
	if(l==r)
		return sm[a]=v,void();
	int mid=(l+r)>>1;
	if(pos<=mid)
		setv(a<<1,l,mid,pos,v);
	else
		setv(a<<1|1,mid+1,r,pos,v);
	sm[a]=sm[a<<1|1]*sm[a<<1];
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		rd(va[i]),rd(vb[i]),rd(vc[i]);
	build(1,1,n);
	for(int i=1,typ,l,r,t,v;i<=m;i++)
	{
		rd(typ),rd(l),rd(r);
		if(typ==1)
		{
			int s[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
			mat ans(s);
			ask(1,1,n,l,r,ans);/*
			for(int j=r;j>=l;j--)
			{
				int s[16]={vb[j],vb[j],0,(int)(((li)va[j]*vb[j]-1)%mod),0,1,0,vc[j],
						vb[j],vb[j],1,(int)((li)va[j]*vb[j]%mod),0,0,0,1};
				ans=ans*mat(s);
				ans.output();
				printf("\n");
			}*/
			printf("%d\n",ans.v[0][3]);
		}
		else if(typ==2)
		{
			int s[16]={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
			mat ans(s);
			ask(1,1,n,l,r,ans);
		//  ans.output();
			printf("%d\n",ans.v[2][3]);
		}
		else
		{
			rd(t),rd(v);
			for(int j=l;j<=r;j++)
			{
				if(t==1)
					va[j]=(va[j]+v)%mod;
				else
					vc[j]=(vc[j]+v)%mod;
				int s[16]={vb[j],vb[j],0,(int)(((li)va[j]*vb[j]-1)%mod),0,1,0,vc[j],
						vb[j],vb[j],1,(int)((li)va[j]*vb[j]%mod),0,0,0,1};
				mat nxt(s);
			//  nxt.output();
				setv(1,1,n,j,nxt);
			}
		}
	}
	return 0;
}
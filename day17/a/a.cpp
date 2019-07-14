#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define mod 1000000007
#define li long long
using namespace std;
int ca,cb;
int pa[7][7]={{},
{0,1,2,3,4,5,6},
{0,1,6,2,4,3,5},
{0,1,5,6,4,2,3},
{0,1,3,5,4,6,2},
{0,3,2,4,6,5,1},
{0,6,2,1,3,5,4}};
int pb[7][9]={{},
{0,1,2,3,4,5,6,7,8},
{0,5,1,4,8,6,2,3,7},
{0,6,5,8,7,2,1,4,3},
{0,2,6,7,3,1,5,8,4},
{0,5,6,2,1,8,7,3,4},
{0,4,3,7,8,1,2,6,5}};
int ra[7]={0,5,1,3,2,4,6};
int rb[9]={0,4,1,2,3,8,5,6,7};
int bsa[5][7]={{},{0,1,2,3,4,5,6}};
int bsb[5][9]={{},{0,1,2,3,4,5,6,7,8}};
int outa[25][7],outb[25][9];
int fn[9];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
int fnd(int x)
{
	return x==fn[x]?x:fn[x]=fnd(fn[x]);
}
int getv(int *p,int l)
{
	for(int i=1;i<=l;i++)
		fn[i]=i;
	int ans=0;
	for(int i=1;i<=l;i++)
	{
		int fa=fnd(i),fb=fnd(p[i]);
		if(fa==fb)
			ans++;
		else
			fn[fa]=fb;
	}
	return ans;
}
void solve()
{
	int cnt=0;
	for(int i=1;i<=4;i++)
	{
		for(int j=1;j<=6;j++)
		{
			cnt++;
			for(int k=1;k<=6;k++)
				outa[cnt][k]=pa[j][bsa[i][k]];
			for(int k=1;k<=8;k++)
				outb[cnt][k]=pb[j][bsb[i][k]];
		}
		for(int j=1;j<=6;j++)
			bsa[i+1][j]=ra[bsa[i][j]];
		for(int j=1;j<=8;j++)
			bsb[i+1][j]=rb[bsb[i][j]];
	}/*
	for(int i=1;i<=cnt;i++)
	{
		printf("i:%d----------\n",i);
		printf("a: ");
		for(int j=1;j<=6;j++)
			printf("%d ",outa[i][j]);
		printf("\nb: ");
		for(int j=1;j<=8;j++)
			printf("%d ",outb[i][j]);
		printf("\n");
	}*/
	int ans=0;
	for(int i=1;i<=cnt;i++)
	{
		int sma=getv(outa[i],6),smb=getv(outb[i],8);
		ans=(ans+(li)qpow(ca,sma)*qpow(cb,smb))%mod;
	}
	ans=(li)ans*qpow(cnt,mod-2)%mod;
	printf("%d",ans);
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&ca,&cb);
	solve();
	return 0;
}
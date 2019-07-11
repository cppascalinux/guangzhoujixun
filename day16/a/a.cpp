#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#include<cmath>
#define ldb long double
#define li long long
#define mod 10000000000000061LL
using namespace std;
li n,out;
int vis[10],st[10];
li qmul(li a,li b)
{
	return ((a*b-(li)((ldb)a/mod*b)*mod)%mod+mod)%mod;
}
li qpow(li a,li b)
{
	li ans=1;
	for(;b;b>>=1,a=qmul(a,a))
		if(b&1)
			ans=qmul(ans,a);
	return ans;
}
int count(li x)
{
	int ans=0;
	while(x)
		x-=x&-x,ans^=1;
	return ans;
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%lld",&n);
	li sm0=0,sm1=0;
	if(n&1)
		sm0=n>>1,sm1=n-sm0;
	else
	{
		int t=count(n);
		if(t)
			sm0=(n-1)>>1,sm1=n-sm0;
		else
			sm0=sm1=n>>1;
	}
	li ans=0,inv=0;
	ans=(qmul(sm1,sm1-1)+qmul(sm0,sm0-1))%mod;
	inv=qpow(qmul(n,n-1),mod-2);
	ans=qmul(ans,inv);
	printf("%lld",ans);/*
	dfs(1);
	printf("%lld",out);*/
	return 0;
}

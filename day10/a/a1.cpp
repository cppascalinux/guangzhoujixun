//2019.07.01
//xsy1612 Problem A: 函数 假设存在积性函数g,h,使得f=g*h,并且满足g(p)=0,且h的前缀和可以快速计算,那么g(x)不为0的x不会超过sqrt(n)个,就可以在
//sqrt(n)的时间内计算出f(x)的前缀和,先考虑如何构造h:f(p)=g(1)*h(p)+g(p)*h(1)=h(p)=p^k,那么可以令h(x)=x^k,有一个结论是x^k的前缀和一定可以表示为一个
//(n+1)次多项式,因此可以使用拉格朗日插值O(k)计算,再观察发现g(p^e),e>=2是p^k-p^2k(神tm观察),直接筛出<=sqrt(n)的所有素数,爆搜所有powerful number和g值
//然后乘上h的前缀和即可
#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#define li long long
#define mod 1000000007
using namespace std;
li n;
int k,tot,ans,prmx;
int pm[6000009],pw[6000009];
int pre[100009];
char vis[10000009];
int px[109],tx[109];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void initpm()
{
	int mx=sqrt(n+0.5)+1;
	vis[1]=1;
	for(int i=2;i<=mx;i++)
	{
		if(!vis[i])
		{
			pm[++tot]=i,pw[tot]=qpow(i,k);
			pw[tot]=(li)pw[tot]*(1-pw[tot]+mod)%mod;
		}
		for(int j=1;j<=tot&&i*pm[j]<=mx;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
				break;
		}
	}
	// for(int i=1;i<=tot;i++)
	// 	printf("i:%d pm:%d pw:%d\n",i,pm[i],pw[i]);
}
void inith()
{
	int v=0;
	for(int i=0;i<=k+1;i++)
	{
		memset(tx,0,sizeof(tx));
		tx[0]=1;
		for(int j=0;j<=k+1;j++)
			if(i!=j)
			{
				for(int l=k+1;l>=1;l--)
					tx[l]=(tx[l-1]-(li)j*tx[l]%mod+mod)%mod;
				tx[0]=(li)tx[0]*(mod-j)%mod;
				int inv=qpow(i-j+mod,mod-2);
				for(int l=0;l<=k+1;l++)
					tx[l]=(li)tx[l]*inv%mod;
			}
		v=(v+qpow(i,k))%mod;
		// printf("i:%d v:%d\n",i,v);
		for(int j=0;j<=k+1;j++)
			tx[j]=(li)tx[j]*v%mod;
		// for(int j=0;j<=k+1;j++)
		// 	printf("j:%d tx:%d\n",j,tx[j]);
		for(int j=0;j<=k+1;j++)
			px[j]=(px[j]+tx[j])%mod;
	}
	// for(int i=0;i<=k+1;i++)
	// 	printf("i:%d px:%d\n",i,px[i]);
}
int geth(int x)
{
	if(x<=prmx)
		return pre[x];
	int ans=0;
	for(int i=k+1;i>=0;i--)
		ans=((li)ans*x+px[i])%mod;
	return ans;
}
void initpre()
{
	prmx=100000;
	for(int i=1;i<=prmx;i++)
		pre[i]=(pre[i-1]+qpow(i,k))%mod;
}
void dfs(int d,li res,int g)
{
	ans=(ans+(li)g*geth(res%mod))%mod;
	for(int i=d+1;i<=tot&&(li)pm[i]*pm[i]<=res;i++)
	{
		int p=pm[i];
		int v=(li)pw[i]*g%mod;
		for(li x=(li)p*p;;x*=p)
		{
			dfs(i,res/x,v);
			if(x>res/p)
				break;
		}
	}	
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%lld%d",&n,&k);
	initpm();
	inith();
	initpre();
	dfs(0,n,1);
	printf("%d",ans);
	return 0;
}
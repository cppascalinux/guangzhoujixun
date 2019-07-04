//2019.07.04
//xsy1614 Problem A: 后缀 考虑串长从k增加到k+1,那么就相当于将每一个0变成01,将每一个1变成10,考虑将后缀按照前缀分为6类,即0,001,01,1,10,110
//考虑这6类后缀对应的长度翻倍的过程:i位置的后缀对应2i-1和2i,故每个后缀有对应2个新的后缀,故一共会有12种转移,且这12种转移不互为前缀,
//因此考虑将询问从第k层开始,倒序处理,这样就可以用每一层的排名确定上一层的种类和排名,这样不断递归下去做即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define li long long
#define a 1
#define aab 2
#define ab 3
#define b 4
#define ba 5
#define bba 6
using namespace std;
int n,m;
li sm[109][13];
li pf[109][7];
int mv[15][3]={{},
{b,a,0},
{ba,aab,0},
{a,ab,-1},
{bba,ab,0},
{aab,ab,-1},
{ab,ab,-1},
{a,b,0},
{b,ba,-1},
{ba,ba,-1},
{bba,ba,-1},
{aab,ba,0},
{ab,bba,0}
};
void init()
{
	sm[0][1]=pf[0][1]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=12;j++)
			sm[i][j]+=pf[i-1][mv[j][0]];
		for(int j=1;j<=12;j++)
			pf[i][mv[j][1]]+=sm[i][j];
	}
	for(int i=0;i<=n;i++)
		for(int j=1;j<=6;j++)
			pf[i][j]+=pf[i][j-1];
}
li solve(int k,li rnk)
{
	if(!k)
		return 1;
	for(int i=1;i<=12;i++)
	{
		if(rnk>sm[k][i])
			rnk-=sm[k][i];
		else
			return solve(k-1,rnk+pf[k-1][mv[i][0]-1])*2+mv[i][2];
	}
	// assert(0);
	return 0;
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++)
	{
		li c;
		scanf("%lld",&c);
		printf("%lld\n",solve(n,c));
	}
	return 0;
}
//2019.07.05
//xsy1614 Problem B: 游戏 神仙思路 首先通过一次询问可以求出1的总个数,然后每次询问就可以求出某个集合中1的个数,然后如果使用k次询问能构造出长为n的串,那么
//通过2k次询问能构造出长为n+n+k-1的串,设三部分分别为a,b,c,那么设p为问出a的前k-1次询问,q为问出b的前k-1次询问,则问k-1次(pi)or(qi),再问k-1次(a-pi)or(qi)or{ci}
//再问一次a的1的个数以及整个序列的1的个数,然后就可以根据奇偶性确定ci,又因为知道了a的1的个数,便可以知道pi,qi的答案,可以分治下去构造
//qwq记得分治的时候每一层要分别开数组qwq...浪费了好几个小时
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#include<string>
#include<cassert>
#include"game.h"
#define bi bitset<5009>
using namespace std;
bi qry[11][1030];
int ans[11][1030],kn[11];
int tmp[11][1030],tmq[11][1030];
int tot1;
string out;
string getb(bi &b)
{
	string t;
	t.resize(5000);
	for(int i=1;i<=5000;i++)
		t[i-1]=(int)b[i]+'0';
	return t;
}
int getsm(bi &b)
{
	int t=guess(getb(b));
	return (t+tot1-(5000-(int)b.count()))>>1;
}
void init()
{
	qry[0][1][1]=1;
	int n=1;
	bi lb;
	for(int i=1;i<=5000;i++)
		lb[i]=1;
	for(int i=1;i<=10;i++)
	{
		int k=1<<(i-1);
		kn[i]=n;
		bi ta,tc,tn;
		for(int j=1;j<=n;j++)
			ta[j]=1;
		for(int j=1;j<=k-1;j++)
			qry[i][j]=qry[i-1][j]|(qry[i-1][j]<<n);
		for(int j=1;j<=k-1;j++)
		{
			if(j+2*n<=5000)
				tc[j+2*n]=1;
			qry[i][j+k-1]=(qry[i-1][j]^ta)|(qry[i-1][j]<<n)|tc;
			assert((qry[i-1][j]|ta)==ta);
			if(j+2*n<=5000)
				tc[j+2*n]=0;
		}
		qry[i][2*k-1]=ta;
		n=n*2+(k-1);
		for(int i=1;i<=min(n,5000);i++)
			tn[i]=1;
		qry[i][2*k]=tn;
	}
}
void solve(int d,int lp)
{
	if(d==0)
		return out[lp]=ans[d][1]+'0',void();
	int k=1<<(d-1),n=kn[d],tpa=ans[d][2*k-1],tp=ans[d][2*k],tpc=0;
	for(int i=1;i<=k-1;i++)
	{
		int pos=lp+2*n+i-1,nc=(ans[d][i]+ans[d][i+k-1]-tpa)&1;
		tpc+=nc;
		if(pos<5000)
			out[pos]=nc+'0';
		tmq[d][i]=(ans[d][i]+ans[d][i+k-1]-nc-tpa)>>1;
		tmp[d][i]=ans[d][i]-tmq[d][i];
	}
	tmp[d][k]=tpa,tmq[d][k]=tp-tpc-tpa;
	// printf("d:%d lp:%d tp:%d tpa:%d tpc:%d\n",d,lp,tp,tpa,tpc);
	memcpy(ans[d-1],tmp[d],(k+1)<<2);
	solve(d-1,lp);
	memcpy(ans[d-1],tmq[d],(k+1)<<2);
	solve(d-1,lp+n);
}
string game(int n,int k)
{
	init();
	ans[10][1024]=tot1=guess(getb(qry[10][1024]));
	for(int i=1;i<=1023;i++)
		ans[10][i]=getsm(qry[10][i]);
	out.resize(n);
	solve(10,0);
	return out;
}
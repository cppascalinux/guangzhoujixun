//2019.07.10
//xsy1616 Problem B: Balanced Rainbow Sequence 令左括号为1,右括号为-1,不难发现,如果蓝色括号的和为p,那么红,绿的和均为-p,那么修改的过程就是先把每种颜色内的
//括号和调整对,显然应该翻转一个前缀的右括号/一个后缀的左括号,然后每次操作交换同种颜色内部的两个括号.一定也是交换的最靠前的和最靠后的,设红,绿,蓝分别交换了r,g,b次
//只考虑某两种颜色,如果某个位置的前缀和为-t,那么一定有min(r,x)+min(b,y)>=(t+1)/2,其中x,y为某个常数,这样可以拆成3个关于r,b的不等式,再对红,绿做一遍
//最后得到r>=c1,g>=c2,b>=c3,r+b>=c4,g+b>=c5,不难发现,r+g+b的最小值为max(c1+c2+c3,c1+c5,c2+c4)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define inf 0x7F7F7F7F
using namespace std;
int n,sm[3],out=inf;
char s[6009],ns[6009];
int cl[6009];
int sf[6009],pre[6009][3],nxt[6009][3];
void solve(int x)//sum of color 2 is x
{
	memcpy(s,ns,n+1);
	int sz[3]={0,0,0};
	for(int i=1;i<=n;i++)
		sz[cl[i]]+=s[i];
	// printf("x:%d sz0:%d sz1:%d sz2:%d\n",x,sz[0],sz[1],sz[2]),fflush(stdout);
	int ans=0;
	for(int k=0;k<=2;k++)
	{
		int t=k==2?x:-x;
		for(int i=1;i<=n&&sz[k]<t;i++)
			if(cl[i]==k&&s[i]==-1)
				sz[k]+=2,s[i]=1,ans++;
		for(int i=n;i>=1&&sz[k]>t;i--)
			if(cl[i]==k&&s[i]==1)
				sz[k]-=2,s[i]=-1,ans++;
	}
	if(ans>=out)
		return;
	// assert(sz[0]==-x),assert(sz[1]==-x),assert(sz[2]==x);
	// for(int i=1;i<=n;i++)
	// 	printf("%d ",s[i]);
	// printf("\n"),fflush(stdout);
	int c0=0,c1=0,c2=0,c3=0,c4=0;//r,g,b,r+b,g+b
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<=2;j++)
			pre[i][j]=pre[i-1][j];
		if(s[i]==-1)
			pre[i][cl[i]]++;
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=0;j<=2;j++)
			nxt[i][j]=nxt[i+1][j];
		if(s[i]==1)
			nxt[i][cl[i]]++;
	}
	//0 and 2
	for(int i=1;i<=n;i++)
	{
		sf[i]=sf[i-1];
		if(cl[i]!=1)
		{
			sf[i]+=s[i];
			if(sf[i]<0)
			{
				int t=(-sf[i]+1)>>1;
				int v0=min(pre[i][0],nxt[i+1][0]);
				int v2=min(pre[i][2],nxt[i+1][2]);
				if(v0+v2<t)
					return;
				// printf("i:%d v0:%d v2:%d t:%d\n",i,v0,v2,t),fflush(stdout);
				c0=max(c0,t-v2);
				c2=max(c2,t-v0);
				c3=max(c3,t);
			}
		}
	}
	//1 and 2
	for(int i=1;i<=n;i++)
	{
		sf[i]=sf[i-1];
		if(cl[i]!=0)
		{
			sf[i]+=s[i];
			if(sf[i]<0)
			{
				int t=(-sf[i]+1)>>1;
				int v1=min(pre[i][1],nxt[i+1][1]);
				int v2=min(pre[i][2],nxt[i+1][2]);
				if(v1+v2<t)
					return;
				c1=max(c1,t-v2);
				c2=max(c2,t-v1);
				c4=max(c4,t);
			}
		}
	}
	// printf("c0:%d c1:%d c2:%d c3:%d c4:%d\n",c0,c1,c2,c3,c4);
	ans+=2*max(c0+c1+c2,max(c0+c4,c1+c3));
	out=min(out,ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b2.out","w",stdout);
#endif
	scanf("%d%s",&n,ns+1);
	for(int i=1;i<=n;i++)
		ns[i]=(ns[i]=='('?1:-1);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",cl+i);
		sm[cl[i]]++;
	}
	if((sm[0]&1)!=(sm[1]&1)||(sm[1]&1)!=(sm[2]&1))
		return printf("-1"),0;
	int st=min(sm[0],min(sm[1],sm[2]));
	for(int i=-st;i<=st;i+=2)
		solve(i);
	printf("%d",out>=inf?-1:out);
	return 0;
}
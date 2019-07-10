//2019.07.10
//xsy1616 Problem B: Balanced Rainbow Sequence 令左括号为1,右括号为-1,不难发现,如果蓝色括号的和为p,那么红,绿的和均为-p,那么修改的过程就是先把每种颜色内的
//括号和调整对,显然应该翻转一个前缀的右括号/一个后缀的左括号,然后每次操作交换同种颜色内部的两个括号.一定也是交换的最靠前的和最靠后的,设红,绿,蓝分别交换了r,g,b次
//只考虑某两种颜色,如果某个位置的前缀和为-t,那么一定有min(r,x)+min(b,y)>=(t+1)/2,其中x,y为某个常数,这样可以拆成3个关于r,b的不等式,再对红,绿做一遍
//最后得到r>=c1,g>=c2,b>=c3,r+b>=c4,g+b>=c5,不难发现,r+g+b的最小值为max(c1+c2+c3,c1+c5,c2+c4)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,sm0,sm1,sm2;
char s[6009],ns[6009];
int cl[6009];
void solve(int x)//sum of color 2 is x
{
	memcpy(s,ns,(n+1)<<2);
	int sz0=0,sz1=0,sz2=0;
	for(int i=1;i<=n;i++)
		if(cl[i]==0)
			sz0+=s[i];
		else if(cl[i]==1)
			sz1+=s[i];
		else	
			sz2+=s[i];
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
		sm0+=(cl[i]==0);
		sm1+=(cl[i]==1);
		sm2+=(cl[i]==2);
	}
	if((sm0&1)!=(sm1&1)||(sm1&1)!=(sm2&1))
		return printf("-1"),0;
	int st=min(sm0,min(sm1,sm2));
	for(int i=-st;i<=st;i+=2)
		solve(i);
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
bitset<50009> f[2],sp;
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void dp()
{
	n=99;
	f[n&1].set();
	f[n&1][0]=0;
	for(int i=n+1;i<=50008;i++)
		f[n&1][i]=0;
	sp=f[n&1];
	for(int i=n-1;i>=1;i--)
	{
		int cur=i&1;
		f[cur]=(~((f[cur^1]<<i)|(f[cur^1]>>i)))&sp;
		for(int j=1;j<=n;j++)
			if(f[cur][j])
				printf(".");
			else
				printf("#");
		printf("\n");
	}
	f[1].flip();
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	rd(n),rd(m);
	dp();
	// for(int i=1,a;i<=m;i++)
	// {
	// 	rd(a);
	// 	printf("%d",(int)f[1][a]);
	// }
	// for(int i=1;i<=3000;i++)
	// {
	// 	n=i;
	// 	dp();
	// 	for(int j=1;j<=i;j++)
	// 	if(f[1][j])
	// 		printf("#");
	// 	else
	// 		printf(".");
	// 	printf("\n");
	// }
	return 0;
}
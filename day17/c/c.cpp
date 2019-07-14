//2019.07.14
//xsy1619 Problem C: 格子 不难发现题目要求的就是有多少对染色方案满足都合法,并且每个格子上的数都相等.然后可以轮廓线dp,f[i,j,s1,s2]表示到第i行第j列,
//第一个的轮廓线为s1,第二个的轮廓线为s2时,有多少对相等的.然后枚举轮廓转移即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define mod 10007
using namespace std;
int n,m;
int mat[69][7];
int f[69][7][135][135];
void dp()
{
	memset(f,0,sizeof(f));
	f[0][m][0][0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int s1=0;s1<1<<m;s1++)
			for(int s2=0;s2<1<<m;s2++)
				f[i][0][s1<<1][s2<<1]=f[i-1][m][s1][s2];
		for(int j=1;j<=m;j++)
			for(int s1=0;s1<1<<(m+1);s1++)
				for(int s2=0;s2<1<<(m+1);s2++)
				{
					int sm1=(s1>>(j-1)&1)+(s1>>j&1),sm2=(s2>>(j-1)&1)+(s2>>j&1);
					int b1=s1^(s1&(3<<(j-1))),b2=(s2^(s2&(3<<(j-1))));
					int p=mat[i][j],tmp=0;
					for(int k1=0;k1<4;k1++)
					{
						int nsm1=(k1&1)+(k1>>1&1)+sm1;
						int pos=b1|(k1<<(j-1));
						if(p!=-1&&nsm1!=p)
							continue;
						for(int k2=0;k2<4;k2++)
						{
							int nsm2=(k2&1)+(k2>>1&1)+sm2;
							tmp+=nsm1==nsm2&&(p==-1||(p!=-1&&nsm1==p))?f[i][j-1][pos][b2|(k2<<(j-1))]:0;
						}
					}
					f[i][j][s1][s2]=tmp%mod;
				}
	}
	printf("%d\n",f[n][m][0][0]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	int t;
	scanf("%d",&t);
	while(t--)
	{
		memset(mat,0,sizeof(mat));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",mat[i]+j);
		dp();
	}
	return 0;
}
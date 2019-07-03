#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int q;
pii mat[209][209];
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&q);
	for(int i=-100;i<=100;i++)
		for(int j=-100;j<=100;j++)
			mat[i+100][j+100]=pii(i,j);
	int lp=0,lq=0;
	for(int i=1,a,b,c;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		b+=lp+lq;
		// printf("i:%d b:%d\n",i,b),fflush(stdout);
		if(a==2)
		{
			for(int j=100;j>b;j--)
				for(int k=-100;k<=100;k++)
					mat[j+100][k+100]=mat[j-1+100][k+100];
			for(int j=-100;j<=100;j++)
				mat[b+100][j+100]=pii(i,j);
		}
		else if(a==1)
		{
			for(int j=-100;j<=100;j++)
				for(int k=100;k>b;k--)
					mat[j+100][k+100]=mat[j+100][k-1+100];
			for(int j=-100;j<=100;j++)
				mat[j+100][b+100]=pii(j,i);
		}
		else
		{
			scanf("%d",&c);
			c+=lp-lq;
			printf("%d %d\n",lp=mat[b+100][c+100].fi,lq=mat[b+100][c+100].se),fflush(stdout);
		}
	}
	return 0;
}
//2019.07.06
//xsy1615 Problem A: Jailing Rabbits 不难发现,对于每一个边全部染色的矩形,兔子一定只从4个角跑出去,于是令f(x1,y1,x2,y2)表示对应的矩形中的兔子的期望总跑动距离,
//g(x1,y1,x2,y2,0/1/2/3)表示从4个角跑出去的兔子的个数期望,然后转移的时候枚举矩形内部第一个打的兔子洞进行转移即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define db double
using namespace std;
int n,m,q;
int mt[31][31];
db f[31][31][31][31],g[31][31][31][31][4];
void dp()
{
	for(int lx=2;lx<=n;lx++)
		for(int x1=0;x1<=n-lx;x1++)
		{
			int x2=x1+lx;
			for(int ly=2;ly<=m;ly++)
				for(int y1=0;y1<=m-ly;y1++)
				{
					int y2=y1+ly,smp=0;
					db &nf=f[x1][y1][x2][y2],*ng=g[x1][y1][x2][y2];
					for(int px=x1+1;px<=x2-1;px++)
						for(int py=y1+1;py<=y2-1;py++)
							if(mt[px][py])
							{
								// printf("px:%d py:%d\n",px,py);
								smp++;
								db lf[4]={f[x1][y1][px][py],f[x1][py][px][y2],f[px][py][x2][y2],f[px][y1][x2][py]};
								db *lg[4]={g[x1][y1][px][py],g[x1][py][px][y2],g[px][py][x2][y2],g[px][y1][x2][py]};
								int tx1=px-x1,tx2=x2-px,ty1=py-y1,ty2=y2-py;
								ng[0]++,ng[1]++,ng[2]++,ng[3]++;
								ng[0]+=lg[0][0]+lg[0][3]+lg[1][3]+lg[3][0];
								ng[1]+=lg[1][1]+lg[1][0]+lg[0][1]+lg[2][0];
								ng[2]+=lg[2][2]+lg[2][1]+lg[1][2]+lg[3][1];
								ng[3]+=lg[3][3]+lg[3][2]+lg[2][3]+lg[0][2];
								nf+=2*(x2-x1+y2-y1);
								nf+=lf[0]+lf[1]+lf[2]+lf[3];
								nf+=lg[0][1]*ty2+lg[0][2]*(tx2+ty1)+lg[0][3]*tx1;
								nf+=lg[1][0]*ty2+lg[1][2]*tx2+lg[1][3]*(tx1+ty1);
								nf+=lg[2][0]*(tx1+ty2)+lg[2][1]*tx2+lg[2][3]*ty1;
								nf+=lg[3][0]*tx1+lg[3][1]*(tx2+ty2)+lg[3][2]*ty1;
							}
					if(!smp)
						continue;
					nf/=smp;
					for(int i=0;i<=3;i++)
						ng[i]/=smp;
				}
		}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1,a,b;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		mt[a][b]=1;
	}
	dp();
	printf("%.10lf",f[0][0][n][m]);
	return 0;
}
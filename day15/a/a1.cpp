//2019.07.09
//xsy1616 Problem A: Cheese 神仙构造 将每个奶酪看成矩形,其中第i个的长为vi,高为wi/vi,那么把所有矩形按高度从小到大排序,列在数轴上,那么即是在数轴上选一段
//长为v/2的区间,使得面积总和为w/2,显然总面积关于左端点是单调的,于是就可以二分套二分,再将左右端点除的矩形切开即可,总时间复杂度O(nlogn+log^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define ldb long double
#define eps 1e-12
using namespace std;
struct node
{
	int x,y,id;
	node(){}
	node(int a,int b,int c){x=a,y=b,id=c;}
	bool operator <(const node &p) const{return (li)y*p.x<(li)x*p.y;}
};
int n;
node s[100009];
ldb hfx,hfy;
li smx[100009],smy[100009];
int getp(ldb x)
{
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(smx[mid]>=x)
			r=mid;
		else
			l=mid+1;
	}
	return l;
}
ldb gety(ldb x1,ldb x2)
{
	int p1=getp(x1),p2=getp(x2);
	ldb ans=smy[p2-1]-smy[p1];
	ans+=(smx[p1]-x1)*((ldb)s[p1].y/s[p1].x);
	ans+=(x2-smx[p2-1])*((ldb)s[p2].y/s[p2].x);
	return ans;
}
void solve()
{
	sort(s+1,s+n+1);
	for(int i=1;i<=n;i++)
	{
		smx[i]=smx[i-1]+s[i].x;
		smy[i]=smy[i-1]+s[i].y;
	}
	hfx=(ldb)smx[n]/2;
	hfy=(ldb)smy[n]/2;
	ldb l=0,r=hfx;
	for(int i=1;i<=1000;i++)
	{
		ldb mid=(l+r)/2;
		if(gety(mid,mid+hfx)<hfy)
			l=mid;
		else
			r=mid;
	}
	int p1=getp(l),p2=getp(l+hfx);
	ldb b1=(smx[p1]-l)/s[p1].x,b2=(l+hfx-smx[p2-1])/s[p2].x;
	printf("2\n");
	printf("%d %.10lf\n",s[p1].id,(double)b1+eps);
	printf("%d %.10lf\n",s[p2].id,(double)b2+eps);
	printf("%d\n",p2-p1+1);
	for(int i=p1;i<=p2;i++)
		printf("%d ",s[i].id);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&s[i].x,&s[i].y);
		s[i].id=i;
	}
	solve();
	return 0;
}
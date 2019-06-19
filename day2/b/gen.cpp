#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
int s[10009];
random_device sd;
mt19937 rnd(sd());
void build(int l,int r)
{
	if(l==r)
		return;
	int p=l;
	printf("%d ",p);
	build(l,p);
	build(p+1,r);
}
int main()
{
	freopen("b.in","w",stdout);
	int n=10000,m=100000;
	printf("%d %d\n",n,m);
	build(1,n);
	printf("\n");
	for(int i=2;i<=2*n-1;i++)
		printf("%d %d\n",i,(int)(rnd()%(i-1)+1));
	for(int i=1;i<=m;i++)
	{
		int a=rnd()%n+1,b=rnd()%n+1,c,d;
		if(rnd()&1)
			c=1,d=rnd()%n+1;
		else
			c=rnd()%n+1,d=n;
		if(a>b)
			swap(a,b);
		if(c>d)
			swap(c,d);
		printf("%d %d %d %d\n",a,b,c,d);
	}
	return 0;
}
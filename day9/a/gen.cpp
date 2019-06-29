#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
random_device sd;
mt19937 rnd(sd());
int main()
{
	freopen("a.in","w",stdout);
	int n=100000,m=500,typ=0;
	printf("%d %d %d\n",n,m,typ);
	int lft=0;
	for(int i=1;i<=n;i++)
	{
		int l=rnd()%m,r=rnd()%m;
		if(l>r)
			swap(l,r);
		if(lft&&rnd()%2==0)
			printf("%d %d %d\n",2,l,r),lft--;
		else
			printf("%d %d %d %d %d\n",1,(int)(rnd()%m),(int)(rnd()%1000000000+1),l,r),lft++;
	}
	return 0;
}
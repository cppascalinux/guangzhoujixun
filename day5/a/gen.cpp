#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
random_device sd;
mt19937 rnd(sd());
using namespace std;
int main()
{
	freopen("a.in","w",stdout);
	int n=2001,m=1000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",(int)(rnd()%10+1));
	printf("\n%d\n",m);
	for(int i=1;i<=m;i++)
		printf("%d ",i);
	return 0;
}
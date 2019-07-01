#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
random_device sd;
mt19937 rnd(sd());
int n,m,l;
int main()
{
	freopen("b.in","w",stdout);
	int n=5000,m=500,l=5;
	printf("%d %d %d\n",n,m,l);
	for(int i=2;i<=n;i++)
		printf("%lu ",rnd()%(i-1)+1);
	printf("\n");
	for(int i=1;i<=n;i++)
		printf("%lu ",rnd()%l+1);
	printf("\n");
	for(int i=1;i<=m;i++)
		printf("%lu ",rnd()%l+1);
	return 0;
}
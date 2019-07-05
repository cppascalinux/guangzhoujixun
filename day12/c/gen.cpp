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
	freopen("c.in","w",stdout);
	int n=300000,m=300000;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d ",(int)(rnd()%1+1));
	printf("\n");
	for(int i=1;i<=m;i++)
		printf("%d %d\n",(int)(rnd()%n),(int)(rnd()%2));
	return 0;
}
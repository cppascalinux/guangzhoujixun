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
	int n=100000,m=500;
	printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,(int)(rnd()%(i-1)+1));
	printf("0 0\n");
	return 0;
}
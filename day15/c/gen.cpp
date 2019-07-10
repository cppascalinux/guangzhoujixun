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
	int n=1000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%lu %lu %lu\n",rnd()%2*2+1,rnd()%1000000000,rnd()%1000000000);
	return 0;
}
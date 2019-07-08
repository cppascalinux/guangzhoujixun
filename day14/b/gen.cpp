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
	freopen("b.in","w",stdout);
	int n=50000,m=200000,typ=1;
	printf("%d %d %d\n",n,m,typ);
	for(int i=1;i<=m;i++)
		printf("%lu %lu\n",rnd()%n+1,rnd()%n+1);
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
using namespace std;
int main()
{
	freopen("b.in","w",stdout);
	random_device sd;
	mt19937 rnd(sd());
	int n=100000,m=n-1;
	printf("%d %d\n",n,m);
	for(int i=2;i<=n;i++)
		printf("%d %d\n",i,i-1);
	return 0;
}
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
	int n=5000,k=5030;
	for(int i=1;i<=n;i++)
		printf("%lu",rnd()%2);
	printf("\n%d",k);
	return 0;
}
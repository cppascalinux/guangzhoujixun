#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#define mod 998244353
using namespace std;
random_device sd;
mt19937 rnd(sd());
int n,m,opt;
int main()
{
	freopen("c.in","w",stdout);
	n=100000,m=50,opt=0;
	printf("%d %d %d\n",n,m,opt);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",(int)(rnd()%mod),(int)(rnd()%mod));
	for(int i=0;i<=n;i++)
		printf("%d ",(int)(rnd()%mod));
	printf("\n");
	for(int i=2;i<=n;i++)
		printf("%d ",(int)(rnd()%(i-1)+1));
	printf("\n");
	for(int i=1;i<=m;i++)
		printf("%d %d\n",(int)(rnd()%n+1),(int)(rnd()%mod));
	return 0;
}
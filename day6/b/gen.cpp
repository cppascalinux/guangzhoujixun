#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#define mx 10000000
using namespace std;
random_device sd;
mt19937 rnd(sd());
int main()
{
	freopen("b.in","w",stdout);
	int n=400,m=400;
	printf("%d %d\n",n,m);
	for(int i=1;i<=n;i++)
		printf("%d %d\n",(int)(rnd()%mx+1),(int)(rnd()%mx+1));
	for(int i=1;i<=m;i++)
		printf("%d %d\n",(int)(rnd()%mx+1),(int)(rnd()%mx+1));
	return 0;
}
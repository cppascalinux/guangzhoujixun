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
	int n=6000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%c",(rnd()&1)?'(':')');
	printf("\n");
	for(int i=1;i<=n;i++)
		printf("%d ",(int)(rnd()%3));
	return 0;
}
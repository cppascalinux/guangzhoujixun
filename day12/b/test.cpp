#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int k=1,n=1;
	for(;n<=10000;n=n*2+k-1,k*=2)
		printf("k:%d n:%d\n",k,n);
	return 0;
}
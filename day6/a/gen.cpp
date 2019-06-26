#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<vector>
#define pb push_back
#define mx 1000000000
using namespace std;
random_device sd;
mt19937 rnd(sd());
vector<int> s[2000009];
int main()
{
	freopen("a.in","w",stdout);
	int n=200000,k=1000,m=200000;
	printf("%d %d\n",n,k);
	for(int i=1;i<=m;i++)
	{
		int u=rnd()%n+1,v=rnd()%mx+1;
		s[u].pb(v);
	}
	for(int i=1;i<=n;i++)
	{
		s[i].pb(rnd()%mx);
		printf("%d ",(int)s[i].size()-1);
		sort(s[i].begin(),s[i].end());
		for(int j=0;j<(int)s[i].size();j++)
			printf("%d ",s[i][j]);
		printf("\n");
	}
	return 0;
}
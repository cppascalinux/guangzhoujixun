#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<random>
#include<queue>
using namespace std;
random_device sd;
mt19937 rnd(sd());
int n=300000,cnt=0;
int s[300009];
int o[300009][27],fil[300009],ft[300009];
void add()
{
	int cur=0;
	for(int i=1;i<=1000;i++)
	{
		if(!o[cur][s[i]])
			o[cur][s[i]]=++cnt;
		ft[o[cur][s[i]]]=cur;
		cur=o[cur][s[i]];
	}
}
void build()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=1;i<=26;i++)
			if(o[x][i])
			{
				if(x)
					fil[o[x][i]]=o[fil[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[fil[x]][i];
	}
}
void output()
{
	printf("%d\n",cnt+1);
	for(int i=1;i<=cnt;i++)
		printf("%d %d\n",i+1,ft[i]+1);
	for(int i=1;i<=cnt;i++)
		printf("%d %d\n",i+1,fil[i]+1);
}
int main()
{
	freopen("c.in","w",stdout);
	for(int i=1;i<=300;i++)
	{
		for(int j=1;j<=1000;j++)
			s[j]=rnd()%26+1;
		add();
	}
	build();
	output();
	return 0;
}
//2019.06.17
//xsy1603 Problem B: Paths 枚举路径的中点,计算答案,并减去三元环和四元环算出来的假答案,用根号分治分析复杂度,O(nsqrt(n))
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
#define li long long
using namespace std;
int n,m;
vector<int> v[100009];
int deg[100009];
li tmp[100009],ans[100009];
int buc[100009],st[100009];
vector<int> sp[100009];
int cmp(int a,int b)
{
	return deg[a]==deg[b]?a<b:deg[a]<deg[b];
}
void sub3()
{
	memset(tmp,0,sizeof(tmp));
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)v[i].size();j++)
			if(cmp(v[i][j],i))
			{
				int u=v[i][j];
				for(int k=0;k<(int)v[u].size();k++)
					if(cmp(v[u][k],i))
					{
						int p=v[u][k];
						if(buc[p])
						{
							ans[i]-=2,ans[u]-=2,ans[p]-=2;
							ans[i]-=2*(deg[i]-2),ans[u]-=2*(deg[u]-2),ans[p]-=2*(deg[p]-2);
							tmp[i]-=2,tmp[u]-=2,tmp[p]-=2;
							ans[i]+=4,ans[u]+=4,ans[p]+=4;
						}
					}
				buc[u]=1;
			}
		for(int j=0;j<(int)v[i].size();j++)
			buc[v[i][j]]=0;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<(int)v[i].size();j++)
			ans[i]+=tmp[v[i][j]];
}
void sub4()
{
	memset(tmp,0,sizeof(tmp));
	memset(buc,0,sizeof(buc));
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<(int)v[i].size();j++)
			if(cmp(v[i][j],i))
			{
				int u=v[i][j];
				for(int k=0;k<(int)v[u].size();k++)
					if(cmp(v[u][k],i))
					{
						int p=v[u][k];
						int sz=sp[p].size();
						ans[i]-=2*sz,ans[u]-=2*sz,ans[p]-=2*sz;
						sp[p].push_back(u);
					}
			}
		for(int j=0;j<(int)v[i].size();j++)
			if(cmp(v[i][j],i))
			{
				int u=v[i][j];
				for(int k=0;k<(int)v[u].size();k++)
					if(cmp(v[u][k],i))
					{
						int p=v[u][k];
						for(int l=0;l<(int)sp[p].size();l++)
						{
							int q=sp[p][l];
							ans[q]-=2*(sp[p].size()-l-1);
						}
						sp[p].clear();
					}
			}
	}
}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		v[a].push_back(b),v[b].push_back(a);
		deg[a]++,deg[b]++;
	}
	for(int i=1;i<=n;i++)
	{
		int sm=0;
		for(int j=0;j<(int)v[i].size();j++)
			sm+=deg[v[i][j]]-1;
		for(int j=0;j<(int)v[i].size();j++)
		{
			tmp[v[i][j]]+=sm-(deg[v[i][j]]-1);
			ans[i]-=sm-(deg[v[i][j]]-1);
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<(int)v[i].size();j++)
			ans[i]+=tmp[v[i][j]];
	sub3();
	sub4();
	for(int i=1;i<=n;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
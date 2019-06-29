//2019.06.29
//xsy1611 Problem B: 饮料 根据题解,n种饮料用k个瓶子装可行,当且仅当存在一种方案,将n个瓶子分为n-k组,每组内部i个饮料的和等于(i-1)个瓶子的总容积
//然后直接瞎子集dp一下就行,可以使用记忆化搜索,找到一个合法区间就不再找,时间复杂度O(n*2^n)(为什么????)
//喔喔,原来是这样子,嗯,我现在完全搞懂了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n;
li tot;
int v[22];
li sm[2100009];
int cnt[2100009];
int f[2100009];
void init()
{
	for(int s=1;s<1<<n;s++)
	{
		for(int i=1;i<=n;i++)
			if(s>>(i-1)&1)
				sm[s]+=v[i],cnt[s]++;
	}
}
int dfs(int x)
{
	if(f[x])
		return 1;
	for(int s=x;s;s=(s-1)&x)
		if(f[s])
			return dfs(x^s);
	return 0;
}
int check(int x)
{
	if(tot%x)
		return 0;
	int tv=tot/x;
	for(int s=1;s<1<<n;s++)
		if(sm[s]==(li)(cnt[s]==1?1:cnt[s]-1)*tv)
			f[s]=1;
		else
			f[s]=0;
	return dfs((1<<n)-1);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",v+i),tot+=v[i];
	init();
	for(int i=(n+1)/2;i<n-1;i++)
	{
		if(check(i))
			return printf("%d",i),0;
	}
	printf("%d",n-1);
	return 0;
}
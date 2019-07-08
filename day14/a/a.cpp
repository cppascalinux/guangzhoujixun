//2019.07.08
//xsy1617 Problem A: 函数 发现答案只与每个素因子的次幂的奇偶性有关,于是可以使用线性基去维护每个素因子的奇偶性,合并就相当于是异或从后向前做,一旦找到可行的x就停止
//这时y一定就是满足条件的最小数字,因为如果存在z<y也满足条件,那么有x^p1^p2^...^pk^y=0,x^q1^q2^...^qw^z=0,两个式子异或,则一定存在p1/q1满足y的限制,且比x更小,矛盾
//然后发现线性基太大没法维护,然后发现每个数>sqrt(n)的素因子至多只有1个,可以拿出来单独算,就只用维护<=sqrt(n)的素数的bitset,就能过了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<bitset>
#define bi bitset<168>
using namespace std;
int n,tot;
int pm[168],vis[1009];
bi v[1000009];
int pa[1000009],used[1000009];
bi bs[1000009];
void initpm()
{
	int m=1000;
	for(int i=2;i<=m;i++)
	{
		if(!vis[i])
			pm[tot++]=i;
		for(int j=0;j<tot&&i*pm[j]<=m;j++)
		{
			vis[i*pm[j]]=1;
			if(i%pm[j]==0)
				break;
		}
	}
	// printf("tot:%d\n",tot);
	// for(int i=0;i<tot;i++)
	// 	printf("%d\n",pm[i]);
}
void initv()
{
	for(int i=1;i<=n;i++)
		pa[i]=i;
	for(int i=0;i<tot;i++)
	{
		int p=pm[i];
		// printf("p:%d\n",p);
		for(int j=p;j<=n;j+=p)
		{
			int sm=0;
			while(pa[j]%p==0)
				pa[j]/=p,sm^=1;
			// printf("p:%d j:%d sm:%d\n",p,j,sm);
			v[j][i]=sm;
		}
	}
	// for(int i=1;i<=n;i++)
	// 	printf("i:%d pa:%d\n",i,pa[i]);
	// for(int i=1;i<=n;i++)
	// 	cout<<"i:"<<i<<"| "<<v[i].to_string()<<endl;
}
int getans(int x)
{
	bi ans=v[n]^v[x];
	if(pa[x]!=pa[n])
	{
		if(pa[n]>1)
		{
			if(!used[pa[n]])
				return 0;
			ans^=bs[pa[n]];
		}
		if(pa[x]>1)
		{
			if(!used[pa[x]])
				return 0;
			ans^=bs[pa[x]];
		}
	}
	for(int i=tot-1;i>=0;i--)
		if(ans[i])
			ans^=bs[i];
	return ans.none();
}
void solve()
{
	if(v[n].none()&&pa[n]<=1)
		return printf("%d",n),void();
	for(int i=n-1;i>=1;i--)
	{
		if(getans(i))
			return printf("%d",i),void();
		if(pa[i]>1)
		{
			if(!used[pa[i]])
			{
				bs[pa[i]]=v[i],used[pa[i]]=1;
				continue;
			}
			else
				v[i]^=bs[pa[i]];
		}
		for(int j=tot-1;j>=0;j--)
			if(v[i][j])
			{
				if(bs[j][j])
					v[i]^=bs[j];
				else
				{
					// for(int k=j-1;k>=0;k--)
					// 	if(v[i][k])
					// 		v[i]^=bs[k];
					// for(int k=j+1;k<tot;k++)
					// 	if(bs[k][j])
					// 		bs[k]^=v[i];
					bs[j]=v[i];
					break;
				}
			}
	}
	printf("-1");
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d",&n);
	initpm();
	initv();
	solve();
	return 0;
}
//2019.06.30
//xsy1610 Problem C: Hat With An Integer 定义两个数组的距离为元素不同的位置个数,然后令S表示到第i天为止,所有人心中已知的不合法的a序列
//如果第x天时,S中存在一个序列和a的距离为1,设Si!=ai,那么第i个人一定就会知道自己的数不是Si,游戏结束,否则所有和S中序列距离为1的序列都要加入S
//(因为如果那些序列可能是a的话,那么在第x天游戏一定就会结束),也就是S和a的最小距离-1,因此答案就是初始时S和a的最小距离
//首先如果bi>ci,那么S一定为空集,输出-1,只考虑bi<=ci的情况.要让S和a的相同元素尽量多,令Bi表示b的前缀和,Ci表示c的前缀和,若Si=ai,Sj=aj,i<j
//那么一定有a[j]>=a[i]+(B[j-1]-B[i-1]),也就是a[j]-B[j-1]>=a[i]-B[i-1],同理a[j]-C[j-1]<=a[i]-C[i-1],于是可以令fi表示前i个位置中
//最多有多少个相同的位置,就是个三维数点,可以使用树套树或者二维线段树维护,时间复杂度O(nlog^2n)
//然后发现一定不存在i>j,使得a[j]-B[j-1]>=a[i]-B[i-1]和a[j]-C[j-1]<=a[i]-C[i-1]同时成立(都相等除外),因为如果成立的话,一定有
//B[i-1]-B[j-1]>=a[i]-a[j]>=C[i-1]-C[j-1],因为不是同时相等,一定有B[i-1]-B[j-1]>C[i-1]-C[j-1],矛盾
//所以最后只需算出(a[i]-B[i-1],a[i]-C[i-1])的一个最长不上升子序列即可,i一定是有序的,一定满足要求,直接O(nlogn)lis即可
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
#define pll pair<li,li>
#define fi first
#define se second
#define inf 10000000000000000LL
using namespace std;
int n;
li sa[100009],sb[100009],sc[100009];
li smb[100009],smc[100009];
pll st[100009];
li f[100009];
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",sa+i);
	for(int i=1;i<=n-1;i++)
	{
		scanf("%lld",sb+i);
		smb[i]=smb[i-1]+sb[i];
	}
	for(int i=1;i<=n-1;i++)
	{
		scanf("%lld",sc+i);
		smc[i]=smc[i-1]+sc[i];
	}
	for(int i=1;i<=n-1;i++)
		if(sb[i]>sc[i])
			return printf("-1"),0;
	for(int i=1;i<=n;i++)
		st[i]=pll(sa[i]-smb[i-1],inf-(sa[i]-smc[i-1]));
	sort(st+1,st+n+1);
	memset(f,0x7F,sizeof(f));
	f[0]=0;
	for(int i=1;i<=n;i++)
		*upper_bound(f+1,f+n+1,st[i].se)=st[i].se;
	int ans=n-(lower_bound(f+1,f+n+1,f[n+1])-f-1);
	printf("%d",ans);
	return 0;
}
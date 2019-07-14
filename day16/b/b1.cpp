//2019.07.12
//xsy1618 Problem B: B 将每个墙拆成两个点,分别表示两个方向,然后得到若干个环,不难发现,每次删除一个墙的时候,如果两边的点在同一个环内,那么一定会分裂为两个环,
//否则一定有两个环合并为1个环,,于是可以对每一个环开一个map表示每种颜色的出现次数,再开一个multiset维护所有出现次数的最大值,每一个环本身可以使用链表来维护
//合并的时候直接启发式合并,并暴力修改map和multiset,分裂的时候可以在链表上走l/2的长度,如果还没有遇到分割点,那么就去分裂另一个环,分裂的时候也去暴力维护map和multiset
//这样启发式合并和分裂的时间复杂度都为O(nlog^2n),不难发现他们的时间复杂度是相互独立的,于是总时间复杂度O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
using namespace std;
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	return 0;
}
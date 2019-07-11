#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define inf 0x7F7F7F7F
using namespace std;
int n;
int cl[6009];
char s[6009];
namespace part1
{
	int f[2][409][409];
	void solve()
	{
		memset(f,0x7F,sizeof(f));
		f[0][0][0]=0;
		int sm0=0,sm1=0;
		for(int i=1;i<=n;i++)
		{
			int cur=i&1;
			memset(f[cur],0x7F,sizeof(f[cur]));
			if(cl[i]==0)
				sm0++;
			else if(cl[i]==1)
				sm1++;
			for(int j=0;j<=i-sm0;j++)
				for(int k=0;k<=i-sm1;k++)
				{
					if(cl[i]==0)
					{
						if(k>0)
							f[cur][j][k]=min(f[cur][j][k],f[cur^1][j][k-1]+(s[i]==')'));
						f[cur][j][k]=min(f[cur][j][k],f[cur^1][j][k+1]+(s[i]=='('));
					}
					else if(cl[i]==1)
					{
						if(j>0)
							f[cur][j][k]=min(f[cur][j][k],f[cur^1][j-1][k]+(s[i]==')'));
						f[cur][j][k]=min(f[cur][j][k],f[cur^1][j+1][k]+(s[i]=='('));
					}
					else
					{
						if(j>0&&k>0)
							f[cur][j][k]=min(f[cur][j][k],f[cur^1][j-1][k-1]+(s[i]==')'));
						f[cur][j][k]=min(f[cur][j][k],f[cur^1][j+1][k+1]+(s[i]=='('));
					}
				}
		}
		printf("%d",f[n&1][0][0]>=inf?-1:f[n&1][0][0]);
	}
}
namespace part2
{
	int st[6009],vis[6009];
	void solve()
	{
		if(n&1)
			return printf("-1"),void();
		int tp=0;
		for(int i=1;i<=n;i++)
			if(s[i]=='(')
				st[++tp]=i;
			else
			{
				if(!tp)
					continue;
				vis[st[tp--]]=vis[i]=1;
			}
		int sml=0,smr=0;
		for(int i=1;i<=n;i++)
			if(s[i]=='('&&!vis[i])
				sml++;
			else if(s[i]==')'&&!vis[i])
				smr++;
		int ans=((sml+1)>>1)+((smr+1)>>1);
		printf("%d",ans);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d",&n);
	scanf("%s",s+1);
	int sm0=0,sm1=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",cl+i);
		if(cl[i]==0)
			sm0++;
		else if(cl[i]==1)
			sm1++;
	}
	if(n<=400)
		part1::solve();
	else if(!sm0&&!sm1)
		part2::solve();
	return 0;
}
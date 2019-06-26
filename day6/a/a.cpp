#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pb push_back
#define li long long
char *p1,*p2,buffer[10000009];
int n,m,smm;
vector<int> s[2000009];
li f[2][1009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void solve1()
{
	memset(f,0x7F,sizeof(f));
	f[0][0]=0;
	int cur=0;
	for(int i=1;i<=n;i++)
		if(s[i].size()>1)
		{
			// printf("i:%d\n",i),fflush(stdout);
			sort(s[i].begin()+1,s[i].end());
			cur^=1;
			memcpy(f[cur],f[cur^1],sizeof(f[cur]));
			li sm=s[i][0];
			// assert(sm==0);
			for(int j=1;j<(int)s[i].size();j++)
			{
				sm+=s[i][j];
				for(int k=j;k<=m;k++)
					f[cur][k]=min(f[cur][k],f[cur^1][k-j]+sm);
			}
		}
	for(int i=1;i<=m;i++)
		printf("%lld ",f[cur][i]);
	// for(int i=2;i<=m-1;i++)
	// 	assert(2*f[cur][i]<f[cur][i-1]+f[cur][i+1]);
}
void solve2()
{
	vector<int> st;
	for(int i=1;i<=n;i++)
		st.insert(st.end(),s[i].begin()+1,s[i].end());
	sort(st.begin(),st.end());
	li sm=0;
	for(int i=0;i<m;i++)
		sm+=st[i],printf("%lld ",sm);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	rd(n),rd(m);
	// printf("n:%d m:%d\n",n,m);
	int fg=1;
	for(int i=1,a;i<=n;i++)
	{
		rd(a),smm+=a;
		for(int j=0,b;j<=a;j++)
		{
			rd(b),s[i].pb(b);
			if(j==0&&b!=0)
				fg=0;
		}
	}
	// for(int i=1;i<=n;i++)
	// {
	// 	for(int j=0;j<(int)s[i].size();j++)
	// 		printf("%d ",s[i][j]);
	// 	printf("\n");
	// }
	// fflush(stdout);
	if(fg)
		solve2();
	else
		solve1();
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pb push_back
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
int s[300009];
int f[300009];
vector<int> vt[300009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void dfs(int x)
{
	f[x]=1;
	for(int i=0;i<(int)vt[x].size();i++)
	{
		dfs(vt[x][i]);
		if(f[vt[x][i]])
			f[x]=0;
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=0;i<n;i++)
		rd(s[i]);
	for(int i=0;i<n;i++)
	{
		int frm=i-s[i]<0?i-s[i]+n:i-s[i];
		if(frm<i)
			vt[frm].pb(i);
	}
	dfs(0);
	int fg=0;
	for(int i=0;i<n&&!fg;i++)
		if(f[i]&&i==s[i])
		{
			fg=1;
			printf("%d\n",i);
			break;
		}
	if(!fg)
		printf("0\n");
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		s[a]=b;
		for(int i=0;i<n;i++)
			vt[i].clear();
		memset(f,0,(n+1)<<2);
		for(int i=0;i<n;i++)
		{
			int frm=i-s[i]<0?i-s[i]+n:i-s[i];
			if(frm<i)
				vt[frm].pb(i);
		}
		dfs(0);
		int fg=0;
		for(int i=0;i<n&&!fg;i++)
			if(f[i]&&i==s[i])
			{
				fg=1;
				printf("%d\n",i);
				break;
			}
		if(!fg)
			printf("0\n");
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#define li long long
#define pb push_back
using namespace std;
int n,m,q,opt,tot;
char s[200009],t[200009];
int o[200009][27];
int lnk[200009];
li sm[200009];
vector<int> gt[200009];
void add(int val)
{
	int l=strlen(t+1),cur=0;
	for(int i=1;i<=l;i++)
	{
		int p=t[i]-'a'+1;
		if(!o[cur][p])
			o[cur][p]=++tot;
		cur=o[cur][p];
	}
	sm[cur]=val;
}
void getf()
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
					lnk[o[x][i]]=o[lnk[x]][i];
				q.push(o[x][i]);
			}
			else
				o[x][i]=o[lnk[x]][i];
	}
	for(int i=1;i<=tot;i++)
		gt[lnk[i]].pb(i);
}
void dfs(int x)
{
	for(int i=0;i<(int)gt[x].size();i++)
	{
		sm[gt[x][i]]+=sm[x];
		dfs(gt[x][i]);
	}
}
void solve(int l,int r)
{
	int cur=0;
	li ans=0;
	for(int i=l;i<=r;i++)
	{
		cur=o[cur][s[i]-'a'+1];
		ans+=sm[cur];
	}
	printf("%lld\n",ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&opt);
	scanf("%s",s+1);
	for(int i=1,a;i<=m;i++)
		scanf("%s%d",t+1,&a),add(a);
	getf();
	dfs(0);
	scanf("%d",&q);
	for(int i=1,a,b;i<=q;i++)
	{
		scanf("%d%d",&a,&b);
		solve(a,b);
	}
	return 0;
}
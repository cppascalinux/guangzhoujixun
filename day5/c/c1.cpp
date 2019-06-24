#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<queue>
#define li long long
using namespace std;
int n,m,typ,tot;
char s[200009],t[200009];
int pos[200009];
int o[400009][27],dep[400009],orv[400009];
int rt[400009];
int ch[10000009][2],rnd[10000009],px[10000009],sm[10000009],v[10000009];
void add0()
{
	int cur=0;
	for(int i=1;i<=n;i++)
	{
		if(!o[cur][s[i]])
		{
			o[cur][s[i]]=++tot;
			dep[o[cur][s[i]]]=dep[cur]+1;
		}
		cur=o[cur][s[i]];
		pos[i]=cur;
	}
}
void add1(int l,int val)
{
	int cur=0;
	for(int i=1;i<=l;i++)
	{
		if(!o[cur][s[i]])
		{
			o[cur][s[i]]=++tot;
			dep[o[cur][s[i]]]=dep[cur]+1;
		}
		cur=o[cur][s[i]];
	}
	orv[cur]=val;
}
void upd(int x)
{
	sm[x]=sm[ch[x][0]]+sm[ch[x][1]]+v[x];
}
int mrg(int a,int b)
{
	if(!a||!b)
		return a+b;
	if(rnd[a]<rnd[b])
		swap(a,b);
	int x=++tot;
	if(px[b]<)
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	srand(20020618+20030619);
	scanf("%d%d%d",&n,&m,&typ);
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	add0();
	for(int i=1,a;i<=m;i++)
	{
		scanf("%s%d",t+1,&a);
		int l=strlen(t+1);
		for(int j=1;j<=l;j++)
			t[i]-='a'-1;
		add1(l,a);
	}

	return 0;
}
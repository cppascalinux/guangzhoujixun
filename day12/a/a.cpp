#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,q,lst=1,cnt=1;
char s[1050009];
int o[2100009][2],ch[2100009][2],lnk[2100009],len[2100009],pos[2100009],org[2100009];
int vis[2100009];
int sa[1050009],tp;
void add(int c,int op)
{
	int cur=++cnt,p;
	org[cur]=1;
	pos[cur]=op;
	len[cur]=len[lst]+1;
	for(p=lst;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			memcpy(o[cln],o[q],2<<2);
			lnk[cln]=lnk[q];
			pos[cln]=pos[q];
			len[cln]=len[p]+1;
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void dfs(int x)
{
	if(org[x])
		sa[++tp]=pos[x];
	for(int i=0;i<=1;i++)
		if(ch[x][i])
			dfs(ch[x][i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	scanf("%d%d",&n,&q);
	n=1<<n;
	for(int i=1;i<n;i++)
		s[i+1]=s[(i^(i&-i))+1]^1;
	for(int i=n;i>=1;i--)
		add(s[i],i);
	for(int i=2;i<=cnt;i++)
		ch[lnk[i]][s[pos[i]+len[lnk[i]]]]=i;
	dfs(1);
	for(int i=1,a;i<=q;i++)
	{
		scanf("%d",&a);
		printf("%d\n",sa[a]);
	}
	return 0;
}
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define li long long
using namespace std;
int n,m,tot,tp,tme,sm1,sm2,ans;
int pos[10009];
int hd[20009],eg[40009],nxt[40009];
int l[20009],r[20009],lp[20009],rp[20009];
int sz1[20009],sz2[20009];
void ins(int a,int b)
{
	eg[++tot]=b;
	nxt[tot]=hd[a];
	hd[a]=tot;
}
void build(int a,int ll,int rr)
{
	l[a]=ll;
	r[a]=rr;
	if(ll==rr)
		return;
	int mid=pos[++tp];
	build(lp[a]=++tme,ll,mid);
	build(rp[a]=++tme,mid+1,rr);
}
void getf(int a,int ll,int rr,int &sm,int *sz)
{
	if(l[a]>rr||r[a]<ll)
		return;
	if(l[a]>=ll&&r[a]<=rr)
	{
		sm++;
		sz[a]=1;
		return;
	}
	getf(lp[a],ll,rr,sm,sz);
	getf(rp[a],ll,rr,sm,sz);
}
void dfs(int x,int fa)
{
	for(int i=hd[x];i;i=nxt[i])
		if(eg[i]!=fa)
		{
			dfs(eg[i],x);
			sz1[x]+=sz1[eg[i]];
			sz2[x]+=sz2[eg[i]];
		}
	ans+=sz1[x]*(sm2-sz2[x])+sz2[x]*(sm1-sz1[x]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++)
		scanf("%d",pos+i);
	tme=1;
	build(1,1,n);
	// printf("tme:%d tp:%d\n",tme,tp);
	for(int i=1,a,b;i<=2*n-2;i++)
	{
		scanf("%d%d",&a,&b);
		ins(a,b);
		ins(b,a);
	}
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		memset(sz1,0,sizeof(sz1));
		memset(sz2,0,sizeof(sz2));
		sm1=sm2=ans=0;
		getf(1,a,b,sm1,sz1);
		getf(1,c,d,sm2,sz2);
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
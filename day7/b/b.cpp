#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pb push_back
#define pii pair<int,int>
#define fi first
#define se second
#define li long long
using namespace std;
int n,m;
vector<int> ta[100009],tb[100009];
namespace part1
{
	int st[509],ord[509],pos[509],epd;
	void dfs(int d,int x,int fa,int ed)
	{
		st[d]=x;
		if(x==ed)
		{
			epd=d;
			memcpy(ord,st,sizeof(st));
			return;
		}
		for(int i=0;i<(int)ta[x].size();i++)
			if(ta[x][i]!=fa)
				dfs(d+1,ta[x][i],x,ed);
	}
	void getans(int a,int b)
	{
		dfs(1,a,0,b);
		memset(pos,0,sizeof(pos));
		for(int i=1;i<=epd;i++)
			pos[ord[i]]=i;
		int ans=0;
		for(int i=1;i<=epd;i++)
		{
			int sm=0;
			for(int j=i;j<=epd;j++)
			{
				sm++;
				int u=ord[j];
				for(int k=0;k<(int)tb[u].size();k++)
				{
					int x=tb[u][k];
					if(pos[x]>=i&&pos[x]<=j)
						sm--;
				}
				if(sm==1)
					ans++;
			}
		}
		printf("%d\n",ans);
	}
	void solve()
	{
		scanf("%d",&m);
		for(int i=1,a,b;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			// printf("%d %d\n",a,b);
			getans(a,b);
		}
	}
}
namespace part2
{
	vector<pii> qry[100009];
	int st[100009],pos[100009];
	li ans[100009];
	int mn[400009],cn[400009],lzmn[400009],lzsm[400009];
	li sm[400009];
	void dfs(int d,int x,int fa)
	{
		st[d]=x;
		pos[x]=d;
		for(int i=0;i<(int)ta[x].size();i++)
			if(ta[x][i]!=fa)
				dfs(d+1,ta[x][i],x);
	}
	void update(int a)
	{
		int la=a<<1,ra=a<<1|1;
		sm[a]=sm[la]+sm[ra];
		mn[a]=min(mn[la],mn[ra]);
		cn[a]=0;
		if(mn[a]==mn[la])
			cn[a]+=cn[la];
		if(mn[a]==mn[ra])
			cn[a]+=cn[ra];
	}
	void down(int a)
	{
		int la=a<<1,ra=a<<1|1;
		if(lzmn[a])
		{
			int v=lzmn[a];
			lzmn[a]=0;
			mn[la]+=v,mn[ra]+=v;
			lzmn[la]+=v,lzmn[ra]+=v;
		}
		if(lzsm[a])
		{
			int v=lzsm[a];
			lzsm[a]=0;
			if(mn[la]==mn[a])
			{
				sm[la]+=(li)v*cn[la];
				lzsm[la]+=v;
			}
			if(mn[ra]==mn[a])
			{
				sm[ra]+=(li)v*cn[ra];
				lzsm[ra]+=v;
			}
		}
	}
	void add(int a,int l,int r,int ll,int rr,int val)
	{
		if(l>rr||r<ll)
			return;
		if(l>=ll&&r<=rr)
			return mn[a]+=val,lzmn[a]+=val,void();
		down(a);
		int mid=(l+r)>>1;
		add(a<<1,l,mid,ll,rr,val);
		add(a<<1|1,mid+1,r,ll,rr,val);
		update(a);
	}
	void getsm(int a,int l,int r,int ll,int rr)
	{
		if(l>rr||r<ll)
			return;
		if(l>=ll&&r<=rr)
		{
			if(mn[a]==1)
				lzsm[a]++,sm[a]+=cn[a];
			return;
		}
		down(a);
		int mid=(l+r)>>1;
		getsm(a<<1,l,mid,ll,rr);
		getsm(a<<1|1,mid+1,r,ll,rr);
		update(a);
	}
	int ask(int a,int l,int r,int ll,int rr)
	{
		if(l>rr||r<ll)
			return 0;
		if(l>=ll&&r<=rr)
			return sm[a];
		down(a);
		int mid=(l+r)>>1;
		return ask(a<<1,l,mid,ll,rr)+ask(a<<1|1,mid+1,r,ll,rr);
	}
	int getmn(int a,int l,int r,int pos)
	{
		if(l==r)
			return mn[a];
		down(a);
		int mid=(l+r)>>1;
		if(pos<=mid)
			return getmn(a<<1,l,mid,pos);
		return getmn(a<<1|1,mid+1,r,pos);
	}
	void getans()
	{
		for(int i=1;i<=4*n;i++)
			cn[i]=1;
		for(int i=1;i<=n;i++)
		{
			// printf("i:%d------------------------------\n",i);
			int x=st[i];
			add(1,1,n,1,i,1);
			// for(int j=1;j<=i;j++)
			// 	printf("j:%d mn:%d\n",j,getmn(1,1,n,j));
			for(int j=0;j<(int)tb[x].size();j++)
			{
				int y=pos[tb[x][j]];
				// printf("y:%d\n",y);
				if(y<=i)
					add(1,1,n,1,y,-1);
			}
			getsm(1,1,n,1,i);
			// for(int j=1;j<=i;j++)
			// 	printf("j:%d mn:%d\n",j,getmn(1,1,n,j));
			for(int j=0;j<(int)qry[i].size();j++)
				ans[qry[i][j].se]=ask(1,1,n,qry[i][j].fi,i);
		}
		for(int i=1;i<=m;i++)
			printf("%lld\n",ans[i]);
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
			if(ta[i].size()==1)
			{
				dfs(1,i,0);
				break;
			}
		// for(int i=1;i<=n;i++)
		// 	printf("i:%d st:%d pos:%d\n",i,st[i],pos[i]);
		scanf("%d",&m);
		for(int i=1,a,b;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			a=pos[a],b=pos[b];
			if(a>b)
				swap(a,b);
			qry[b].pb(pii(a,i));
		}
		getans();
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d",&n);
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		ta[a].pb(b),ta[b].pb(a);
	}
	for(int i=1,a,b;i<=n-1;i++)
	{
		scanf("%d%d",&a,&b);
		tb[a].pb(b),tb[b].pb(a);
	}
	if(n<=500)
		part1::solve();
	else
		part2::solve();
	return 0;
}
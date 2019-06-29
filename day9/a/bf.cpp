#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define pb push_back
#define mod 1000000007
#define li long long
using namespace std;
int n,m,typ;
namespace part1
{
	int w[50009],v[50009];
	li f[2][509];
	int lst=0,lp=1,rp=0;
	li getans(int l,int r)
	{
		// assert(lp<=rp+1);
		// printf("lp:%d rp:%d\n",lp,rp),fflush(stdout);
		memset(f,0x80,sizeof(f));
		f[0][0]=0;
		int cur=0;
		for(int j=lp;j<=rp;j++)
		{
			cur^=1;
			for(int k=0;k<m;k++)
			{
				int np=k+w[j]>=m?k+w[j]-m:k+w[j];
				f[cur][np]=max(f[cur^1][np],f[cur^1][k]+v[j]);
			}
		}
		li ans=-1;
		for(int i=l;i<=r;i++)
			ans=max(ans,f[cur][i]);
		return ans;
	}
	void solve()
	{
		for(int i=1,a,b,c,d,e;i<=n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			b^=lst,c^=lst;
			if(a==2)
			{
				// if(lp<rp)
					lp++;
				li ans=getans(b,c);
				if(ans>=0&&typ)
					lst=ans%mod;
				printf("%lld\n",ans);
			}
			else
			{
				scanf("%d%d",&d,&e);
				d^=lst,e^=lst;
				rp++;
				w[rp]=b,v[rp]=c;
				li ans=getans(d,e);
				if(ans>=0&&typ)
					lst=ans%mod;
				printf("%lld\n",ans);
			}
		}
	}
}
namespace part2
{
	li f[59][509],g[2][509];
	int st[100009],w[100009],v[100009];
	int lq[100009],rq[100009];
	li ans[100009];
	vector<int> vs[400009];
	void add(int a,int l,int r,int ll,int rr,int val)
	{
		if(l>rr||r<ll)
			return;
		if(l>=ll&&r<=rr)
			return vs[a].pb(val),void();
		int mid=(l+r)>>1;
		add(a<<1,l,mid,ll,rr,val);
		add(a<<1|1,mid+1,r,ll,rr,val);
	}
	void dfs(int d,int a,int l,int r)
	{
		int cur=0;
		memcpy(g[0],f[d],sizeof(g[0]));
		for(int i=0;i<(int)vs[a].size();i++)
		{
			cur^=1;
			int x=vs[a][i],tw=w[x],tv=v[x];
			for(int j=0;j<m;j++)
			{
				int np=j+tw>=m?j+tw-m:j+tw;
				g[cur][np]=max(g[cur^1][np],g[cur^1][j]+tv);
			}
		}
		memcpy(f[d],g[cur],sizeof(f[d]));
		if(l==r)
		{
			ans[l]=-1;
			for(int i=lq[l];i<=rq[l];i++)
				ans[l]=max(ans[l],f[d][i]);
			return;
		}
		int mid=(l+r)>>1;
		memcpy(f[d+1],f[d],sizeof(f[d]));
		dfs(d+1,a<<1,l,mid);
		memcpy(f[d+1],f[d],sizeof(f[d]));
		dfs(d+1,a<<1|1,mid+1,r);
	}
	void solve()
	{
		int lp=1,rp=0;
		for(int i=1,a,b,c,d,e;i<=n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			if(a==1)
			{
				scanf("%d%d",&d,&e);
				rp++;
				w[rp]=b,v[rp]=c;
				lq[i]=d,rq[i]=e;
				st[rp]=i;
			}
			else
			{
				add(1,1,n,st[lp],i-1,lp);
				lp++;
				lq[i]=b,rq[i]=c;
			}
		}
		for(;lp<=rp;lp++)
			add(1,1,n,st[lp],n,lp);
		memset(f[1],0x80,sizeof(f[1]));
		f[1][0]=0;
		dfs(1,1,1,n);
		for(int i=1;i<=n;i++)
			printf("%lld\n",ans[i]);
	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("a.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&typ);
	// if(n<=500)
		part1::solve();
	// else
	// 	part2::solve();
	return 0;
}
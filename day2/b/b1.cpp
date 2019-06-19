//2019.06.19
//xsy1604 线段树 用线段树建出来L树和R树,L树的每个节点x代表线段树中以x为左端点的最长区间[x,y],x的父亲为y+1,R树同理
//可以证明线段树中的每一个节点和L树,R树中的节点一一对应(除了根之外),要将[l,r]定位到线段树的点上时,只需要在L树上找到最浅的,右端点<=r
//的点,在R树上同理,这样就将[l,r]定位到了L树和R树上的两条路径,每次询问即是询问两对路径对应点在B树上的距离和,差分一下,变成16个
//到根路径的询问,对B树建点分树,求出L树和R树的括号序列接在一起,再跑莫队即可 O(nsqrt(m)log(n))
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cassert>
#define li long long
#define inf 0x7F7F7F7F
#define getmn(a,b) (dep[a]<dep[b]?a:b)
#define pb push_back
#define db double
using namespace std;
int blk[40009];
struct qry
{
	int l,r,id,sgn;
	qry(){}
	qry(int a,int b,int c,int d){l=a,r=b,id=c,sgn=d;}
	bool operator <(const qry &p) const
	{
		return blk[l]==blk[p.l]?(blk[l]&1?r<p.r:r>p.r):blk[l]<blk[p.l];
	}
};
struct node
{
	int dnl,upl,dnr,upr;
	node(){}
	node(int a,int b,int c,int d){dnl=a,upl=b,dnr=c,upr=d;}
};
int n,m,tot,cnt,tme,mn,rt;
int cut[10009];
int l[20009],r[20009];
int mxr[10009],mnl[10009];
vector<int> ta[20009],tb[20009];
int fta[20009][17];
int fb[17][40009],dep[20009],pos[20009];
int lg[40009];
int sz[20009],vis[20009],ft[20009];
int adsz[2][20009],sbsz[2][20009];
li adln[2][20009],sbln[2][20009];
int sa[40009],pa[20009];
int buc1[20009],buc2[20009];
qry q[1600009];
li ans[100009];
vector<int> dis[20009];
void build(int a,int ll,int rr)
{
	l[a]=ll,r[a]=rr;
	if(r[a]>r[mxr[ll]])
		mxr[ll]=a;
	if(l[a]<l[mnl[rr]])
		mnl[rr]=a;
	if(ll==rr)
		return;
	int mid=cut[++tme];
	build(++cnt,ll,mid);
	build(++cnt,mid+1,rr);
}
void getta()
{
	mxr[n+1]=mnl[0]=2*n;
	for(int i=1;i<=n;i++)
	{
		int x=mxr[i],fa=mxr[r[x]+1];
		// printf("x:%d fa:%d\n",x,fa);
		ta[fa].pb(x);
		x=mnl[i],fa=mnl[l[x]-1];
		if(x!=1)
			ta[fa].pb(x);
	}
}
void dfsa1(int x,int fa)
{
	sa[++cnt]=x,pa[x]=cnt;
	fta[x][0]=fa;
	for(int i=1;i<=14;i++)
		fta[x][i]=fta[fta[x][i-1]][i-1];
	for(int i=0;i<(int)ta[x].size();i++)
		dfsa1(ta[x][i],x);
	sa[++cnt]=x;
}
void dfsb1(int x,int fa)
{
	fb[0][++tme]=x,pos[x]=tme;
	dep[x]=dep[fa]+1;
	for(int i=0;i<(int)tb[x].size();i++)
		if(tb[x][i]!=fa)
		{
			dfsb1(tb[x][i],x);
			fb[0][++tme]=x;
		}
}
void initlca()
{
	for(int k=1;k<=15;k++)
		for(int i=1;i<=tme-(1<<k)+1;i++)
			fb[k][i]=getmn(fb[k-1][i],fb[k-1][i+(1<<(k-1))]);
	for(int i=2;i<=tme;i++)
		lg[i]=lg[i>>1]+1;
}
int getlca(int a,int b)
{
	a=pos[a],b=pos[b];
	if(a>b)
		swap(a,b);
	int k=lg[b-a+1];
	return getmn(fb[k][a],fb[k][b-(1<<k)+1]);
}
int getlen(int a,int b)
{
	return dep[a]+dep[b]-2*dep[getlca(a,b)];
}
void getrt(int x,int fa,int siz)
{
	int mx=0,p;
	sz[x]=1;
	for(int i=0;i<(int)tb[x].size();i++)
		if(!vis[p=tb[x][i]]&&p!=fa)
		{
			getrt(p,x,siz);
			mx=max(mx,sz[p]);
			sz[x]+=sz[p];
		}
	mx=max(mx,siz-sz[x]);
	if(mx<mn)
		mn=mx,rt=x;
}
void inittb(int x,int siz)
{
	int p;
	vis[x]=1;
	for(int i=0;i<(int)tb[x].size();i++)
		if(!vis[p=tb[x][i]])
		{
			int nsz=sz[p]>sz[x]?siz-sz[x]:sz[p];
			mn=inf,getrt(p,0,nsz);
			ft[rt]=x;
			inittb(rt,nsz);
		}
}
void initdis()
{
	for(int i=1;i<=2*n-1;i++)
	{
		for(int x=i;x;x=ft[x])
			dis[i].pb(getlen(i,x));
	}
}
li modify(int a,int cl,int sgn)
{
	li ans=0;
	if(!a||a>2*n-1)
		return 0;
	int dp=0;
	for(int x=a,y=0;x;y=x,x=ft[x])
	{
		// int len=getlen(x,a);
		int len=dis[a][dp++];
		// int len=1;
		// printf("x:%d a:%d len;%d\n",x,a,len);
		ans+=sgn*((li)len*(adsz[cl^1][x]-sbsz[cl^1][y])+(adln[cl^1][x]-sbln[cl^1][y]));
		adsz[cl][x]+=sgn;
		adln[cl][x]+=sgn*len;
		if(y)
		{
			sbsz[cl][y]+=sgn;
			sbln[cl][y]+=sgn*len;
		}
	}
	// assert(dp<=14);
	return ans;
}
void initblk()
{
	int len=sqrt((db)n*n/m)*2.8;
	len=max(len,1);
	// printf("len:%d\n",len);
	for(int i=1;i<=4*n;i++)
		blk[i]=(i-1)/len+1;
}
node getp(int ll,int rr)
{
	int dnl=mxr[ll],upl,dnr=mnl[rr],upr;
	if(r[dnl]>rr)
		upl=dnl;
	else
	{
		int t=dnl;
		for(int i=14;i>=0;i--)
			if(r[fta[t][i]]<=rr)
				t=fta[t][i];
		upl=fta[t][0];
	}
	if(l[dnr]<ll||(ll==1&&rr==n))
		upr=dnr;
	else
	{
		int t=dnr;
		for(int i=14;i>=0;i--)
			if(l[fta[t][i]]>=ll)
				t=fta[t][i];
		upr=fta[t][0];
	}
	// printf("l:%d r:%d dnl:%d upl:%d dnr:%d upr:%d\n",ll,rr,dnl,upl,dnr,upr);
	return node(pa[dnl],pa[upl],pa[dnr],pa[upr]);
}
void add(int l1,int r1,int l2,int r2,int id)
{
	node p1=getp(l1,r1),p2=getp(l2,r2);
	q[++tot]=qry(p1.dnl,p2.dnl,id,1),q[++tot]=qry(p1.dnl,p2.upl,id,-1),q[++tot]=qry(p1.dnl,p2.dnr,id,1),q[++tot]=qry(p1.dnl,p2.upr,id,-1);
	q[++tot]=qry(p1.upl,p2.dnl,id,-1),q[++tot]=qry(p1.upl,p2.upl,id,1),q[++tot]=qry(p1.upl,p2.dnr,id,-1),q[++tot]=qry(p1.upl,p2.upr,id,1);
	q[++tot]=qry(p1.dnr,p2.dnl,id,1),q[++tot]=qry(p1.dnr,p2.upl,id,-1),q[++tot]=qry(p1.dnr,p2.dnr,id,1),q[++tot]=qry(p1.dnr,p2.upr,id,-1);
	q[++tot]=qry(p1.upr,p2.dnl,id,-1),q[++tot]=qry(p1.upr,p2.upl,id,1),q[++tot]=qry(p1.upr,p2.dnr,id,-1),q[++tot]=qry(p1.upr,p2.upr,id,1);
}
void solve()
{
	sort(q+1,q+tot+1);
	// q[tot=1]=qry(8,7,1,1);
	li sm=0;
	int pl=0,pr=0;
	for(int i=1;i<=tot;i++)
	{
		// printf("l:%d r:%d sgn:%d\n",q[i].l,q[i].r,q[i].sgn);
		while(pl<q[i].l)
		{
			buc1[sa[++pl]]^=1;
			sm+=modify(sa[pl],0,buc1[sa[pl]]?1:-1);
			// printf("pl:%d pr:%d sm:%lld\n",pl,pr,sm);
		}
		while(pl>q[i].l)
		{
			sm+=modify(sa[pl],0,buc1[sa[pl]]?-1:1);
			buc1[sa[pl--]]^=1;
			// printf("pl:%d pr:%d sm:%lld\n",pl,pr,sm);
		}
		while(pr<q[i].r)
		{
			buc2[sa[++pr]]^=1;
			sm+=modify(sa[pr],1,buc2[sa[pr]]?1:-1);
			// printf("pl:%d pr:%d sm:%lld\n",pl,pr,sm);
		}
		while(pr>q[i].r)
		{
			sm+=modify(sa[pr],1,buc2[sa[pr]]?-1:1);
			buc2[sa[pr--]]^=1;
			// printf("pl:%d pr:%d sm:%lld\n",pl,pr,sm);
		}
		// for(int i=1;i<=2*n-1;i++)
		// 	printf("i:%d buc1:%d buc2:%d\n",i,buc1[i],buc2[i]);
		assert(sm>=0);
		// printf("pl:%d pr:%d sm:%lld\n",pl,pr,sm);
		ans[q[i].id]+=sm*q[i].sgn;
	}
}
void dbg()
{
	for(int i=1;i<=2*n-1;i++)
		printf("i:%d l:%d r:%d ft:%d\n",i,l[i],r[i],ft[i]);
	for(int i=1;i<=n;i++)
		printf("i:%d mnl:%d mxr:%d\n",i,mnl[i],mxr[i]);
	for(int i=1;i<=cnt;i++)
		printf("i:%d sa:%d\n",i,sa[i]);
	// for(int i=1;i<=2*n-1;i++)
	// 	for(int j=i;j<=2*n-1;j++)
	// 		printf("i:%d j:%d len:%d\n",i,j,getlen(i,j));
	for(int i=1;i<=2*n;i++)
		printf("i:%d pa:%d\n",i,pa[i]);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("b1.out","w",stdout);
#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n-1;i++)
		scanf("%d",cut+i);
	r[0]=0,l[0]=inf;
	build(cnt=1,1,n);
	getta();
	r[0]=inf,l[0]=0;
	r[2*n]=inf,l[2*n]=0;
	cnt=0;
	dfsa1(2*n,0);
	for(int i=1,a,b;i<=2*n-2;i++)
	{
		scanf("%d%d",&a,&b);
		tb[a].pb(b),tb[b].pb(a);
	}
	tme=0;
	dfsb1(1,0);
	initlca();
	mn=inf,getrt(1,0,2*n-1);
	inittb(rt,2*n-1);
	initblk();
	initdis();
	for(int i=1,a,b,c,d;i<=m;i++)
	{
		scanf("%d%d%d%d",&a,&b,&c,&d);
		add(a,b,c,d,i);
	}
	solve();
	// dbg();
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
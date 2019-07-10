//2019.07.10
//xsy1616 Problem C: Ranges 首先可以离线线段树分治,这样就只有添加点然后询问与左上角点构成的矩形的面积最大值,不难发现如果一个点左上方还有点的话,他一定是没有用的,
//可以直接删掉,然后得到一些x,y坐标都递增的点,然后列出不等式,发现相邻两个点作为最优解出现的区域一定由一条直线分割开来,如果直线不存在交点的话,那么显然可以扫描线
//然后二分查找询问的y,若两条直线相交,那么显然可以将中间的点删除,可以使用set维护所有直线,再用优先队列维护每个点的消失时间,总时间复杂度O(nlog^2n)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#include<queue>
#include<cassert>
#include<cmath>
#define li long long
#define db double
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eps 1e-10
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define fls() (fwrite(buf2,1,p3-buf2,stdout),p4=(p3=buf2)+10000000,0)
#define pc(x) (p3==p4&&fls()?EOF:*p3++=x)
using namespace std;
char buf1[10000009],buf2[10000009],*p1,*p2,*p3=buf2,*p4=buf2;
int n,qx,qy;
pii sp[200009];
int stt[200009];
int pre[200009],nxt[200009];
li ans[200009];
pii v[200009];
li cal(int x)
{
	if(!x||v[x].fi>=qx||v[x].se<=qy)
		return -1;
	return (li)(qx-v[x].fi)*(v[x].se-qy);
}
struct node
{
	int x,y,id;
	node(){}
	node(int a,int b,int c){x=a,y=b,id=c;}
	bool operator <(const node &p) const{return x<p.x;}
};
struct mat
{
	int x;
	mat(){}
	mat(int a){x=a;}
	bool operator <(const mat &p) const
	{
		if(!x)
			return cal(p.x)>cal(nxt[p.x]);
		if(!p.x)
			return cal(x)<cal(nxt[x]);
		return x<p.x;
	}
};
vector<node> qry[800009];
vector<pii> pt[800009];
template<class T>
void read(T &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
template<class T>
void print(T x)
{
	if(x>=10)
		print(x/10);
	pc(x%10+'0');
}
void addp(int a,int l,int r,int ll,int rr,pii val)
{
	if(l>rr||r<ll)
		return;
	if(l>=ll&&r<=rr)
		return pt[a].pb(val),void();
	int mid=(l+r)>>1;
	addp(a<<1,l,mid,ll,rr,val);
	addp(a<<1|1,mid+1,r,ll,rr,val);
}
void addq(int a,int l,int r,int pos,node val)
{
	qry[a].pb(val);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	if(pos<=mid)
		addq(a<<1,l,mid,pos,val);
	else
		addq(a<<1|1,mid+1,r,pos,val);
}
bool cmp(pii a,pii b)
{
	return a.fi!=b.fi?a.fi<b.fi:a.se>b.se;
}
void init(vector<pii> &p)
{
	sort(p.begin(),p.end(),cmp);
	vector<pii> np;
	for(int i=0;i<(int)p.size();i++)
	{
		if(np.empty())
			np.pb(p[i]);
		else if(p[i].fi>np.back().fi&&p[i].se>np.back().se)
			np.pb(p[i]);
	}
	np.swap(p);
}
int gett(int p2)
{
	int p1=pre[p2],p3=nxt[p2];
	if(!p1||!p3)
		return inf;
	int x1=v[p1].fi,x2=v[p2].fi,x3=v[p3].fi;
	int y1=v[p1].se,y2=v[p2].se,y3=v[p3].se;
	db a1=(db)(y2-y1)/(x1-x2),a2=(db)(y3-y2)/(x2-x3);
	if(a1<=a2)
		return inf;
	if(fabs(a1-a2)<=eps)
		return inf;
	db b1=((li)x1*y1-(li)x2*y2)/(db)(x1-x2);
	db b2=((li)x2*y2-(li)x3*y3)/(db)(x2-x3);
	db ans=(b2-b1)/(a1-a2);
	// if(p2==2)
	// {
	// 	printf("x1:%d y1:%d\nx2:%d y2:%d\nx3:%d y3:%d\n",x1,y1,x2,y2,x3,y3);
	// 	printf("p2:%d p1:%d p3:%d a1:%.2lf a2:%.2lf b1:%lf b2:%lf ans:%.2lf\n",p2,p1,p3,a1,a2,b1,b2,ans);
	// }
	if(ans>inf)
		return inf;
	return ceil(ans);
}
void solve(int a,int l,int r)
{
	// if(a!=1&&a!=3)
	// 	return;
	if(!pt[a].size()||!qry[a].size())
	{
		if(l==r)
			return;
		int mid=(l+r)>>1;
		solve(a<<1,l,mid);
		solve(a<<1|1,mid+1,r);
		return;
	}
	// printf("sizep:%d sizeq:%d\n",(int)pt[a].size(),(int)qry[a].size());
	sort(qry[a].begin(),qry[a].end());
	init(pt[a]);
	// for(node i:qry[a])
	// 	for(pii j:pt[a])
	// 	{
	// 		if(j.fi<i.x&&j.se>i.y)
	// 			ans[i.id]=max(ans[i.id],(li)(i.x-j.fi)*(j.se-i.y));
	// 	}
	int cnt=0;
	for(pii i:pt[a])
		v[++cnt]=i;
	// printf("a:%d l:%d r:%d cnt:%d--------------------------------\n",a,l,r,cnt);
	// for(int i=1;i<=cnt;i++)
	// 	printf("i:%d x:%d y:%d\n",i,v[i].fi,v[i].se);
	set<pii> pq;
	set<mat> s;
	int cur=0;
	for(node t:qry[a])
	{
		// printf("x:%d y:%d id:%d\n",t.x,t.y,t.id);
		qx=t.x,qy=t.y;
		while(cur<cnt&&v[cur+1].fi<qx)
		{
			cur++;
			pre[cur]=cur-1,nxt[cur]=0;
			int t=gett(cur);
			// printf("t:%d\n",t);
			pq.insert(pii(t,cur));
			if(pre[cur])
			{
				int t0=gett(pre[cur]);
				nxt[pre[cur]]=cur;
				int t1=gett(pre[cur]);
				// printf("cur:%d t0:%d t1:%d\n",cur-1,t0,t1);
				pq.erase(pii(t0,pre[cur]));
				pq.insert(pii(t1,pre[cur]));
			}
			s.insert(mat(cur));
		}
		// for(auto k:s)
		// 	printf("k:%d ",k.x);
		while(!pq.empty()&&pq.begin()->fi<=qx)
		{
			int x=pq.begin()->se;
			pq.erase(pq.begin());
			if(pre[x])
			{
				int t0=gett(pre[x]);
				nxt[pre[x]]=nxt[x];
				int t1=gett(pre[x]);
				pq.erase(pii(t0,pre[x]));
				pq.insert(pii(t1,pre[x]));
			}
			if(nxt[x])
			{
				int t0=gett(nxt[x]);
				pre[nxt[x]]=pre[x];
				int t1=gett(nxt[x]);
				pq.erase(pii(t0,nxt[x]));
				pq.insert(pii(t1,nxt[x]));
			}
			s.erase(mat(x));
		}
		auto it=s.upper_bound(mat(0));
		// printf("\n");
		// if(it==s.end())
		// 	printf("sdoihj9gwei9fvjwo\n");
		// printf("cnt:%d x:%d px:%d py:%d qx:%d qy:%d\n",cnt,it->x,v[it->x].fi,v[it->x].se,qx,qy);
		if(it!=s.end()&&v[it->x].se>qy)
			ans[t.id]=max(ans[t.id],cal(it->x));
	}
	if(l==r)
		return;
	int mid=(l+r)>>1;
	solve(a<<1,l,mid);
	solve(a<<1|1,mid+1,r);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	read(n);
	int cntp=0,cntq=0;
	for(int i=1,a,b,c;i<=n;i++)
	{
		read(a),read(b);
		if(a==1)
		{
			read(c);
			sp[++cntp]=pii(b,c);
			stt[cntp]=i;
		}
		else if(a==2)
			addp(1,1,n,stt[b+1],i,sp[b+1]),stt[b+1]=-1;
		else
		{
			read(c);
			addq(1,1,n,i,node(b,c,++cntq));
		}
	}
	for(int i=1;i<=cntp;i++)
		if(stt[i]!=-1)
			addp(1,1,n,stt[i],n,sp[i]);
	memset(ans,-1,sizeof(ans));
	solve(1,1,n);
	for(int i=1;i<=cntq;i++)
	{
		if(ans[i]>=0)
			print(ans[i]);
		else
			pc('-'),pc('1');
		pc('\n');
	}
	return fls(),0;
}
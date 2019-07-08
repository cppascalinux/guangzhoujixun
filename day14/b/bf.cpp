#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<vector>
#define pb push_back
#define inf 0x7F7F7F7F
#define fi first
#define se second
#define gc() (p1==p2&&(p2=(p1=buf1)+fread(buf1,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define flush() (fwrite(buf2,1,p3-buf2,stdout),p4=(p3=buf2)+10000000)
#define pc(x) (p3==p4&&(flush(),0)?EOF:*p3++=x)
using namespace std;
char buf1[10000009],buf2[10000009],*p1,*p2,*p3=buf2,*p4=buf2;
int n,m,typ,csm;
int cl[100009],pre[100009];
int buc[100009],lst[100009];
vector<int> v[100009];
set<int> s[100009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void pt(int x)
{
	if(x>=10)
		pt(x/10);
	pc(x%10+'0');
}
int getans()
{
	memset(buc,0,(n+1)<<2);
	int rp=0,sm=0,ans=inf;
	for(int lp=1;lp<=n;lp++)
	{
		while(rp<n&&sm<csm)
		{
			int t=pre[++rp];
			buc[t]++;
			sm+=t<lp;
		}
		if(sm<csm)
			break;
		// printf("sm:%d csm:%d\n",sm,csm);
		// if(sm>=csm)
		ans=min(ans,rp-lp+1);
		sm+=buc[lp]-1;
	}
	return ans;
}
void clrv(vector<int> &v)
{
	vector<int> tmp;
	tmp.swap(v);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("b.in","r",stdin);
	freopen("bf.out","w",stdout);
#endif
	rd(n),rd(m),rd(typ);
	for(int i=1;i<=n;i++)
		cl[i]=i,v[i].pb(i),s[i].insert(i);
	int lans=0;
	csm=n;
	for(int i=1,a,b;i<=m;i++)
	{
		rd(a),rd(b);
		a=(a-1+lans*typ)%n+1,b=(b-1+lans*typ)%n+1;
		int ca=cl[a],cb=cl[b];
		if(ca==cb)
		{
			if(!lans)
				pt(n);
			else
				pt(lans);
			pc('\n');
			continue;
		}
		csm--;
		if(v[ca].size()<v[cb].size())
			swap(a,b),swap(ca,cb);
		set<int>::iterator it1,it2,it3;
		v[ca].insert(v[ca].end(),v[cb].begin(),v[cb].end());
		for(int i=0;i<(int)v[cb].size();i++)
		{
			cl[v[cb][i]]=ca;
			it3=it2=it1=s[ca].insert(v[cb][i]).fi;
			pre[*it2]=0;
			if(it1!=s[ca].begin())
			{
				it1--;
				pre[*it2]=*it1;
			}
			it3++;
			if(it3!=s[ca].end())
				pre[*it3]=*it2;
		}
		// clrv(v[b]);
		// s[cb].clear();
		// precal();
		// for(int i=1;i<=n;i++)
		// 	printf("i:%d cl:%d pre:%d\n",i,cl[i],pre[i]);
		pt(lans=getans()),pc('\n');
	}
	flush();
	return 0;
}
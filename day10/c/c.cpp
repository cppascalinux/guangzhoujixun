#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define pb push_back
using namespace std;
struct node
{
	int o[27],len,lnk;
	node(){len=lnk=0,memset(o,0,sizeof(o));}
};
struct sam
{
	int lst,cnt;
	vector<node> v;
	sam(){lst=cnt=1,v.pb(node()),v.pb(node());}
	void ins(int c)
	{
		int cur=++cnt,p;
		v.pb(node());
		for(p=lst;p&&!v[p].o[c];p=v[p].lnk)
			v[p].o[c]=cur;
		if(!p)
			v[cur].lnk=1;
		else
		{
			int q=v[p].o[c];
			if(v[q].len==v[p].len+1)
				v[cur].lnk=q;
			else
			{
				int cln=++cnt;
				v.pb(node());
				v[cln]=v[q];
				v[cln].len=v[p].len+1;
				for(;p&&v[p].o[c]==q;p=v[p].lnk)
					v[p].o[c]=cln;
				v[cur].lnk=v[q].lnk=cln;
			}
		}
		lst=cur;
	}
	void add(char *s,int l)
	{
		for(int i=1;i<=l;i++)
			ins(s[i]);
	}
	int ask(char *s,int l)
	{
		int cur=1;
		for(int i=1;i<=l;i++)
			if(!(cur=v[cur].o[s[i]]))
				return 0;
		return 1;
	}
};
int n,typ,tot;
char ts[300009];
sam p[40009];
vector<int> pos;
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d",&n,&typ);
	pos.pb(0);
	int lst=0;
	for(int i=1,a,b,c;i<=n;i++)
	{
		scanf("%d%d",&a,&b);
		b^=lst;
		if(a==1)
		{
			scanf("%s",ts+1);
			int l=strlen(ts+1);
			for(int i=1;i<=l;i++)
			{
				ts[i]-='a'-1;
				ts[i]=(ts[i]+lst-1)%26+1;
			}
			p[++tot].add(ts,l);
			pos.insert(pos.begin()+b+1,tot);
		}
		else
		{
			scanf("%d%s",&c,ts+1);
			c^=lst;
			int l=strlen(ts+1);
			for(int i=1;i<=l;i++)
			{
				ts[i]-='a'-1;
				ts[i]=(ts[i]+lst-1)%26+1;
			}
			int ans=0;
			for(int i=b;i<=c;i++)
				ans+=p[pos[i]].ask(ts,l);
			printf("%d\n",ans);
			if(typ)
				lst=ans;
		}
	}
	return 0;
}
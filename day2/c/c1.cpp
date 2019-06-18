#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define inf 0x7F7F7F7F
#define gc() (p1==p2&&(p2=(p1=buffer)+fread(buffer,1,10000000,stdin),p1==p2)?EOF:*p1++)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
char *p1,*p2,buffer[10000009];
int n,m;
vector<int> f[1000009];
int ans[1000009];
void rd(int &x)
{
	char ch=0;
	x=0;
	while(ch<'0'||ch>'9')
		ch=gc();
	while(ch>='0'&&ch<='9')
		x=x*10+(ch&15),ch=gc();
}
void dp()
{
	f[n].push_back(1),f[n].push_back(n+1);
	for(int i=n;i>=2;i--)
	{
		// printf("i:%d\n",i),fflush(stdout);
		// for(int j=0;j<(int)f[i].size();j++)
		// 	printf("%d ",f[i][j]);
		// printf("\n"),fflush(stdout);
		int pr=f[i][0]-1,pl=pr-2*(i-1),cl=1,cr=1,idl=-1,idr=-1,sm=0;
		while(idl+1<(int)f[i].size())
		{
			int dl=f[i][idl+1]-pl,dr=idr+1<f[i].size()?f[i][idr+1]-pr:inf;
			int bfr=cl&cr;
			if(dl<dr)
				cl^=1,idl++,pl+=dl,pr+=dl;
			else if(dr<dl)
				cr^=1,idr++,pl+=dr,pr+=dr;
			else
				cl^=1,cr^=1,idl++,idr++,pl+=dl,pr+=dl;
			int aft=cl&cr,mid=(pl+pr)>>1;
			if(bfr!=aft)
			{
				if(mid>=1&&mid<=n+1)
					f[i-1].push_back(mid);
				else if(mid<=0)
					sm++;
			}
			// printf("idl:%d idr:%d dl:%d dr:%d cl:%d cr:%d bfr:%d aft:%d pl:%d pr:%d mid:%d sm:%d\n"
			// ,idl,idr,dl,dr,cl,cr,bfr,aft,pl,pr,mid,sm),fflush(stdout);
			// for(int j=0;j<(int)f[i-1].size();j++)
			// 	printf("%d ",f[i-1][j]);
		}
		if(!(sm&1))
		{
			if(f[i-1][0]!=1)
				f[i-1].insert(f[i-1].begin(),1),f[i-1].push_back(n+1);
			else
				f[i-1].erase(f[i-1].begin()),f[i-1].pop_back();
		}
	}
}
void getans()
{
	for(int i=0;i<(int)f[1].size();i++)
		ans[f[1][i]]=1;
	ans[0]=1;
	for(int i=1;i<=n;i++)
		ans[i]^=ans[i-1];
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	rd(n),rd(m);
	dp();
	getans();
	for(int i=1,a;i<=m;i++)
	{
		rd(a);
		printf("%d",ans[a]);
	}
	return 0;
}
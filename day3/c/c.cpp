//2019.06.20
//xsy1605 Problem C: 斐波拉契数串 首先考虑如何判定循环同构,将T复制拼接成TT,在S的sam上跑,如果当前节点的最小长度>|T|,就沿lnk向上跳,直至节点满足要求
//然后考虑如何计算斐波那契串的答案:先暴力拼出a,b,a为最短的长度>=1000000的串,b为a后面的串,TT在S中出现,只有可能是在a中,在b中,跨过ab,跨过ba,跨过bb
//这5种中的1种,对于a,b长度和<=100000的,直接建sam跑,否则对S串哈希,求出每一个长度=|T|的子串的哈希值,存在哈希表中,同时对TT的每一个
//长为|T|的子串求出哈希值,在哈希表中查询答案.全部使用sam的话可能会MLE,全部使用哈希的话,可能会在询问非常多,T非常短,而s1,s2又非常长的情况下TLE
//最后再对算出来的答案乘上一个斐波那契的系数即可,可以使用矩阵快速幂来计算斐波那契数列的第n项
//qwq偷懒没写哈希也过了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cassert>
#define pb push_back
#define li long long
#define mod 998244353
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
struct mat
{
	int v[2][2];
	mat(){memset(v,0,sizeof(v));}
	mat(int a,int b,int c,int d){v[0][0]=a,v[0][1]=b,v[1][0]=c,v[1][1]=d;}
	mat operator *(mat p)
	{
		mat ans;
		for(int i=0;i<=1;i++)
			for(int j=0;j<=1;j++)
				for(int k=0;k<=1;k++)
					ans.v[i][j]=(ans.v[i][j]+(li)v[i][k]*p.v[k][j])%mod;
		return ans;
	}
};
int q,lst=1,cnt=1;
char s1[10009],s2[10009],ts[2000009];
int o[6000009][27],lnk[6000009],len[6000009],sm[6000009],org[6000009],vis[6000009];
vector<int> gt[6000009],sb[109];
vector<char> sp[109],qs[100009];
li qid[100009];
pii qry[100009];
int ansq[100009][5],bel[100009];
template<class T>
void clrv(vector<T> &v)
{
	vector<T> tmp;
	tmp.swap(v);
}
void add(int c)
{
	int cur=++cnt,p;
	len[cur]=len[lst]+1;
	len[0]=-1;
	org[cur]=1;
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
			memcpy(o[cln],o[q],27<<2);
			len[cln]=len[p]+1;
			lnk[cln]=lnk[q];
			org[cln]=0;
			for(;p&&o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void dfs(int x)
{
	sm[x]=org[x];
	for(int i=0;i<(int)gt[x].size();i++)
	{
		dfs(gt[x][i]);
		sm[x]+=sm[gt[x][i]];
	}
	clrv(gt[x]);
}
void getsm()
{
	assert(cnt<6000009);
	for(int i=2;i<=cnt;i++)
		gt[lnk[i]].pb(i);
	dfs(1);
}
void init()
{
	int l1=strlen(s1+1),l2=strlen(s2+1);
	// printf("l1:%d l2:%d\n",l1,l2);
	for(int i=1;i<=l1;i++)
		s1[i]-='a'-1;
	for(int i=1;i<=l2;i++)
		s2[i]-='a'-1;
	sp[1].insert(sp[1].begin(),s1+1,s1+l1+1);
	sp[2].insert(sp[2].begin(),s2+1,s2+l2+1);
	for(int i=3;sp[i-2].size()<2000000;i++)
	{
		sp[i]=sp[i-1];
		sp[i].insert(sp[i].end(),sp[i-2].begin(),sp[i-2].end());
	}
}
int cal(li x)
{
	if(x<=0)
		return 0;
	mat ans(1,0,0,1),a(1,1,1,0);
	for(;x;x>>=1,a=a*a)
		if(x&1)
			ans=ans*a;
	return ans.v[1][0];
}
int getrp(vector<char> &s)
{
	int l=s.size();
	for(int i=0;i<l;i++)
		ts[i+1]=s[i];
	for(int i=l+1;i<=2*l-1;i++)
		ts[i]=ts[i-l];
	// printf("getrp!!!!!!\n");
	// for(int i=1;i<=2*l-1;i++)
	// 	printf("%c",ts[i]+'a'-1);
	// printf("\n");
	int cur=1,ans=0,curl=0;
	vector<int> bk;
	for(int i=1;i<=2*l-1;i++)
	{
		while(cur&&!o[cur][ts[i]])
			cur=lnk[cur],curl=len[cur];
		if(!o[cur][ts[i]])
			cur=1,curl=0;
		else
		{
			cur=o[cur][ts[i]],curl++;
			while(cur&&len[lnk[cur]]+1>l)
				cur=lnk[cur],curl=len[cur];
			if(l<=curl&&!vis[cur])
				assert(sm[cur]>0),ans=(ans+sm[cur])%mod,vis[cur]=1,bk.pb(cur);
		}
	}
	// for(int i=1;i<=l;i++)
	// {
	// 	while(cur&&!o[cur][ts[i]])
	// 		cur=lnk[cur],curl=len[cur];
	// 	if(!cur)
	// 		cur=1,curl=0;
	// 	else
	// 	{
	// 		cur=o[cur][ts[i]],curl++;
	// 		while(cur&&len[lnk[cur]]+1>l)
	// 			cur=lnk[cur],curl=len[cur];
	// 		if(l<=curl&&!vis[cur])
	// 			ans=(ans+sm[cur])%mod,vis[cur]=1,bk.pb(cur);
	// 	}
	// }
	for(int i=0;i<(int)bk.size();i++)
		vis[bk[i]]=0;
	return ans;
}
void getans(int id,vector<int> &s)
{
	// for(int i=1;i<=l;i++)
	// 	printf("ids:%d idt:%d\n",id,s[i].se);

	//a 0
	memset(o,0,(cnt+1)*(27<<2));
	// memset(o,0,sizeof(o));
	// memset(len,0,sizeof(len));
	// memset(lnk,0,sizeof(lnk));
	// memset(sm,0,sizeof(sm));
	// memset(org,0,sizeof(org));
	// memset(vis,0,sizeof(vis));
	cnt=lst=1;
	for(int i=0;i<(int)sp[id].size();i++)
		add(sp[id][i]);
	getsm();
	for(int i=0;i<(int)s.size();i++)
		ansq[s[i]][0]=getrp(qs[s[i]]);

	//ab 1
	for(int i=0;i<(int)sp[id+1].size();i++)
		add(sp[id+1][i]);
	getsm();
	for(int i=0;i<(int)s.size();i++)
		ansq[s[i]][1]=getrp(qs[s[i]]);

	//b 2
	memset(o,0,(cnt+1)*(27<<2));
	cnt=lst=1;
	for(int i=0;i<(int)sp[id+1].size();i++)
		add(sp[id+1][i]);
	getsm();
	for(int i=0;i<(int)s.size();i++)
		ansq[s[i]][2]=getrp(qs[s[i]]);

	//ba 3
	for(int i=0;i<(int)sp[id].size();i++)
		add(sp[id][i]);
	getsm();
	for(int i=0;i<(int)s.size();i++)
		ansq[s[i]][3]=getrp(qs[s[i]]);

	//bb 4
	memset(o,0,(cnt+1)*(27<<2));
	cnt=lst=1;
	for(int i=0;i<(int)sp[id+1].size();i++)
		add(sp[id+1][i]);
	for(int i=0;i<(int)sp[id+1].size();i++)
		add(sp[id+1][i]);
	getsm();
	for(int i=0;i<(int)s.size();i++)
		ansq[s[i]][4]=getrp(qs[s[i]]);
}
void solve()
{
	for(int i=1;i<=q;i++)
		qry[i]=pii(qs[i].size(),i);
	sort(qry+1,qry+q+1);
	int curs=1;
	for(int i=1;i<=q;i++)
	{
		while((int)sp[curs].size()<qry[i].fi)
			curs++;
		if(qid[qry[i].se]<=4)
			bel[qry[i].se]=qid[qry[i].se];
		else
			bel[qry[i].se]=max(curs,4);
	}
	for(int i=1;i<=q;i++)
		sb[bel[i]].push_back(i);
	for(int i=1;i<=100;i++)
		if(sb[i].size())
			getans(i,sb[i]);
}
void output()
{
	for(int i=1;i<=q;i++)
	{
		int tsm=(ansq[i][0]+ansq[i][2])%mod;
		ansq[i][1]=(ansq[i][1]-tsm+mod)%mod;
		ansq[i][3]=(ansq[i][3]-tsm+mod)%mod;
		ansq[i][4]=(ansq[i][4]-2*ansq[i][2]%mod+mod)%mod;
		int ans=0;
		if(qid[i]<bel[i])
			ans=0;
		else if(qid[i]==bel[i])
			ans=ansq[i][0];
		else
		{
			li dt=qid[i]-bel[i];
			int t0=cal(dt),t1=cal(dt-1),t2=cal(dt-2);
			// if(i==3)
			// 	printf("bel3:%d\n",bel[i]);
			// 	printf("%d %d %d %d %d\n",ansq[i][0],ansq[i][2],ansq[i][3],ansq[i][1],ansq[i][4]);
			ans=(ans+(li)ansq[i][0]*t1)%mod;
			ans=(ans+(li)ansq[i][2]*t0)%mod;
			ans=(ans+(li)ansq[i][3]*t1)%mod;
			ans=(ans+(li)ansq[i][1]*(t1+((dt&1)||dt<=1?0:mod-1)))%mod;
			ans=(ans+(li)ansq[i][4]*(t2+((dt&1)&&dt>=3?mod-1:0)))%mod;
			// printf("a:%d b:%d ba:%d ab:%d bb:%d\n",t1,t0,t1,t1+((dt&1)||dt<=1?0:mod-1),t2+((dt&1)&&dt>=3?mod-1:0));
		}
		printf("%d\n",ans);
	}
}
void dbg()
{
	for(int i=1;i<=10;i++)
	{
		for(int j=0;j<(int)sp[i].size();j++)
			printf("%c",sp[i][j]+'a'-1);
		printf("\n");
	}
	for(int i=0;i<(int)sp[10].size();i++)
		add(sp[10][i]);
	// add(1),add(2),add(3),add(2),add(3);
	getsm();
	for(int i=1;i<=cnt;i++)
		printf("i:%d len:%d lnk:%d org:%d sm:%d\n",i,len[i],lnk[i],org[i],sm[i]);
	vector<char> vs;
	vs.pb(2),vs.pb(1),vs.pb(2),vs.pb(2),vs.pb(1),vs.pb(2);
	printf("getrp:%d\n",getrp(vs));
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%s%s",s1+1,s2+1);
	init();
	// dbg();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%lld%s",qid+i,ts+1);
		int l=strlen(ts+1);
		// if(i==3)
			// printf("id:%lld l:%d\n",qid[i],l);
		for(int j=1;j<=l;j++)
			ts[j]-='a'-1;
		qs[i].insert(qs[i].begin(),ts+1,ts+l+1);
	}
	// q=1,qs[1]=qs[3];
	solve();
	output();
	// for(int i=1;i<=q;i++)
	// 	printf("a:%d ab:%d b:%d ba:%d bb:%d\n",ansq[i][0],ansq[i][1],ansq[i][2],ansq[i][3],ansq[i][4]);
	return 0;
}
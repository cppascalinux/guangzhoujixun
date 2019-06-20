//2019.06.20
//xsy1605 Problem C: 斐波拉契数串 首先考虑如何判定循环同构,将T复制拼接成TT,在S的sam上跑,如果当前节点的最小长度>|T|,就沿lnk向上跳,直至节点满足要求
//然后考虑如何计算斐波那契串的答案:先暴力拼出a,b,a为最短的长度>=1000000的串,b为a后面的串,TT在S中出现,只有可能是在a中,在b中,跨过ab,跨过ba,跨过bb
//这5种中的1种,对于a,b长度和<=100000的,直接建sam跑,否则对S串哈希,求出每一个长度=|T|的子串的哈希值,存在哈希表中,同时对TT的每一个
//长为|T|的子串求出哈希值,在哈希表中查询答案.全部使用sam的话可能会MLE,全部使用哈希的话,可能会在询问非常多,T非常短,而s1,s2又非常长的情况下TLE
//最后再对算出来的答案乘上一个斐波那契的系数即可,可以使用矩阵快速幂来计算斐波那契数列的第n项
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 998244353
#define pii pair<int,int>
#define fi first
#define se second
#define bse 619
#define mod1 1000000007
#define mod2 1000000009
#define pb push_back
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
int n,m,q,cnt=1,lst=1;
char s1[10009],s2[10009];
vector<int> gt[7000009];
int o[7000009][27],len[7000009],lnk[7000009],sm[7000009];
vector<char> sp[109];
char qry[2000009];
template<class T>
void clrv(vector<T> &v)
{
	vector<T> tmp;
	tmp.swap(v);
}
int cal(li x)
{
	mat ans(1,0,0,1),a(1,1,1,0);
	for(;x;x>>=1,a=a*a)
		if(x&1)
			ans=ans*a;
	return ans.v[1][0];
}
void add(int c)
{
	int p,cur=++cnt;
	len[cur]=len[lst]+1;
	sm[cur]=1;
	for(;p&&!o[p][c];p=lnk[p])
		o[p][c]=cur;
	if(!p)
		lnk[cur]=1;
	else
	{
		int q=o[p][c];
		if(!len[q]==len[p]+1)
			lnk[cur]=q;
		else
		{
			int cln=++cnt;
			lnk[cln]=lnk[q];
			len[cln]=len[p]+1;
			memcpy(o[cln],o[q],27<<2);
			for(;o[p][c]==q;p=lnk[p])
				o[p][c]=cln;
			lnk[cur]=lnk[q]=cln;
		}
	}
	lst=cur;
}
void dfs(int x)
{
	for(int i=0;i<(int)gt[x].size();i++)
	{
		dfs(gt[x][i]);
		sm[x]+=sm[gt[x][i]];
	}
}
void getsm()
{
	for(int i=2;i<=cnt;i++)
		gt[lnk[i]].push_back(i);
	dfs(1);
	for(int i=1;i<=cnt;i++)
		clrv(gt[i]);
}
void init()
{
	for(int i=1;i<=n;i++)
		sp[1].pb(s1[i]-'a'+1);
	for(int i=1;i<=m;i++)
		sp[2].pb(s2[i]-'a'+1);
	for(int i=3;sp[i-2].size()<=1000000;i++)
	{
		sp[i]=sp[i-1];
		sp[i].insert(sp[i].end(),sp[i-2].begin(),sp[i-1].end());
	}
}
li ask(char *s,int l)
{
	int p=1;
	li ans=0;
	for(int i=1;i<=2*l;i++)
	{

	}
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%s%s",s1+1,s2+1);
	n=strlen(s1+1),m=strlen(s2+1);
	init();
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%s",qry+1);
		int l=strlen(qry+1);
		for(int i=1;i<=l;i++)
			
	}
	return 0;
}
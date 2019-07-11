//2019.07.11
//xsy1618 Problem C: C 定义一个串是lyndon串,当且仅当它是所有循环同构串中字典序最小的(等价于是所有后缀中字典序最小的).不难发现,若u,v是lyndon串,且u<v
//那么一定有u+v也是lyndon串,不难发现,每个字符串都存在唯一一种划分方式,使得每一个得到的串都是lyndon串,且s[i]>=s[i+1],构建的方式可以通过不断合并两个相邻的
//且s[i]<s[i+1]的lyndon串得到,而在这道题中,不难发现划分的位置一定都在lyndon划分的分界点上,在内部划分的话,将分界点向前移到lyndon串首一定更优
//设划分得的串为s1^p1+s2^p2+...,现在要划分为k段,若k|p1,则得到的字典序最大的串一定是s1^(p1/k)+s2^p2+...,否则一定是s1^((p1-1)/k+1),
//再考虑对于每一个后缀如何求出lyndon划分的s1,p1,因为刚刚提到lyndon划分可以通过合并相邻lyndon串得到,于是可以使用单调栈去维护当前后缀的lyndon划分,
//然后可以通过二分+哈希比较字典序,就做完了
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define pii pair<int,int>
#define fi first
#define se second
#define mod1 1000000007
#define mod2 1000000009
#define bn 619
#define li long long
using namespace std;
pii operator +(pii a,pii b){return pii((a.fi+b.fi)%mod1,(a.se+b.se)%mod2);}
pii operator -(pii a,pii b){return pii((a.fi-b.fi+mod1)%mod1,(a.se-b.se+mod2)%mod2);}
pii operator *(pii a,pii b){return pii((li)a.fi*b.fi%mod1,(li)a.se*b.se%mod2);}
pii operator +(pii a,int x){return pii((a.fi+x)%mod1,(a.se+x)%mod2);}
pii operator *(pii a,int x){return pii((li)a.fi*x%mod1,(li)a.se*x%mod2);}
struct node
{
	int l,r,tm;
	node(){}
	node(int a,int b,int c){l=a,r=b,tm=c;}
};
int n,m;
char s[100009];
pii hs[100009],mul[100009];
int len[100009],rep[100009];
node st[100009];
void iniths()
{
	for(int i=1;i<=n;i++)
		hs[i]=hs[i-1]*bn+s[i];
	mul[0]=pii(1,1);
	for(int i=1;i<=n;i++)
		mul[i]=mul[i-1]*bn;
}
pii geths(int l,int r)
{
	return hs[r]-(hs[l-1]*mul[r-l+1]);
}
int cmps(int l1,int r1,int l2,int r2)//s1>s2:1 s1==s2:0 s1<s2:-1
{
	int len1=r1-l1+1,len2=r2-l2+1;
	int l=0,r=min(len1,len2);
	while(l<r)//find the maximum length for s1 and s2 to be equal
	{
		int mid=(l+r+1)>>1;
		if(geths(l1,l1+mid-1)==geths(l2,l2+mid-1))
			l=mid;
		else
			r=mid-1;
	}
	if(l==len1&&l==len2)
		return 0;
	if(l==len2)
		return 1;
	if(l==len1)
		return -1;
	return s[l1+l]>s[l2+l]?1:-1;
}
void initl()
{
	int tp=0;
	for(int i=n;i>=1;i--)
	{
		int le=0;
		while(tp>0&&cmps(i,i+le,st[tp].l,st[tp].r)==-1)
			le+=(st[tp].r-st[tp].l+1)*st[tp].tm,tp--;
		if(tp>0&&cmps(i,i+le,st[tp].l,st[tp].r)==0)
			st[tp].tm++;
		else
			st[++tp]=node(i,i+le,1);
		len[i]=st[tp].r-st[tp].l+1,rep[i]=st[tp].tm;
	}
}
void ask(int l,int k)
{
	if(rep[l]%k==0)
	{
		int lp=l+len[l]*(rep[l]-rep[l]/k);
		printf("%d %d\n",lp,n);
		return;
	}
	int rp=l+len[l]*((rep[l]-1)/k+1)-1;
	printf("%d %d\n",l,rp);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c1.out","w",stdout);
#endif
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	for(int i=1;i<=n;i++)
		s[i]-='a'-1;
	iniths();
	initl();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		ask(a,b);
	}
	return 0;
}
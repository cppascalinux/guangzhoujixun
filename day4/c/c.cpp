#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define li long long
#define mod 998244353
#define pb push_back
#define vi vector<int>
using namespace std;
int n,m,len,lst,opt;
int rt[2][270009],mp[270009];
int va[100009],vb[100009],vk[100009];
int ft[100009];
int qpow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=(li)a*a%mod)
		if(b&1)
			ans=(li)ans*a%mod;
	return ans;
}
void init(int l)
{
	int bit=0;
	while(1<<bit<l)
		bit++;
	len=1<<bit;
	rt[0][0]=rt[1][0]=1;
	rt[0][1]=qpow(3,(mod-1)/len);
	for(int i=2;i<len;i++)
		rt[0][i]=(li)rt[0][i-1]*rt[0][1]%mod;
	for(int i=1;i<len;i++)
		rt[1][i]=rt[0][len-i];
	for(int i=0;i<len;i++)
		mp[i]=(mp[i>>1]>>1)|((i&1)<<(bit-1));
}
void fft(vi &s,int c)
{
	for(int i=0;i<len;i++)
		if(i<mp[i])
			swap(s[i],s[mp[i]]);
	for(int l=2;l<=len;l<<=1)
	{
		int d=l>>1,sp=len/l;
		for(int j=0;j<len;j+=l)
			for(int i=0;i<d;i++)
			{
				int t=(li)s[i+j+d]*rt[c][sp*i]%mod;
				s[i+j+d]=(s[i+j]-t+mod)%mod;
				s[i+j]=(s[i+j]+t)%mod;
			}
	}
	if(c)
	{
		int inv=qpow(len,mod-2);
		for(int i=0;i<len;i++)
			s[i]=(li)s[i]*inv%mod;
	}
}
vi solve(int l,int r)
{
	vi ans;
	if(l==r)
	{
		ans.pb(va[l]),ans.pb(vb[l]);
		return ans;
	}
	int mid=(l+r)>>1;
	vi sml=solve(l,mid),smr=solve(mid+1,r);
	int tsz=((int)sml.size()-1)+((int)smr.size()-1)+1;
	init(tsz);
	sml.resize(len),smr.resize(len),ans.resize(len);
	fft(sml,0),fft(smr,0);
	for(int i=0;i<len;i++)
		ans[i]=(li)sml[i]*smr[i]%mod;
	fft(ans,1);
	ans.resize(tsz);
	return ans;
}
void getsm()
{
	int ans=0;
	vi f=solve(1,n);
	for(int i=0;i<=n;i++)
		ans=(ans+(li)f[i]*vk[i])%mod;
	printf("%d\n",lst=ans);
}
int main()
{
#ifdef I_LOVE_KTY
	freopen("c.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	scanf("%d%d%d",&n,&m,&opt);
	for(int i=1;i<=n;i++)
		scanf("%d%d",va+i,vb+i);
	for(int i=0;i<=n;i++)
		scanf("%d",vk+i);
	for(int i=2;i<=n;i++)
		scanf("%d",ft+i);
	getsm();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(opt)
			a^=lst,b^=lst;
		for(;a;a=ft[a])
			vb[a]=(li)vb[a]*b%mod;
		getsm();
	}
	return 0;
}
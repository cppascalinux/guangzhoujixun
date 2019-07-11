#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
int n,q,cnt;
char s[100009];
int sa[100009],rnk[100009],h[100009],t1[100009],t2[100009],c[100009];
int rs[59][59];
int f[59][59];
void getsa()
{
    int *x=t1,*y=t2,m=26;
    for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
    for(int i=1;i<=m;i++) c[i]+=c[i-1];
    for(int i=1;i<=n;i++) sa[c[x[i]]--]=i;
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-k+1;i<=n;i++)
            y[++p]=i;
        for(int i=1;i<=n;i++)
            if(sa[i]>k)
                y[++p]=sa[i]-k;
        memset(c,0,(m+1)<<2);
        for(int i=1;i<=n;i++) c[x[i]]++;
        for(int i=1;i<=m;i++) c[i]+=c[i-1];
        for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i];
        swap(x,y);
        p=0;
        for(int i=1;i<=n;i++)
            x[sa[i]]=y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k]?p:++p;
        m=p;
        if(m>=n)
            break;
    }
}
void geth()
{
    for(int i=1;i<=n;i++)
        rnk[sa[i]]=i;
    int j=0;
    for(int i=1;i<=n;i++)
    {
        if(j)
            j--;
        int lp=sa[rnk[i]-1];
        while(s[i+j]==s[lp+j])
            j++;
        h[rnk[i]]=j;
    }/*
    for(int i=1;i<=n;i++)
        printf("i:%d sa:%d h:%d\n",i,sa[i],h[i]);*/
}
void getrs()
{
    for(int i=1;i<=n;i++)
    {
        int p=sa[i],lp=sa[i-1];
        for(int j=0;j<=h[i]-1;j++)
            rs[p][p+j]=rs[lp][lp+j];
        for(int j=p+h[i];j<=n;j++)
            rs[p][j]=++cnt;
    }/*
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            printf("i:%d j:%d rs:%d\n",i,j,rs[i][j]);*/
}
void dp()
{
    for(int i=n;i>=1;i--)
    {
        f[i][1]=rs[i][n];
        for(int j=2;j<=n;j++)
        {
            f[i][j]=f[i][j-1];
            for(int k=i+1;k<=n;k++)
                f[i][j]=min(f[i][j],max(f[k][j-1],rs[i][k-1]));
        }
    }
}
void ask(int l,int k)
{
    int ans=f[l][k];
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            if(rs[i][j]==ans&&i>=l)
                return printf("%d %d\n",i,j),void();
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
#endif
    scanf("%s",s+1);
    n=strlen(s+1);
    for(int i=1;i<=n;i++)
        s[i]-='a'-1;
    getsa();
    geth();
    getrs();
    dp();
    scanf("%d",&q);
    for(int i=1,a,b;i<=q;i++)
    {
        scanf("%d%d",&a,&b);
        ask(a,b);
    }
    return 0;
}
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
    int q=0;char ch=' ';
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
    return q;
}
typedef long long LL;
const int N=200010,M=100005,sqn=100,inf=0x3f3f3f3f;
int n,m,qjs,sqn_id[N<<1];LL ans[M];
struct node{int p1,p2,id,v;}q[M*16];
inline bool cmp(node A,node B) {
    if(sqn_id[A.p1]!=sqn_id[B.p1]) return sqn_id[A.p1]<sqn_id[B.p1];
    if(A.p2!=B.p2) return (sqn_id[A.p1]&1)?A.p2<B.p2:A.p2>B.p2;
    return A.p1<B.p1;
}
 
struct A_tree{
    int rt,SZ,son[N][2],pos[N],fa[N][15],dep[N];
    inline void build(int &x,int s,int t) {
        x=++SZ;if(s==t) {pos[s]=x;return;}
        int mid=read();
        build(son[x][0],s,mid),build(son[x][1],mid+1,t);
    }
    inline void dfs(int x,int las) {
        fa[x][0]=las,dep[x]=dep[las]+1;
        for(RI i=1;i<=14;++i) fa[x][i]=fa[fa[x][i-1]][i-1];
        if(son[x][0]) dfs(son[x][0],x),dfs(son[x][1],x);
    }
    inline int lca(int x,int y) {
        if(dep[x]<dep[y]) swap(x,y);
        for(RI i=14;i>=0;--i) if(dep[fa[x][i]]>=dep[y]) x=fa[x][i];
        if(x==y) return x;
        for(RI i=14;i>=0;--i) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
        return fa[x][0];
    }
    inline void prework() {
        build(rt,1,n);
        ++SZ,son[SZ][0]=rt;++SZ,son[SZ-1][1]=SZ,pos[n+1]=SZ;
        ++SZ,son[SZ][1]=SZ-2,rt=SZ;++SZ,son[SZ-1][0]=SZ,pos[0]=SZ;
        dfs(rt,0);
    }
    inline int is(int x) {return son[fa[x][0]][1]==x;}
}A;
 
struct B_tree{
    int h[N],ne[N<<1],to[N<<1],vis[N],sz[N],fa[N];
    int bin[16],Log[N<<1],f[16][N<<1],dep[N],pos[N];
    int tot,rt,mi,js;
    inline void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
    inline void getrt(int x,int las,int SZ) {
        sz[x]=1;int bl=0;
        for(RI i=h[x];i;i=ne[i])
            if(to[i]!=las&&!vis[to[i]])
                getrt(to[i],x,SZ),sz[x]+=sz[to[i]],bl=max(bl,sz[to[i]]);
        bl=max(bl,SZ-sz[x]);
        if(bl<mi) mi=bl,rt=x;
    }
    inline void build(int x,int SZ) {
        vis[x]=1;
        for(RI i=h[x];i;i=ne[i]) {
            if(vis[to[i]]) continue;
            int y=to[i],ksz=(sz[y]>sz[x]?SZ-sz[x]:sz[y]);
            mi=inf,getrt(y,x,ksz),fa[rt]=x,build(rt,ksz);
        }
    }
    inline void dfs(int x,int las) {
        dep[x]=dep[las]+1,f[0][++js]=dep[x],pos[x]=js;
        for(RI i=h[x];i;i=ne[i])
            if(to[i]!=las) dfs(to[i],x),f[0][++js]=dep[x];
    }
    inline void prework() {
        mi=inf,rt=0,getrt(1,0,n+n-1),build(rt,n+n-1);
        dfs(1,0);
        bin[0]=1;for(RI i=1;i<=15;++i) bin[i]=bin[i-1]<<1;
        Log[0]=-1;for(RI i=1;i<=js;++i) Log[i]=Log[i>>1]+1;
        for(RI j=1;j<=15;++j)
            for(RI i=1;i+bin[j]-1<=js;++i)
                if(f[j-1][i]<f[j-1][i+bin[j-1]]) f[j][i]=f[j-1][i];
                else f[j][i]=f[j-1][i+bin[j-1]];
    }
    inline int dis(int x,int y) {
        int re=dep[x]+dep[y];
        x=pos[x],y=pos[y];if(x>y) swap(x,y);
        int t=Log[y-x+1];
        if(f[t][x]<f[t][y-bin[t]+1]) return re-2*f[t][x];
        else return re-2*f[t][y-bin[t]+1];
    }
}B;
 
struct tilted_tree{
    int top,tot,js;
    int h[N],ne[N],to[N],p[N<<1],pos[N],fa[N],st[N];
    inline void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
    inline void build(int x,int o) {
        if(!A.son[x][0]&&!A.son[x][1]) return;
        fa[A.son[x][o]]=st[top],add(st[top],A.son[x][o]),st[++top]=A.son[x][o];
        build(A.son[x][o^1],o),--top,build(A.son[x][o],o);
    }
    inline void dfs(int x) {
        p[++js]=x,pos[x]=js;
        for(RI i=h[x];i;i=ne[i]) dfs(to[i]);
        p[++js]=-x;
    }
    inline void prework() {
        st[++top]=A.rt;
        build(A.rt,0),build(A.rt,1),dfs(A.rt);
    }
}T;
 
LL val1[N],val2[N],fa_val1[N],fa_val2[N];
int sum1[N],sum2[N],dd[N][22];
inline LL move1(int x,int v) {
    if(x<0) x=-x,v=-v;
    if(x>n+n-1) return 0;
    LL res=val2[x];sum1[x]+=v;int kmx=0;
    for(RI i=B.fa[x],j=x,k=1;i;j=i,i=B.fa[i],++k) {
        fa_val1[j]+=dd[x][k]*v,val1[i]+=dd[x][k]*v,sum1[i]+=v;
        res+=(val2[i]-fa_val2[j])+1LL*(sum2[i]-sum2[j])*dd[x][k];
    }
    return res*v;
}
inline LL move2(int x,int v) {
    if(x<0) x=-x,v=-v;
    if(x>n+n-1) return 0;
    LL res=val1[x];sum2[x]+=v;int kmx=0;
    for(RI i=B.fa[x],j=x,k=1;i;j=i,i=B.fa[i],++k) {
        fa_val2[j]+=dd[x][k]*v,val2[i]+=dd[x][k]*v,sum2[i]+=v;
        res+=(val1[i]-fa_val1[j])+1LL*(sum1[i]-sum1[j])*dd[x][k];
    }
    return res*v;
}
inline void work() {
    for(RI i=1;i<=T.js;++i) sqn_id[i]=(i-1)/sqn+1;
    sort(q+1,q+1+qjs,cmp);
    int k1=0,k2=0;LL nowans=0;
    for(RI i=1;i<=n+n-1;++i) {
        int x=B.fa[i];
        for(RI j=1;x;x=B.fa[x],++j) dd[i][j]=B.dis(i,x);
    }
    for(RI i=1;i<=qjs;++i) {
        while(k1<q[i].p1) ++k1,nowans+=move1(T.p[k1],1);
        while(k1>q[i].p1) nowans+=move1(T.p[k1],-1),--k1;
        while(k2<q[i].p2) ++k2,nowans+=move2(T.p[k2],1);
        while(k2>q[i].p2) nowans+=move2(T.p[k2],-1),--k2;
        ans[q[i].id]+=1LL*q[i].v*nowans;
    }
}
 
int main()
{
	freopen("b.in","r",stdin);
	freopen("std.out","w",stdout);
    int x,y;
    n=read(),m=read();
    A.prework(),T.prework();
    for(RI i=1;i<n+n-1;++i) x=read(),y=read(),B.add(x,y),B.add(y,x);
    B.prework();
    for(RI i=1;i<=m;++i) {
        int l1=read(),r1=read(),l2=read(),r2=read();
        int a=A.pos[l1-1],b=A.pos[r1+1],c=A.pos[l2-1],d=A.pos[r2+1];
        int o1=A.lca(a,b),o2=A.lca(c,d);
        int p1=T.pos[A.son[o1][0]],p2=(A.is(b)?T.pos[A.son[A.fa[b][0]][0]]:T.pos[T.fa[b]]);
        int p3=T.pos[A.son[o1][1]],p4=(A.is(a)?T.pos[T.fa[a]]:T.pos[A.son[A.fa[a][0]][1]]);
        int p5=T.pos[A.son[o2][0]],p6=(A.is(d)?T.pos[A.son[A.fa[d][0]][0]]:T.pos[T.fa[d]]);
        int p7=T.pos[A.son[o2][1]],p8=(A.is(c)?T.pos[T.fa[c]]:T.pos[A.son[A.fa[c][0]][1]]);
        q[++qjs]=(node){p1,p5,i,1},q[++qjs]=(node){p1,p6,i,-1};
        q[++qjs]=(node){p2,p5,i,-1},q[++qjs]=(node){p2,p6,i,1};
        q[++qjs]=(node){p1,p7,i,1},q[++qjs]=(node){p1,p8,i,-1};
        q[++qjs]=(node){p2,p7,i,-1},q[++qjs]=(node){p2,p8,i,1};
        q[++qjs]=(node){p3,p5,i,1},q[++qjs]=(node){p3,p6,i,-1};
        q[++qjs]=(node){p4,p5,i,-1},q[++qjs]=(node){p4,p6,i,1};
        q[++qjs]=(node){p3,p7,i,1},q[++qjs]=(node){p3,p8,i,-1};
        q[++qjs]=(node){p4,p7,i,-1},q[++qjs]=(node){p4,p8,i,1};
    }
    work();
    for(RI i=1;i<=m;++i) printf("%lld\n",ans[i]);
    return 0;
}
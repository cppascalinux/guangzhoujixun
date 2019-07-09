#include <bits/stdc++.h>
#define MAXN 100100
using namespace std;
 
int read(){
    char c;
    while((c=getchar())<'0' || c>'9');
    int res=c-'0';
    while((c=getchar())>='0' && c<='9') res=res*10+c-'0';
    return res;
}
 
int n,m,T;
int nxt[MAXN];
int f[MAXN];
set<int> S[MAXN],S0;
 
int debug=0;
 
namespace Seg{
    int maxv[MAXN<<2];
    int tag[MAXN<<2],minb[MAXN<<2];
 
    void init(int x,int l,int r){
        if(l==r){
            maxv[x]=nxt[l];
            return;
        }
        int mid=(l+r)/2;
        init(x<<1,l,mid);
        init(x<<1|1,mid+1,r);
        maxv[x]=max(maxv[x<<1],maxv[x<<1|1]);
    }
 
    void pushdown(int x,int mid,int cr){
        if(tag[x]){
            tag[x<<1]=tag[x];
            minb[x<<1]=tag[x]-mid;
            tag[x<<1|1]=tag[x];
            minb[x<<1|1]=tag[x]-cr;
            tag[x]=0;
        }
    }
 
    void gao2(int x,int cl,int cr,int l,int r,int v){
        if(l<=cl && cr<=r){
            tag[x]=v;
            minb[x]=v-cr;
            return;
        }
        int mid=(cl+cr)>>1;
        pushdown(x,mid,cr);
        if(l<=mid) gao2(x<<1,cl,mid,l,r,v);
        if(r>mid) gao2(x<<1|1,mid+1,cr,l,r,v);
        minb[x]=min(minb[x<<1],minb[x<<1|1]);
    }
 
    int getmax(int x,int cl,int cr,int l,int r){
        if(l<=cl && cr<=r) return maxv[x];
        int mid=(cl+cr)>>1;
        if(r<=mid) return getmax(x<<1,cl,mid,l,r);
        if(l>mid) return getmax(x<<1|1,mid+1,cr,l,r);
        return max(getmax(x<<1,cl,mid,l,r),getmax(x<<1|1,mid+1,cr,l,r));
    }
 
    int find(int x,int l,int r,int v){
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(maxv[x<<1]>v) return find(x<<1,l,mid,v);
        return find(x<<1|1,mid+1,r,v);
    }
 
    void modify1(int x,int l,int r,int pos,int v){
        if(l==r){ maxv[x]=v; return; }
        int mid=(l+r)>>1;
        if(pos<=mid) modify1(x<<1,l,mid,pos,v);
        else modify1(x<<1|1,mid+1,r,pos,v);
        maxv[x]=max(maxv[x<<1],maxv[x<<1|1]);
    }
 
    void modify(int x,int y0,int y){
        int t=(x>0?getmax(1,0,n,0,x-1):0);
        modify1(1,0,n,x,y);
        if(t>=y0) return;
        if(t>y) y=t;
        int x2=(y0==nxt[n]?n:find(1,0,n,y0)-1);
        while(y<nxt[n] && x<=x2){
            int x1=find(1,0,n,y);
            gao2(1,0,n,x,x1-1,y);
            y=nxt[x1];
            x=x1;
        }
    }
 
    void init(){
        init(1,0,n);
        int x=0;
        while(nxt[x]<nxt[n]){
            int x2=find(1,0,n,nxt[x]);
            gao2(1,0,n,x,x2-1,nxt[x]);
            x=x2;
        }
        gao2(1,0,n,x,n,nxt[x]);
    }
}
 
int getf(int x){
    if(f[x]==x) return x;
    return f[x]=getf(f[x]);
}
 
void modify(int x,int y){
    if(y>=nxt[x]) return;
    int y0=nxt[x];
    nxt[x]=y;
    Seg::modify(x,y0,y);
}
 
void merge(int x,int y){
    if(S[x].size()>S[y].size()) swap(x,y);
    S0.erase(S0.find(max(*S[x].begin(),*S[y].begin())));
    if(nxt[0]!=*S0.begin()) modify(0,*(--S0.end()));
    for(int i:S[x]){
        auto it=S[y].insert(i).first;
        auto it2=it;
        it2++;
        if(it2!=S[y].end()) modify(i,*it2);
        if(it!=S[y].begin()){
            auto it2=it;
            modify(*(--it2),i);
        }
    }
    f[x]=y;
}
 
int main(){
    freopen("b.in","r",stdin);
    freopen("std.out","w",stdout);
    n=read(); m=read(); T=read();
    for(int i=1;i<=n;i++) nxt[i]=n*2+1,f[i]=i,S[i].insert(i),S0.insert(i);
    nxt[0]=n;
    Seg::init();
    int lastans=0;
    while(m--){
        int x=(read()+T*lastans-1)%n+1,y=(read()+T*lastans-1)%n+1;
        if(getf(x)!=getf(y)) merge(f[x],f[y]);
        printf("%d\n",lastans=Seg::minb[1]);
    }
    return 0;
}

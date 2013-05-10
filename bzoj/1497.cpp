#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#define len 6500
#define maxn 65000
#define V (len+maxn)
#define E (V*6)
#define rep(i,n) for(long i=1;i<=n;i++)
#define inf 0x6eeeeeee
using namespace std;
struct re{
        long y,z;re* next,*opt;
        re(){}
        re(long y,long z,re* next):y(y),z(z),next(next){}
        void* operator new(size_t,void* p){return p;}
}GG[E],*data=GG,*a[V];
long readt(void){char ch;long r=0;while(ch=getchar(),!isdigit(ch));r=ch-'0';while(ch=getchar(),isdigit(ch))r=r*10+ch-'0';return r;}
inline void add(long u,long v,long c){a[u]=new((void*)data++) re(v,c,a[u]);a[v]=new((void*)data++) re(u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
long n,m,c[len]={0},vs,vt,sos=0,level[V]={0};
bool bfs(long s,long t){
        memset(level,-1,sizeof level);
        long d[V]={0},head=1,tail=1;d[1]=s,level[s]=0;
        while(head<=tail){
                long now=d[head++];
                for(re* p=a[now];p;p=p->next)
                        if(p->z>0&&level[p->y]==-1)
                                level[d[++tail]=p->y]=level[now]+1;
                }
        return level[t]!=-1;
}
long extend(long u,long sum){
        if(u==vt)return sum;
        long r=0,t;
        for(re* p=a[u];p&&r<sum;p=p->next)
                if(p->z>0&&level[p->y]==level[u]+1){
                        t=p->z;if(t>sum-r)t=sum-r;
                        t=extend(p->y,t);
                        r+=t,p->z-=t,(p->opt)->z+=t;
                }
        if(!r)level[u]=-1;
        return r;
}
long dinic(long s,long t){
        long r=0,tt;
        while(bfs(s,t))while(tt=extend(s,inf))r+=tt;
        return r;
}
int main(int argc,char** argv){
        cin >>n>>m;
        vs=n+m+1,vt=vs+1;
        rep(i,n)c[i]=readt(),add(i,vt,c[i]);
        long l1,l2,c;
        rep(i,m)l1=readt(),l2=readt(),c=readt(),add(i+n,l1,inf),add(i+n,l2,inf),add(vs,i+n,c),sos+=c;
        long ans=dinic(vs,vt);
        printf("%ld\n",sos-ans);
        return 0;
}
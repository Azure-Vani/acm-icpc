#include <iostream>
#include <cstring>
#define inf 0x6eeeeeee
#define len 37
#define V len*len
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
        long y,z;re* next,* opt;
        re(){}
        re(long y,long z,re* next):y(y),z(z),next(next){}
        void* operator new(size_t,void* p){return p;}
}GG[V*V],*data=GG,*a[V];
long n,m,vs,vt,lab[len][len],sos=0,level[V]={0},inp[V]={0};
bool h[V]={0};
inline void add(long u,long v,long cc){inp[u]++;a[u]=new((void*)data++) re(v,cc,a[u]);a[v]=new((void*)data++) re(u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
bool bfs(long s,long t){
        memset(level,-1,sizeof level);
        long d[V]={0},head=1,tail=1;level[s]=0;d[1]=s;
        while(head<=tail){
                long now=d[head++];
                for(re* p=a[now];p;p=p->next)
                        if(!h[p->y]&&p->z>0&&level[p->y]==-1)
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
        while(bfs(s,t))
                while(tt=extend(s,inf))
                        r+=tt;
        return r;
}
void circle(void){
        memset(h,1,sizeof h);
        long d[V]={0},head=1,tail=0;
        rep(i,vt)if(!inp[i])d[++tail]=i;
        while(head<=tail){
                long now=d[head++];h[now]=false;
                for(re* p=a[now];p;p=p->next)if((p->opt)->z){
                        inp[p->y]--;if(!inp[p->y])d[++tail]=p->y;}
        }
}
int main(int argc,char** argv){
        cin >>n>>m;
        rep(i,n)rep(j,m)lab[i][j]=(i-1)*m+j;
        vs=lab[n][m]+1,vt=vs+1;
        rep(i,n)rep(j,m){
                long w,u,l1,l2;
                cin >>u>>w;
                if(u<0)add(lab[i][j],vt,-u);else 
                        add(vs,lab[i][j],u);
                rep(k,w)
                        cin >>l1>>l2,add(lab[l1+1][l2+1],lab[i][j],inf);
                if(j<m)
                        add(lab[i][j],lab[i][j+1],inf);
        }
        circle();sos=0;
        for(re* p=a[vs];p;p=p->next)if(!h[p->y])sos+=p->z;
        long ans=dinic(vs,vt);
        cout <<sos-ans<<endl;
        return 0;
}
 
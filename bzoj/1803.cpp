//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
const long kMAX_ARRAY=100005;
long n;
long Read(void){
        long r;int ch;
        while(ch=getchar(),!isdigit(ch));
        r=ch-'0';
        while(ch=getchar(),isdigit(ch))r=(r<<3)+(r<<1)+ch-'0';
        return r;
}
 
namespace Ask{
        std::pair<long,long> l[kMAX_ARRAY];
        std::pair<long,std::pair<long,long> >  a[kMAX_ARRAY];
 
        struct Tree{
                long d,s;
        }f[20][kMAX_ARRAY];
        
        void Build(long h,long l,long r){
                if(l==r)return;
                long mid=(l+r)>>1,temp=0;
 
                for(long i=l;i<=r;i++)
                        if(f[h][i].d<=mid){
                                f[h+1][l+temp].d=f[h][i].d;
                                temp++;
                                f[h][i].s=temp;
                        }else{
                                f[h+1][mid+(i-l+1)-temp].d=f[h][i].d;
                                f[h][i].s=temp;
                        }
                Build(h+1,l,mid);
                Build(h+1,mid+1,r);
        }
        
        long Find(long h,long l,long r,long ll,long rr,long k){
                if(ll==rr)return f[h][ll].d;
                long mid=(l+r)>>1,sx=0,sy=0;
                if(ll>l)
                        sx=f[h][ll-1].s;
                sy=f[h][rr].s;
 
                if(sy-sx>=k)
                        return Find(h+1,l,mid,l+sx,l+sy-1,k);
                else
                        return Find(h+1,mid+1,r,mid+(ll-l+1)-sx,mid+(rr-l+1)-sy,k-(sy-sx));
        }
        void Work(void){
                std::sort(a+1,a+n+1);
                for(long i=1;i<=n;i++)
                        f[0][a[i].second.first].d=i;
                
                Build(0,1,n);
                long Q=Read();
                while(Q--){
                        long u=Read(),k=Read();
                        printf("%ld\n",a[Find(0,1,n,l[u].first,l[u].second,k)].second.second);
                }
        }
}
namespace Solve{
        
        struct Edge{
                long y;Edge *next,*opt;bool flag;
                Edge(){}
                Edge(long y,Edge* next):y(y),next(next){flag=true;}
                void* operator new(size_t,void* p){return p;}
        }*e[kMAX_ARRAY],POOL[kMAX_ARRAY<<1],*data=POOL;
 
        long c[kMAX_ARRAY]={0};
        void Input(void){
                n=Read();long *p=c;
                for(long i=1;i<=n;i++)(*(++p))=Read();
                for(long i=1;i<n;i++){
                        long x=Read(),y=Read();
                        e[x] = new ((void*) data++) Edge(y,e[x]);
                        e[y] = new ((void*) data++) Edge(x,e[y]);
                        e[x]->opt = e[y], e[y]->opt=e[x];
                }
        }
        long v=0;
        void Dfs(long u){
                Ask::a[Ask::l[u].first=++v].first=c[u];
                Ask::a[v].second.first=v;
                Ask::a[v].second.second=u;
                for(Edge* p=e[u];p;p=p->next)
                        if(p->flag){
                                p->opt->flag=false;
                                Dfs(p->y);
                        }
                Ask::l[u].second=v;
        }
        void Work(void){
                Input();
                Dfs(1);
                Ask::Work();
        }
        
}
int main(int argc,char** argv){
        #ifdef Debug
                freopen("1.in","r",stdin);
        #endif
        Solve::Work();
        return 0;
}
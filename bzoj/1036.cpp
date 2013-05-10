 
#ifdef Debug
        #include <sys/time.h>
#endif
 
#include <queue>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <algorithm>
const long kMAK_ARRAY=30050;
namespace Segment{
        struct re{
                long left,right;
                long max,sum,ll,rr;
                
                void Build(long l,long r,long *cost);
                long Qsum(long,long);
                long Qmax(long,long);
                void chang(long,long);
                void Updata(void);
        }T[kMAK_ARRAY*20];
        long p=0;
        long re::Qsum(long l,long r){
                        if(l>r)return 0;
                        if(l<=ll&&rr<=r){
                                return sum;
                        }
                        long l1=T[left].Qsum(l,std::min(r,(ll+rr)>>1));
                        long l2=T[right].Qsum(std::max(l,(ll+rr)/2+1),r);
                        return l1+l2;
                }
        long re::Qmax(long l,long r){
                        if(l>r)return -0x6eeeeeee;
                        if(l<=ll&&rr<=r){
                                return max;
                        }
                        long l1=T[left].Qmax(l,std::min(r,(ll+rr)>>1));
                        long l2=T[right].Qmax(std::max(l,(ll+rr)/2+1),r);
                        return std::max(l1,l2);
                }
        void re::chang(long k,long u){
                if(ll==rr){
                        max=sum=u;
                        return;
                }
                long mid=(ll+rr)>>1;
                if(k<=mid)
                        T[left].chang(k,u);
                else
                        T[right].chang(k,u);
                Updata();
        }
        void re::Updata(void){
                        max=std::max(T[left].max,T[right].max);
                        sum=T[left].sum+T[right].sum;
        }
        void re::Build(long l,long r,long *cost){
                        if(l==r){
                                ll=l;rr=r;
                                max=sum=cost[l];
                                return;
                        }
                        long mid=((ll=l)+(rr=r))>>1;
                        
                        left=p++;T[left].Build(l,mid,cost);
                        right=p++;T[right].Build(mid+1,r,cost);
 
                        Updata();
                }
        struct Node{
                long root;
                void Make(long *cost,long size){
                        root=p++;
                        T[root].Build(1,size,cost);
                }
                void Chang(long k,long u){
                        T[root].chang(k,u);
                }
                long GetSum(long l,long r){
                        return T[root].Qsum(l,r);
                }
                long GetMax(long l,long r){
                        return T[root].Qmax(l,r);
                }
        }Tree[kMAK_ARRAY];
}
 
namespace Solve{
        struct Edge{
                long y;Edge* next,*opt;bool flag;
                Edge(){}
                Edge(long y,Edge* next):y(y),next(next){flag=true;}
                void* operator new(size_t,void* p){return p;}
        }*a[kMAK_ARRAY],POOL[kMAK_ARRAY<<1],*data=POOL;
 
        long Read(void){
                long r=0;char ch,cs;
                while(ch=getchar(),!isdigit(ch)&&ch!='-');
                if(ch!='-')r=ch-'0';
                while(cs=getchar(),isdigit(cs))r=(r<<1)+(r<<3)+cs-'0';
                if(ch=='-')return -r;else return r;
        }
        int ReadChar(void){
                int ch;
                while(ch=getchar(),!isupper(ch));
                return getchar();
        }
        long f[20][kMAK_ARRAY]={0};
        struct Node{
                long cost,father,sum,lable,tree_lable,deep,depth;
                Node(){sum=1;father=0;depth=0;}
                Edge *edge;
                long Dfs();
        }node[kMAK_ARRAY];
 
        long Node::Dfs(){
                        for(long i=1;(1<<i)<=depth;i++)
                                f[i][lable]=f[i-1][f[i-1][lable]];
                        long best=0,temp,son=0;
                        for(Edge *p=edge;p;p=p->next)
                                if(p->flag){
                                        p->opt->flag=false;
                                        f[0][p->y]=lable;
                                        node[p->y].depth=depth+1;
                                        temp=node[p->y].Dfs();
                                        sum=sum+temp;
                                        if(temp>best)
                                                best=temp,son=p->y;
                                }
                        if(son){
                                node[son].father=lable;
                                deep=node[son].deep+1;
                        }else deep=1;
                        return sum;
        }
 
        long n;
        void Input(void){
                n=Read();
                for(long i=1;i<n;i++){
                        long x=Read(),y=Read();
                        a[x]=new((void*)data++) Edge(y,a[x]);
                        a[y]=new((void*)data++) Edge(x,a[y]);
                        a[x]->opt=a[y];a[y]->opt=a[x];
                }
                for(long i=1;i<=n;i++){
                        node[i].cost=Read();
                        node[i].edge=a[i];node[i].lable=i;
                }
        }
        
        void Make(void){
                node[1].Dfs();
                node[1].tree_lable=1;
                long d[kMAK_ARRAY]={0},head=1,tail=1;d[1]=1;
                
                while(head<=tail){
                        long now=d[head++];
                        bool flag=true;
                        for(Edge *p=a[now];p;p=p->next)
                                if(p->flag){
                                        d[++tail]=p->y,flag=false;
                                        if(node[p->y].father!=now)
                                                node[p->y].tree_lable=p->y;
                                        else
                                                node[p->y].tree_lable=node[now].tree_lable;
                                }
                        if(flag){
                                long fee[kMAK_ARRAY]={0},*p=fee,t;
                                while(now){
                                        *(++p)=node[now].cost;
                                        t=now;
                                        now=node[now].father;
                                }
                                Segment::Tree[t].Make(fee,node[t].deep);
                        }
                }
        }
        
        inline void GoUp(long &a,long delta){
                for(long i=0;i<=15;i++)
                        if((1<<i) & delta)
                                a=f[i][a];
        }
        long GetFather(long l1,long l2){
                if(node[l1].depth>node[l2].depth)std::swap(l1,l2);
                GoUp(l2,node[l2].depth-node[l1].depth);
 
                if(l1==l2)return l1;
                for(long i=15;i>=0;i--)
                        if(f[i][l1]!=f[i][l2])
                                l1=f[i][l1],l2=f[i][l2];
                return f[0][l1];
        }
        
        long AnswerMax(long u,long v){
                long t=u,limit=node[v].depth,res=-0x6eeeeeee;
                while(true){
                        long tt=node[t].tree_lable;
                        if(node[tt].depth<=limit){
                                long temp=Segment::Tree[tt].GetMax(node[t].deep,node[v].deep);
                                res=std::max(res,temp);
                                return res;
                        }else{
                                long size=node[tt].deep;
                                long temp=Segment::Tree[tt].GetMax(node[t].deep,size);
                                res=std::max(res,temp);
                                t=f[0][node[t].tree_lable];
                        }
                }
        }
        long AnswerSum(long u,long v){
                long t=u,limit=node[v].depth,res=0;
                while(true){
                        long tt=node[t].tree_lable;
                        if(node[tt].depth<=limit){
                                long temp=Segment::Tree[tt].GetSum(node[t].deep,node[v].deep);
                                return res+temp;
                        }else{
                                long size=node[tt].deep;
                                long temp=Segment::Tree[tt].GetSum(node[t].deep,size);
                                res+=temp;
                                t=f[0][node[t].tree_lable];
                        }
                }
        }
        
        void Work(void){
                long Q=Read();
                register long l1,l2,flag;
                while(Q--){
                        flag=ReadChar();l1=Read();l2=Read();
                        if(flag=='M'){
                                long A=GetFather(l1,l2);
                                long ans1=AnswerMax(l1,A);
                                long ans2=AnswerMax(l2,A);
                                printf("%ld\n",std::max(ans1,ans2));
                        }else
                        if(flag=='S'){
                                long A=GetFather(l1,l2);
                                long ans1=AnswerSum(l1,A);
                                long ans2=AnswerSum(l2,A);
                                printf("%ld\n",ans1+ans2-node[A].cost);
                        }else
                        if(flag=='H'){
                                Segment::Tree[node[l1].tree_lable].Chang(node[l1].deep,l2);
                                node[l1].cost=l2;
                        }
                }
        }
        void solve(void){
                Input();
                Make();
                Work();
        }
}
int main(int argc,char** argv){
        #ifdef Debug
                timeval start,end;
                gettimeofday(&start,NULL);
                freopen("1.out","w",stdout);
                freopen("1.in","r",stdin);
                Solve::solve();
        #else
                Solve::solve();
        #endif
 
        #ifdef Debug
                gettimeofday(&end,NULL);
                freopen("2.out","w",stdout);
                printf("%ld\n",1000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec)/1000);
        #endif
        return 0;
}
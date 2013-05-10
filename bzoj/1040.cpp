#include <queue>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve{
        typedef long long Long;
        const Long kMAX_ARRAY=1000005;
        Long Read(void){
                long r;int ch;
                while(ch=getchar(),!isdigit(ch));
                r=ch-'0';
                while(ch=getchar(),isdigit(ch))r=(r<<3)+(r<<1)+ch-'0';
                return r;
        }
 
        long n,c[kMAX_ARRAY]={0},p[kMAX_ARRAY]={0};long out[kMAX_ARRAY]={0};
        void Input(void){
                n=Read();
                for(long i=1;i<=n;i++){
                        c[i]=Read(),p[i]=Read();
                        out[p[i]]++;
                }
        }
        
        struct Tree{
                Long A[2];
                Long operator()(long u) {return A[u];}
                void Make(Long i){A[1]=c[i];}
                void Renew(Tree son){
                        A[0]+=std::max(son(0),son(1));
                        A[1]+=son(0);
                }
        }f[kMAX_ARRAY];
        
        struct Cricle{
                Long A[2][2];
                Cricle(Tree node){memset(A,0,sizeof A);
                        A[1][1]=node(1);
                        A[0][0]=node(0);
                }
                Long operator ()(long i,long j){return A[i][j];}
                void Renew(Tree node){
                        Long ans[2][2]={0};
                        for(Long i=0;i<2;i++){
                                ans[i][0]=std::max(A[i][0],A[i][1])+node(0);
                                ans[i][1]=A[i][0]+node(1);
                        }
                        memcpy(A,ans,sizeof A);
                }
        };
 
        void Work(void){
                std::queue <long> Q;
                for(long i=1;i<=n;i++){
                        f[i].Make(i);
                        if(!out[i])
                                Q.push(i);
                }
                while(Q.size()){
                        long now=Q.front();Q.pop();
                        f[p[now]].Renew(f[now]);
                        if(--out[p[now]]==0)
                                Q.push(p[now]);
                }
                
                Long ans=0;
                for(Long i=1;i<=n;i++)
                        if(out[i]){
                                long now=p[i];
                                Cricle dp(f[i]);
                                while(now!=i){
                                        out[now]=0;
                                        dp.Renew(f[now]);
                                        now=p[now];
                                }
                                ans+=(std::max(std::max(dp(0,1),dp(1,0)),dp(0,0)));
                                out[i]=0;
                        }
                std::cout <<ans<<std::endl;
        }
        void solve(void){
                Input();
                Work();
        }
}
int main(int argc,char** argv){
        #define OJ
        #ifdef OJ
                Solve::solve();
        #else
                freopen("1.in","r",stdin);
                Solve::solve();
        #endif
        return 0;
}
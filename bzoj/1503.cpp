//#define Debug
#include <cstdio>
#include <cctype>
namespace Solve{
        const long kMAX_ARRAY=105000;
 
        long L[kMAX_ARRAY]={0},R[kMAX_ARRAY]={0},S[kMAX_ARRAY]={0},K[kMAX_ARRAY]={0},root=0,sid=0;
        void RR(long &t){
                long k=L[t];L[t]=R[k];R[k]=t;
                S[k]=S[t],S[t]=S[L[t]]+S[R[t]]+1;
                t=k;
        }
        void LL(long &t){
                long k=R[t];R[t]=L[k],L[k]=t;
                S[k]=S[t],S[t]=S[L[t]]+S[R[t]]+1;
                t=k;
        }
        void Maintrain(long &t){
                if(S[L[t]]<S[L[R[t]]]) RR(R[t]), LL(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);else
                if(S[L[t]]<S[R[R[t]]]) LL(t), Maintrain(L[t]), Maintrain(t);else
                if(S[R[t]]<S[R[L[t]]]) LL(L[t]), RR(t), Maintrain(L[t]), Maintrain(R[t]), Maintrain(t);else
                if(S[R[t]]<S[L[L[t]]]) RR(t), Maintrain(R[t]), Maintrain(t);
        }
        void Push(long& t,long x){
                if(!t){
                        K[t=++sid]=x,S[t]=1;
                        L[t]=R[t]=0;
                        return;
                }
                S[t]++;
                if(x<K[t])
                        Push(L[t],x);
                else
                        Push(R[t],x);
                Maintrain(t);
        }
        void Delete(long& t,long x){
                if(!t)return;
                if(K[t]<x)t=R[t],Delete(t,x);
                        else Delete(L[t],x),S[t]=S[L[t]]+S[R[t]]+1;
        }
        long Select(long t,long x){
                if(S[R[t]]+1==x)
                        return K[t];
                else
                        if(x>S[R[t]]+1)return Select(L[t],x-S[R[t]]-1);else return Select(R[t],x);
        }
        long Read(void){
                long r;int ch;
                while(ch=getchar(),!isdigit(ch));
                r=ch-'0';
                while(ch=getchar(),isdigit(ch))r=(r<<3)+(r<<1)+ch-'0';
                return r;
        }
        int ReadChar(void){
                int ch;
                while(ch=getchar(),!isupper(ch));
                return ch;
        }
 
        void solve(void){
                long n=Read(),m=Read(),tot=0,now=0;
                for(long i=1;i<=n;i++){
                        char flag=ReadChar();long u=Read();
                        if(flag=='I')
                                if(u>=m)Push(root,u-now),++tot;
                        if(flag=='A')now+=u;
                        if(flag=='S')now-=u,Delete(root,m-now);
                        if(flag=='F')if(u>S[root])puts("-1");else printf("%ld\n",Select(root,u)+now);
                }
                printf("%ld\n",tot-S[root]);
        }
}
 
int main(int argc,char** argv){
        #ifdef Debug
                freopen("1.in","r",stdin);
                freopen("1.out","w",stdout);
        #endif
        Solve::solve();
        return 0;
}
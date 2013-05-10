 
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
const long kMAX_ARRAY=1050;
const long inf=0x6eeeeeee;
namespace Solve{
        long Read(void){
                int ch;long r=0;
                while(ch=getchar(),!isdigit(ch));
                r=ch-'0';
                while(ch=getchar(),isdigit(ch))r=(r<<1)+(r<<3)+ch-'0';
                return r;
        }
        long n,m,k;
        void Deal(long* a,long* res,bool flag){
                std::pair<long,long> d[kMAX_ARRAY];long head=1,tail=1;
                
                d[1].first=a[1];d[1].second=1;
                for(long i=2;i<=m;i++){
                        while(head<=tail&&i-d[head].second+1>k)head++;
                        while(head<=tail&&(flag^d[tail].first<a[i]))tail--;
 
                        d[++tail].first=a[i],d[tail].second=i;
                        res[i]=d[head].first;
                }
        }
 
        long a[kMAX_ARRAY][kMAX_ARRAY]={0},f[kMAX_ARRAY][kMAX_ARRAY]={0},g[kMAX_ARRAY][kMAX_ARRAY]={0};
        void Input(void){
                n=Read(),m=Read(),k=Read();
                for(long i=1;i<=n;i++)
                        for(long j=1;j<=m;j++)
                                a[i][j]=Read();
                for(long i=1;i<=n;i++)
                        Deal(a[i],f[i],false),Deal(a[i],g[i],true);
                
                long ans=inf;
                for(long j=k;j<=m;j++){
                        std::pair<long,long> Q1[kMAX_ARRAY];long head1=1,tail1=1;
                        std::pair<long,long> Q2[kMAX_ARRAY];long head2=1,tail2=1;
 
                        Q1[1].first=f[1][j];Q2[1].first=g[1][j];
                        Q1[1].second=Q2[1].second=1;
 
                        for(long i=2;i<=n;i++){
                                while(head1<=tail1&&i-Q1[head1].second+1>k)head1++;
                                while(head2<=tail2&&i-Q2[head2].second+1>k)head2++;
 
                                while(head1<=tail1&&Q1[tail1].first<=f[i][j])tail1--;
                                while(head2<=tail2&&Q2[tail2].first>=g[i][j])tail2--;
 
                                Q1[++tail1].first=f[i][j];Q1[tail1].second=i;
                                Q2[++tail2].first=g[i][j];Q2[tail2].second=i;
 
                                if(i>=k)ans=std::min(ans,Q1[head1].first-Q2[head2].first);
                        }
                }
 
                printf("%ld\n",ans);
        }
}
 
int main(int argc,char** argv){
        #ifdef Debug
                freopen("1.in","r",stdin);
        #endif
        Solve::Input();
        return 0;
}
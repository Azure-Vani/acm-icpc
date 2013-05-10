#include <cstdio>
#define lx 10050
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
 
long f[lx]={0},s[lx]={0},n,m;
int main(int argc,char** argv){
        //freopen("1.in","r",stdin);
        scanf("%ld%ld",&n,&m);
        for(long i=1;i<=n;i++){
                scanf("%ld",&s[i]);
                s[i]+=s[i-1];
        }
        for(long i=1;i<=n;i++){
                long temp=0;
                for(long j=i-1;j>=0&&((i-j)>>1)<=m;j--)
                        temp=max(temp,f[j]+s[((i-j)>>1)+j]-s[j]);
                f[i]=temp;
        }
        printf("%ld\n",f[n]);
        return 0;
}
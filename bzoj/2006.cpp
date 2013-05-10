#include <cstdio>
#include <cstring>
#include <cmath>
#define len 530050
#define ma(a,b) ((a)>(b)?(a):(b))
#define swap(i,j) {node c;c=g[i];g[i]=g[j];g[j]=c;}
using namespace std;
 
struct re{
        long da,i;
}f[len][20];
struct node{
        long l,r,k,max,lab;
}g[len];
 
long n,k,l,r,a[len]={0},m;
 
long rmq(long l1,long l2,long &k){
        long u=long(log(double(l2-l1+1))/log(2.0));
        if(f[l1][u].da<f[l2-(1<<u)+1][u].da){
                k=f[l1][u].i;return f[l1][u].da;
        }else{
                k=f[l2-(1<<u)+1][u].i;return f[l2-(1<<u)+1][u].da;
        }
}
 
void insert(long k,long l1,long l2){
        long t=rmq(l1,l2,g[++m].lab);
        g[m].l=l1;g[m].r=l2;g[m].k=k;g[m].max=a[k]-t;
        long i=m;
        while(i>1&&g[i].max>g[i>>1].max){
                swap(i,i>>1);
                i>>=1;
        }
}
 
long pop(long& l1,long& l2,long& t){
        l1=g[1].l;l2=g[1].r;t=g[1].k;
        long r=g[1].max;
        swap(1,m);
        m--;
        long i=1,j=2;
        if(j+1<=m&&g[j+1].max>g[j].max)j++;
        while(i*2<=m&&g[i].max<g[j].max){
                swap(i,j);
                i=j;j=i<<1;
                if(j+1<=m&&g[j+1].max>g[j].max)j++;
        }
        return r;
}
int main(int argc,char** argv){
        scanf("%ld%ld%ld%ld",&n,&k,&l,&r);
        
        long x;
        n++;
        for(long i=2;i<=n;i++)
                scanf("%ld",&x),a[i]=a[i-1]+x,f[i][0].da=a[i],f[i][0].i=i;
        
        long u=(long)(log(double(n))/log(2.0));f[1][0].i=1;
        for(long j=1;j<=u;j++)
                for(long i=1;i+(1<<j)-1<=n;i++)
                        if(f[i][j-1].da<f[i+(1<<(j-1))][j-1].da)
                                f[i][j]=f[i][j-1];
                        else
                                f[i][j]=f[i+(1<<(j-1))][j-1];
                        
        for(long i=l+1;i<=n;i++)
                insert(i,ma(1,i-r),ma(1,i-l));
        
        long long ans=0;
        for(long i=1;i<=k;i++){
                long l1,l2,t,u,h;
                u=pop(l1,l2,t);
                rmq(l1,l2,h);
                ans+=u;
                if(h>l1)
                        insert(t,l1,h-1);
                if(h<l2)
                        insert(t,h+1,l2);
        }
        
        printf("%I64d\n",ans);
        return 0;
}
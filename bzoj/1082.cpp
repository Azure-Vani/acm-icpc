#include <iostream>
#include <cstring>
using namespace std;
long a[60]={0},b[2000]={0},n,m,deep=1,sum=0;
long fim[2000]={0};
void ex(long& a,long& b){
    long c=a;a=b;b=c;
}
int comp(const void* a,const void* b){
    return *(long*)a-*(long*)b;
}
long temp[60]={0};
bool kk=false;
void dfs(long u,long k){
    if(u<=0){
        kk=true;
        return;
    }
    for(long i=1;i<=n;i++){
        if(temp[i]<=0)continue;
        long sum=0;long h=u;
        while(sum<temp[i]&&h>0){sum+=b[h--];}
        if(sum==temp[i]){
            long pp=temp[i];
            temp[i]=0;
            dfs(h,1);
            temp[i]=pp;
            return;
        }
    }
    long j=n;
    while(j>=k){
        if(kk)return;
        if(b[u]<=temp[j]){
            temp[j]-=b[u];
            if(b[u]==b[u-1])
                dfs(u-1,j);
            else 
                dfs(u-1,1);
            temp[j]+=b[u];
        }
        j--;
    }
}
int main(int argc,char** argv){
    cin >>n;
    for(long i=1;i<=n;i++){
        cin >>a[i];
        sum+=a[i];
    }
    memcpy(temp,a,sizeof(long)*(n+1));
    cin >>m;
    for(long j=1;j<=m;j++){
        cin >>b[j];
    }
    qsort(b,m+1,sizeof b[0],comp);
    qsort(a,n+1,sizeof a[0],comp);
    for(long j=1;j<=m;j++)fim[j]=fim[j-1]+b[j];
    for(deep=1;deep<=m;deep+=30){
        memcpy(temp,a,sizeof(long)*(n+1));
        kk=false;
        if(fim[deep]>sum){break;}
        dfs(deep,1);
        if(!kk)break;
    }
    long uuu=deep-30;
    for(deep=uuu;deep<=uuu+30;deep++){
        memcpy(temp,a,sizeof(long)*(n+1));
        kk=false;
        if(fim[deep]>sum){break;}
        dfs(deep,1);
        if(!kk)break;
    }
    if(!kk)
    cout <<deep-1<<endl;
    else cout<<m<<endl;
    return 0;
}
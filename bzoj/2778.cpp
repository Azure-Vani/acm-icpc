#include <fstream>
#include <iostream>
#include <cstdlib>
#define len 1000005
using namespace std;

long a[len]={0},n,k,b[len]={0},l[len]={0},r[len]={0},e[len]={0};
int main(int argc,char** argv){
        cin >>n;
        if(n==1){
                cout <<0<<endl;
                exit(0);
        }
        for(long i=1;i<=n;i++){
                cin >>a[i];
                if(a[i]>a[k]) k=i;
        }
        b[1]=a[k];
        b[0]=1;
        for(long i=k+1;i!=k;i=i+1>n?1:i+1)
                b[++b[0]]=a[i];
        b[0]=0;
        for(long i=n;i>=1;i--){
                long p=i+1;
                while(p<n+1&&b[i]>b[p])
                        p=r[p];
                if(r[i]<n+1&&b[i]==b[p]){
                        e[i]=e[p]+1;
                        p=r[p];
                }
                r[i]=p;
        }
        for(long i=1;i<=n;i++){
                long p=i-1;
                while(p>0&&b[i]>=b[p])
                        p=l[p];
                l[i]=p;
        }
        unsigned long long ans=0;
        for(long i=1;i<=n;i++){
                ans+=e[i];
                if(b[i]==b[1])continue;
	  if(r[i]==n+1&&l[i]==1)
		  ans++;
	else
		ans+=2;
        }
        cout <<ans<<endl;
        return 0;
}
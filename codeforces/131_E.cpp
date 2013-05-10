#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#define len 303
long maxn(long,long,long,long);
using namespace std;
long f[613][len][len];
long a[len][len];
long n;
int main(int argc,char** argv){
	memset(f, -55, sizeof f);
	cin >>n;
	for (int i =1 ; i <= n; i++)
		for (int j = 1; j <= n; j++) cin >>a[i][j];
    f[1][1][1]=a[1][1];
    for(long i=2;i<=n+n-1;i++)
        for(long j=1;j<=i;j++)
            for(long k=1;k<=i;k++){
                f[i][j][k]=maxn(f[i-1][j-1][k],f[i-1][j][k-1],f[i-1][j-1][k-1],f[i-1][j][k]);
                f[i][j][k]+=(j==k?a[j][i+1-j]:(a[j][i+1-j]+a[k][i+1-k]));
                }
    cout <<f[n+n-1][n][n]<<endl;
    return 0;
}
long maxn(long a,long b,long c,long d){
    long t=a;
    t=(t<b?b:t);
    t=(t<c?c:t);
    t=(t<d?d:t);
    return t;
}

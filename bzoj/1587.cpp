#include <iostream>
#include <algorithm>
#define len 1050
#define rep(i,j,m) for(long i=j;i<=m;i++)
#define reep(i,n) for(long i=1;i<=n;i++)
#define inf 0x6eeeeeee
using namespace std;
long f[13][len]={0},n,k,a[len]={0};
int main(int argc,char** argv){
	cin >>n>>k;
	reep(i,n)cin >>a[i],f[1][i]=f[1][i-1]+(a[i]*(i-1));
	long *(c[len]);rep(i,0,n)c[i]=new long[n+2];
	rep(i,0,n)rep(j,0,n)c[i][j]=0;
	reep(i,n)rep(j,i,n)c[i][j]=c[i][j-1]+(a[j]*(j-i));
	rep(p,2,k)rep(i,p,n){f[p][i]=inf;rep(m,p,i)f[p][i]=min(f[p][i],f[p-1][m-1]+c[m][i]);}
	cout <<f[k][n]<<endl;
	return 0;
}

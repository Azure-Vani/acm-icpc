#include <cstring>
#include <iostream>
#include <cstdio>
using namespace std;
const long kMAX=153;
const long kMOD=12345678;
#define max(a,b) ((a)>(b)?(a):(b))
inline void Add(long &a,long b){
	a=(a+b)%kMOD;
}
int main(int argc,char** argv){
	long n,m,k;cin >>n>>m>>k;
	long f[2][kMAX][22][22]={0};long old=1,now=0;
	f[now][0][0][0]=1;
	for(long i=0;i<n+m;i++){
		swap(old,now);
		memset(f[now],0,sizeof f[now]);
		for(long j=0;j<=min(i,n);j++)
			for(long p=0;p<=min(j,k);p++)
				for(long q=0;q<=min(i-j,k);q++){
					long x=f[old][j][p][q];
					if(p<k&&j<n)
						Add(f[now][j+1][p+1][max(q-1,0)],x);
					if(q<k&&i-j<m)
						Add(f[now][j][max(p-1,0)][q+1],x);
				}
	}
	long ans=0;
	for(long i=0;i<=k;i++)for(long j=0;j<=k;j++) Add(ans,f[now][n][i][j]);
	cout <<ans<<endl;
	return 0;
}

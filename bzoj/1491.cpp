#include <fstream>
#include <iostream>
#include <cstdlib>
#define ma 19940522
using namespace std;

int main(int agrc,char** argv){
	ifstream fin("1.in");
	long a[101][101]={0};
	long n,m;
	unsigned long long p[101][101]={0};
	cin >>n>>m;
	for(long i=1;i<=n;i++)
		for(long j=1;j<=n;j++){
			p[i][j]=1;
			if(i!=j)a[i][j]=ma;
			}
	for(long i=1;i<=m;i++){
		long x,y,z;
		cin >>x>>y>>z;
		a[x][y]=z;a[y][x]=z;
	}
	for(long k=1;k<=n;k++)
		for(long i=1;i<=n;i++)
			for(long j=1;j<=n;j++)
				if(i!=j&&j!=k&&k!=i){
					if(a[i][j]>a[i][k]+a[k][j]){
						a[i][j]=a[i][k]+a[k][j];
						p[i][j]=p[i][k]*p[k][j];
					}else if(a[i][j]==a[i][k]+a[k][j])
							p[i][j]+=(p[i][k]*p[k][j]);
				}
	double ans[101]={0};
	for(long k=1;k<=n;k++)
		for(long j=1;j<=n;j++)
			for(long i=1;i<=n;i++)
				if(a[i][j]==a[i][k]+a[k][j]&&i!=j&&j!=k&&k!=i)
					ans[k]+=((double)(p[i][k]*p[k][j])/(double)p[i][j]);
	for(long i=1;i<=n;i++)
		printf("%.3f\n",ans[i]);
	return 0;
}

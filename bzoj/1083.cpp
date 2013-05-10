#include <cstdio>
#include <algorithm>
#define E 90050
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	long x,y,z;
	friend bool operator <(const re& a,const re& b){return a.z<b.z;}
}a[E];
long n,m;
long f[350]={0};
long find(long x){
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}
int main(int argc,char** argv){
	scanf("%ld%ld",&n,&m);
	rep(i,m)scanf("%ld%ld%ld",&a[i].x,&a[i].y,&a[i].z);
	for(long i=1;i<=n;i++)f[i]=i;
	sort(a,a+m+1);
	long ans=0,t=1;
	for(long i=1;t<n;i++)
		if(find(a[i].x)!=find(a[i].y))
			f[find(a[i].x)]=a[i].y,ans=a[i].z,t++;
	printf("%ld %ld\n",n-1,ans);
	return 0;
}

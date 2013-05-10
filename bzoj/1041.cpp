#include <cstdio>
#include <algorithm>
#include <set>
typedef std::pair<long long,long long> ii;
std::set<ii> hash;
long long r;
void cal(long long d){
	long long n=1,m=1,r=::r/d;while(m*m<r)m++;
	while(n<m){
		while(n<m&&n*n+m*m>r)m--;
		if(n>=m)break;
		if(n*n+m*m==r){long long a=m*m-n*n,b=(n*m)<<1;hash.insert(ii(a*d,b*d));hash.insert(ii(b*d,a*d));}
		n++;
	}
}
int main(int argc,char** argv){
	scanf("%lld",&r);
	long long k;
	for(k=1;k*k<r;k++)if(r%k==0)cal(k),cal(r/k);
	if(k*k==r)cal(k);
	printf("%d\n",hash.size()*4+4);
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <cctype>
#define ABS(x) ((x)<0?(-(x)):(x))
long Read(void){
	long r;char ch;
	while(ch=getchar(),!isdigit(ch));
	r=ch-'0';
	while(ch=getchar(),isdigit(ch))r=(r<<1)+(r<<3)+ch-'0';
	return r;
}
const long kMAX=1000050;
int main(int argc,char** argv){
	long n=Read();
	long long *a,s=0;a=new long long[n+3];a[0]=0;long long *p=a+1,*end=a+n+1;
	while(p!=end)s+=(*p++=Read());s/=n;p=a+1;
	while(p!=end)*p++=*(p-1)+*p-s;
	std::sort(a+1,end);
	long long k=a[n>>1],ans=0;p=a+1;
	while(p!=end)ans+=ABS(*p-k),p++;
	printf("%I64d\n",ans);
	return 0;
}

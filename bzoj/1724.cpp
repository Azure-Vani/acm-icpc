#include <cstdio>
#include <cctype>
#include <algorithm>
#define rep(i,n) for(long i=1;i<=n;i++)
#define len 200010
using namespace std;
long head=1,tail=0,v=1;
long d1[len]={0};long long d2[100000]={0};
inline long readT(void){char ch;long r=0;while(ch=getchar(),!isdigit(ch));r=ch-'0';while(ch=getchar(),isdigit(ch))r=r*10+ch-'0';return r;}
inline long min(void){
	long r=0;
	if(d1[v]&&(!d2[head]||d1[v]<d2[head]))
		r=d1[v++];
	else
		r=d2[head++],head=head>100000-5?1:head;
	return r;
}
int main(int argc,char** argv){
	long n;
	n=readT();
	rep(i,n)d1[i]=readT();
	sort(d1,d1+n+1);
	long long ans=0;
	rep(i,n-1){
		long l1=min(),l2=min();
		ans+=(l1+l2);
		tail++;tail=tail>100000-5?1:tail;
		d2[tail]=l1+l2;
	}
	printf("%I64d\n",ans);
	return 0;
}

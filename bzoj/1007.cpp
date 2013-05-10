#include <cstdio>
#include <algorithm>
#define len 50050
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	double k,b;long x;
	friend bool operator <(const re& a,const re& c){if(a.k!=c.k)return a.k<c.k;else return a.b>c.b;}
}a[len];
long n;
int main(int argc,char** argv){
	a[0].k=-0x6eeeeeee;
	scanf("%ld",&n);
	rep(i,n)scanf("%lf%lf",&a[i].k,&a[i].b),a[i].x=i;
	sort(a,a+n+1);
	
	long stack[len]={0},t=0;
	rep(i,n)if(a[i].k!=a[i-1].k){
		while(t>1){
			double x=(a[stack[t-1]].b-a[stack[t]].b)/(a[stack[t]].k-a[stack[t-1]].k);double y=x*a[stack[t]].k+a[stack[t]].b;
			if(a[i].k*x+a[i].b>=y)t--;
				else break;
		}
		stack[++t]=i;
	}
	long ans[len]={0};
	rep(i,t)
		ans[i]=a[stack[i]].x;
	sort(ans,ans+t+1);
	rep(i,t-1)printf("%ld ",ans[i]);printf("%ld\n",ans[t]);
	return 0;
}

#include <cstdio>
#include <cstdlib>
#define len 10051
#define rep(i,k,n) for(long i=k;i<=n;i++)
using namespace std;
long n;int a[len]={0},b[len]={0};
void pp(void){
	printf("0\n");
	exit(0);
}
int main(int argc,char** argv){
	scanf("%ld",&n);
	rep(i,1,n){scanf("%d",&a[i]),b[i]=a[i];if(a[i]>3)pp();};
	long ans=0;
	rep(o,1,2){
		if(o==2)
			a[1]--,a[2]--;
		rep(i,2,n){
			if(a[i]<0)break;
			if(a[i]>0&&a[i-1]>0)
				a[i]--,a[i-1]--,a[i+1]--;
			if(a[i]==0&&a[i-1]>0)break;
		}
		bool bo=false;
		rep(i,1,n){if(a[i]!=0)bo=true;a[i]=b[i];}
		if(!bo)ans++;
	}
	printf("%ld\n",ans);
	return 0;
}

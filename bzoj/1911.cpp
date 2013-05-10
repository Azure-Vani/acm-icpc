#include <cstdio>
#define len 1000010
#define _long long long
using namespace std;

struct {
	_long x,y,d;
}g[len]={0};
_long n,f[len]={0},a,b,c,head,tail,s[len]={0},t;

_long sum(_long l1,_long l2){return a*(s[l2]-s[l1])*(s[l2]-s[l1])+b*(s[l2]-s[l1])+c;}
_long tot(_long l){return f[l]+a*s[l]*s[l]-b*s[l];}

int main(int argc,char** argv){
	//freopen("1.in","r",stdin);
	scanf("%I64d%I64d%I64d%I64d",&n,&a,&b,&c);
	for(_long i=1;i<=n;i++){
		scanf("%I64d",&s[i]);
		s[i]+=s[i-1];
	}
	g[0].x=0;
	g[0].y=0;
	g[0].d=0;head=0;tail=0;
	for(_long i=1;i<=n;i++){
		_long k=(s[i]<<1);
		while(head<tail&&(g[head].x-g[head+1].x<=k*(g[head].y-g[head+1].y)))head++;
		f[i]=f[g[head].d]+sum(g[head].d,i);
		_long x=tot(i),y=a*s[i];
		while(head<tail&&(x-g[tail].x)*(g[tail].y-g[tail-1].y)<=(y-g[tail].y)*(g[tail].x-g[tail-1].x))tail--;
		g[++tail].d=i;
		g[tail].x=x;
		g[tail].y=y;
	}
	printf("%I64d\n",f[n]);
	return 0;
}

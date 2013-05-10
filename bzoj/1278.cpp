#include <cstdio>
#include <algorithm>
#include <cmath>
#define re(i,n) for(int i=1;i<=n;i++)
#define sqr(x,y) ((x)*(x)+(y)*(y))
struct _{long long x, y;double an;}b[200005], a[200005];int n;bool c(const _ a, const _ b){return a.an<b.an;}
int main(){
	scanf("%d",&n);re(i,n)scanf("%lld%lld",&a[i].x, &a[i].y),a[i].an=atan2(a[i].y,a[i].x);
	std::sort(a+1,a+n+1,c); int cnt = 1; b[1] = a[1];
	for (int i = 2; i <= n; i++) if (fabs(a[i].an-a[i-1].an)<=1e-8) b[cnt].x+=a[i].x,b[cnt].y+=a[i].y; else b[++cnt] = a[i];
	long long A=0,sx=0,sy=0,j=1;n = cnt;re(i,n)b[i+n]=b[i];
	re(i,n) {while(j<i+n&&sqr(sx,sy)<=sqr(sx+b[j].x,sy+b[j].y))sx+=b[j].x,sy+=b[j].y,j++;A=std::max(A,sqr(sx,sy));
		sx-=b[i].x,sy-=b[i].y;}
	printf("%lld.000\n",A);
	return 0;
}

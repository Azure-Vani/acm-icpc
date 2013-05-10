#include <fstream>
#include <iostream>
#include <cstdio>
#define len 50005
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
struct re{
	long long x,y;
}yy[len],a[len];
struct G{
	long long l,r,da;
}d[len];
long long n0=0,f[len]={0},n=0;

ifstream fin("1.in");
int comp(const void* a,const void*b){
	return ((re*)b)->y-((re*)a)->y;
}
long long cal(long long l1,long long l2){
	return f[l1-1]+a[l1].y*a[l2].x;
}
long find(long l1,long l2,long k,long u){
	long long l=l1,r=l2;
	while(l<=r){
		long long mid=(l+r)>>1;
		long long sum=cal(u+1,mid),tot=cal(k+1,mid);
		if(sum==tot)return mid;
		if(sum<tot)
			l=mid+1;
		else r=mid-1;
	}
	return l;
}
int main(int argc,char** argv){
	cin >>n;
	for(long i=1;i<=n;i++)
		scanf("%I64d%I64d",&yy[i].x,&yy[i].y);
	qsort(yy,n+1,sizeof yy[0],comp);
	long long p=0;
	for(long i=0;i<n;i++){
		if(yy[i].x>p)
			a[++n0]=yy[i];
		p=max(p,yy[i].x);
	}
	n=n0;
	long t=1;
	d[1].l=1;d[1].r=n;d[1].da=0;
	for(long i=1;i<=n;i++){
		long long temp=t;
		while(i<d[temp].l)temp--;
		long u=d[temp].da;
		f[i]=cal(u+1,i);
		while(t>0&&cal(i+1,d[t].l)<cal(d[t].da+1,d[t].l))t--;
		long long p=find(max(i+1,d[t].l),d[t].r,i,d[t].da);
		if(p>n)continue;
		d[t].r=p-1;
		d[++t].r=n;
		d[t].l=p;
		d[t].da=i;
	}
	cout <<f[n]<<endl;
	return 0;
}

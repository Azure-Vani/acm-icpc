#include <fstream>
#include <iostream>
#include <cstdio>
#define max(a,b) ((a)>(b)?(a):(b))
#define len 1000010
using namespace std;

ifstream fin("1.in");
struct re{
	long l,r,d;
}g[len];
long long x[len]={0},nump[len]={0},c[len]={0},f[len]={0},n=0,sp[len]={0},;
long long sum(long long j,long long i){
	return x[i]*(sp[i]-sp[j])-(nump[i]-nump[j])+c[i];
}
long long t=1;
long long find(long long l1,long long l2,long long k){
	long long l=l1,r=l2;
	long u=g[t].d;
	while(l<=r){
		long long mid=(l+r)>>1;
		long long su=f[u]+sum(u,mid),tot=f[k]+sum(k,mid);
		if(su==tot){while(f[u]+sum(u,mid)==f[k]+sum(k,mid)&&mid<=n)mid++;return mid;}
		if(tot<su)
			r=mid-1;
		else l=mid+1;
	}
	return l;
}
int main(int argc,char** argv){
	//freopen("1.in","r",stdin);
	scanf("%I64d",&n);
	for(long long i=1;i<=n;i++){
		scanf("%I64d%I64d%I64d",&x[i],&sp[i],&c[i]);
		nump[i]=nump[i-1]+x[i]*sp[i];
		sp[i]+=sp[i-1];
	}
	g[1].l=1;g[1].r=n;g[1].d=0;
	for(long long i=1;i<=n;i++){
		long long temp=t;
		while(i<g[temp].l)temp--;
		long long u=g[temp].d;
		f[i]=f[u]+sum(u,i);
		while(i<g[t].l&&f[i]+sum(i,g[t].l)<f[g[t].d]+sum(g[t].d,g[t].l))t--;
		long long p=find(max(i+1,g[t].l),g[t].r,i);
		if(p>n)continue;
		g[t].r=p-1;
		if(g[t].r<g[t].l)t--;
		g[++t].r=n;
		g[t].l=p;g[t].d=i;
	}
	cout <<f[n]<<endl;
	return 0;
}

#include <fstream>
#include <iostream>
#include <cstdio>
#define len 100002
#define sqr(q) ((q)*(q))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;

struct re{
	unsigned long long l,r,d;
}g[len]={0};
unsigned long long f[len]={0},s[len]={0},n,l;

unsigned long long c(unsigned long long a,unsigned long long b){
	return sqr(b-a-1+s[b]-s[a]-l);
}
ifstream fin("toy.in");
ofstream fout("toy.out");
long find(long l1,long l2,long k,unsigned long long i){
	long l=l1,r=l2;
	while(l<=r){
		long long mid=(l+r)>>1;
		unsigned long long x=f[k]+c(k,mid),sum=f[i]+c(i,mid);
		if(x==sum){while((x=c(k,mid))==(sum=c(i,mid)))mid++;return mid;}
		if(x<sum)r=mid-1;
			else l=mid+1;
	}
	return l;
}
int main(int argc,char** argv){
	cin >>n>>l;
	for(unsigned long i=1;i<=n;i++){
		scanf("%I64d",&s[i]);
		s[i]+=s[i-1];
	}
	unsigned long long t=0,temp=0;
	g[0].l=1;g[0].r=n;
	for(unsigned long long i=1;i<=n;i++){
		while(i>g[temp].r)
			temp++;
		unsigned long long u=g[temp].d;
		f[i]=f[u]+c(u,i);
		while(f[g[t].d]+c(g[t].d,g[t].l)>f[i]+c(i,g[t].l)&&t>0)
			t--;
		unsigned long long p=find(max(g[t].l,i+1),g[t].r,i,g[t].d);
		g[t].r=p-1;
 		if(p>n)continue;
		g[++t].l=p;g[t].r=n;g[t].d=i;
	}
	cout <<f[n]<<endl;
	return 0;
}

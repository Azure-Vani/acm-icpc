#include <cstdio>
#include <cstring>

#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))
#define add(u,v,c) a[u]=new((void*)data++)re(u,v,c,a[u]);
#define ex(a,b) {long c=a;a=b;b=c;}
#define len 604
#define V (len*len)
#define E (V*4)

using namespace std;

struct re{
	long x,y,z;
	re* next;
	re(){}
	re(long x,long y,long z,re* next):x(x),y(y),z(z),next(next){}
	void* operator new(size_t,void* p){return p;}
}GG[E<<1],*data=GG,*a[V];

long dis[V];
long n,s,t;

class Heap{
	private:
		long *fim;
		long l;
		long *a;long *home;
		void swap(long i,long j){
			ex(fim[home[i]],fim[home[j]]);
			ex(home[i],home[j]);
			ex(a[i],a[j]);
		}
	public:
		Heap(){
			fim=new long[V];a=new long[V];home=new long[V];
			l=n+1,a[1]=0,fim[0]=1;home[1]=0;
			for(long i=1;i<=n;i++)
				a[i+1]=dis[i],fim[i]=i+1,home[i+1]=i;
		}
		void change(long u){
			a[fim[u]]=dis[u];
			
			long i=fim[u];
			while(i>1&&a[i]<a[i>>1])
				swap(i,i>>1),i>>=1;
			
			i=fim[u];long j;if(i*2<=l)
			j=(i*2+1>l||a[i<<1]<a[i*2+1])?i*2:i*2+1;
			while(i*2<=l&&a[i]>a[j]){
				swap(i,j),i=j;if(i*2<=l)j=(a[i<<1]<a[i*2+1]||i*2+1>l)?i*2:i*2+1;
			}
		}
		long pop(void){
			long r=home[1];
			swap(1,l);l--;
			
			long i=1;long j;if(i*2<=l)
			j=(i*2+1>l||a[i<<1]<a[i*2+1])?i*2:i*2+1;
			while(i*2<=l&&a[i]>a[j]){
				swap(i,j),i=j;if(i*2<=l)j=(a[i<<1]<a[i*2+1]||i*2+1>l)?i*2:i*2+1;
			}
			return r;
		}
};

long Dijkstra(long s,long t){
	
	for(long i=1;i<=n;i++)dis[i]=0x6eeeeeee;
	dis[0]=0;
	Heap list;
	
	for(long i=0;i<=n;i++){
		if(i==61214)
			i=61214;
		long k=list.pop();
		for(re* p=a[k];p;p=p->next)
			if(dis[p->y]>dis[k]+p->z){
				dis[p->y]=dis[k]+p->z;
				list.change(p->y);
			}
	}
	
	return dis[t];
}

int main(int argc,char** argv){
	
	scanf("%ld",&n);
	s=0;t=n*n+1;
	
	for(long i=0;i<=n;i++)
		for(long j=1;j<=n;j++){
			long c;
			scanf("%ld",&c);
			long u,v;
			u=(i-1)*n+j;
			v=u+n;
			if(i==0)u=t;
			if(i==n)v=s;
			add(v,u,c);
		}
	for(long i=0;i<n;i++)
		for(long j=0;j<=n;j++){
			long c;
			scanf("%ld",&c);
			long u,v;
			u=i*n+j;
			v=u+1;
			if(j==0)u=s;
			if(j==n)v=t;
			add(u,v,c);
		}
	for(long i=0;i<=n;i++)
		for(long j=1;j<=n;j++){
			long c;
			scanf("%ld",&c);
			long u,v;
			u=(i-1)*n+j;
			v=u+n;
			if(i==0)u=t;
			if(i==n)v=s;
			add(u,v,c);
		}
	for(long i=0;i<n;i++)
		for(long j=0;j<=n;j++){
			long c;
			scanf("%ld",&c);
			long u,v;
			u=i*n+j;
			v=u+1;
			if(j==0)u=s;
			if(j==n)v=t;
			add(v,u,c);
		}
	n=n*n+1;
	long ans=Dijkstra(s,t);
	printf("%ld\n",ans);
	return 0;
}

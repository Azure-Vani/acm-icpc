#include <iostream>
#include <queue>
#include <cstdio>
#include <cctype>
#define len 1003
#define min(a,b) ((a)<(b)?(a):(b))
#define V (len*len*2)
#define E V*4
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	long y,z;re* next;
	re(){}
	re(long y,long z,re* next):y(y),z(z),next(next){}
	void* operator new(size_t,void* p){return p;}
}G[E],*data=G,*a[V];
struct node{
	long k,d;
	node(long k,long d):k(k),d(d){}
	friend bool operator <(const node& a,const node& b){return a.d>b.d;}
};
inline void add(long u,long v,long z){a[u]=new((void*)data++)re(v,z,a[u]);a[v]=new((void*)data++) re(u,z,a[v]);}

long Dijkstra(long s,long t){
	long *dis=new long[V];
	rep(i,t)dis[i]=0x5eeeeeee;dis[s]=0;
	priority_queue<node> heap;heap.push(node(s,0));
	
	while(heap.size()){
		node t=heap.top();heap.pop();if(t.d>dis[t.k])continue;dis[t.k]=t.d;
		for(re* p=a[t.k];p;p=p->next)if(dis[p->y]>dis[t.k]+p->z){
			dis[p->y]=dis[t.k]+p->z;heap.push(node(p->y,dis[p->y]));}
	}
	return dis[t];
}
void papapa(long x){long r=0x6eeeeeee,t;rep(i,x-1)scanf("%ld",&t),r=min(t,r);printf("%ld\n",r);exit(0);}
void readT(long& x){char c;while((c=getchar())==' '||c=='\n');long r=c-'0';while((c=getchar())>='0'&&c<='9')r=r*10+c-'0';x=r;}
int main(int argc,char** argv){
	long n,m,vs,vt;
	readT(n);readT(m);
	if(n==1||m==1){long x=n==1?m:n;papapa(x);}
	n--,m--;
	vs=n*m*2+1;vt=vs+1;long x,u,v;
	rep(i,n+1)rep(j,m){readT(x);if(i==1)u=vt,v=j*2;else if(i==n+1)u=vs,v=((i-2)*m+j)*2-1; else u=((i-1)*m+j)*2,v=u-m*2-1;add(u,v,x);}
	rep(i,n)rep(j,m+1){readT(x);if(j==1)u=vs,v=((i-1)*m+1)*2-1;else if(j==m+1)u=vt,v=i*m*2;else u=((i-1)*m+j-1)*2,v=u+1;add(u,v,x);}
	rep(i,n)rep(j,m){readT(x);add(((i-1)*m+j)*2,((i-1)*m+j)*2-1,x);}
	long ans=Dijkstra(vs,vt);
	printf("%ld\n",ans);
	return 0;
}

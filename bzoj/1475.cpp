#include <cstdio>
#include <cstring>

#define min(a,b) ((a)<(b)?(a):(b))

#define len 402
#define V (len*len)
#define E (V*5)
#define mm 0x6eeeeeee

#define add(u,v,c) {a[u]=new((void*)data++)re(u,v,c,a[u]);a[v]=new((void*)data++)re(v,u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
using namespace std;
struct re{
        long x,y,z;
        re *next,*opt;
        re(){}
        re(long x,long y,long z,re* next):x(x),y(y),z(z),next(next){}
        void* operator new(size_t,void* p){return p;}
}G[E<<1],*a[V],*pre[V],*c[V],*data=G;
 
long n,m,dis[V]={0},g[V]={0},begin,end,sum=0;
 
void bfs(long s,long t){
	for(long i=1;i<=n;i++)
		c[i]=a[i],dis[i]=n;
	
	long d[V]={0},head=1,tail=1;
	d[1]=t;dis[t]=0;
	
	while(head<=tail){
		long now=d[head++];
		for(re* p=a[now];p;p=p->next)
			if(dis[p->y]==n&&(p->opt)->z)
				g[dis[d[++tail]=p->y]=dis[now]+1]++;
		}
}

long SAP(long s,long t){
	bfs(s,t);
	
	long r=0,x=s;
	while(dis[s]<n){
		while(c[x]&&(!c[x]->z||dis[c[x]->y]+1!=dis[x]))
			c[x]=c[x]->next;
		if(c[x]){
			pre[c[x]->y]=c[x]->opt;
			x=c[x]->y;
			if(x==t){
				long u=mm;
				for(re* p=pre[t];p;p=pre[p->y])
					u=min(u,(p->opt)->z);
				for(re* p=pre[t];p;p=pre[p->y])
					p->z+=u,(p->opt)->z-=u;
				r+=u,x=s;
			}
		}else{
			long temp=dis[x];
			g[temp]--;
			dis[x]=n;
			for(re* p=c[x]=a[x];p;p=p->next)
				if(p->z)
					dis[x]=min(dis[x],dis[p->y]+1);
			g[dis[x]]++;
			if(!g[temp])break;
			if(x!=s)x=pre[x]->y;
		}
	}
	return r;
}

 
int main(int argc,char** argv){
	scanf("%ld",&n);
	begin=0;end=n*n+1;
	long c;
	for(long i=1;i<=n;i++)
		for(long j=1;j<=n;j++){
			scanf("%ld",&c);
			sum+=c;
			long lab=(i-1)*n+j;
			if((i+j)&1){
				add(begin,lab,c);
				if(i>1)
					add(lab,lab-n,mm);
				if(i<n)
					add(lab,lab+n,mm);
				if(j>1)
					add(lab,lab-1,mm);
				if(j<n)
					add(lab,lab+1,mm);
			}
			else
				add(lab,end,c);
		}
	n=n*n+1;
	long ans=sum-SAP(begin,end);
	printf("%ld\n",ans);
    return 0;
}
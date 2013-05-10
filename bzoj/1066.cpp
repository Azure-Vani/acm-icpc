#include <iostream>
#include <fstream>
#include <cmath>
#define len 25
#define V len*len*2+10
#define inf 0x6eeeeeee
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	long y,z;re *next,*opt;re(long y,long z,re* next):y(y),z(z),next(next){}
}*a[V];
long n,m,d,f=0;
void add(long u,long v,long c){a[u]=new re(v,c,a[u]);a[v]=new re(u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
inline long inp(long i,long j){return ((i-1)*m+j)*2-1;}
inline long oup(long i,long j){return inp(i,j)+1;}
inline long dis(long i,long j,long x,long y){return abs(i-x)+abs(j-y);}
long level[V]={0},vs,vt;
bool bfs(long vs,long vt){
	memset(level,-1,sizeof level);long d[V]={0},head=1,tail=1;level[d[1]=vs]=0;
	while(head<=tail)for(re* p=a[d[head++]];p;p=p->next)
		if(level[p->y]==-1&&p->z)level[d[++tail]=p->y]=level[d[head-1]]+1;
	return level[vt]!=-1;
}
long extend(long u,long sum){
	if(u==vt)return sum;
	long t,r=0;
	for(re* p=a[u];p&&r<sum;p=p->next)if(level[p->y]==level[u]+1&&p->z){
			t=p->z;if(t>sum-r)t=sum-r;t=extend(p->y,t);p->z-=t,(p->opt)->z+=t,r+=t;
		}
	if(!r)level[u]=-1;return r;
}
long dinic(long vs,long vt){long r=0,t;while(bfs(vs,vt))while(t=extend(vs,0x6eeeeeee))r+=t;return r;}
int main(int argc,char** argv){
	cin >>n>>m>>d;char x;vs=n*m*2+1,vt=vs+2;
	rep(i,n)rep(j,m){cin >>x;if(x-'0')add(inp(i,j),oup(i,j),x-'0');}
	rep(i,n)rep(j,m){cin >>x;if(x!='.')f++,add(vs,inp(i,j),1);}
	rep(i,n)rep(j,m)rep(l1,n)rep(l2,m)if(dis(i,j,l1,l2)<=d)add(oup(i,j),inp(l1,l2),inf);
	rep(i,n)rep(j,m)if(i<=d||j<=d||n-i+1<=d||m-j+1<=d)add(oup(i,j),vt,inf);
	long ans=dinic(vs,vt);
	cout <<f-ans<<endl;
	return 0;
}

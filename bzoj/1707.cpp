#include <iostream>
#include <cstring>
#define len 5050
#define inf 0x6eeeeeee
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	long y,z;re *next,*opt;
	re(long y,long z,re* next):y(y),z(z),next(next){};
}*a[len];
inline void add(long u,long v,long c){a[u]=new re(v,c,a[u]);a[v]=new re(u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
long n,m,level[len]={0},vs,vt;
bool bfs(long s,long t){
	memset(level,-1,sizeof level);
	level[s]=0;long d[len]={0},tail=1,head=1;
	d[1]=s;
	while(head<=tail){
		long now=d[head++];
		for(re* p=a[now];p;p=p->next)
			if(p->z&&level[p->y]==-1)level[d[++tail]=p->y]=level[now]+1;
			}
	return level[t]!=-1;
}
long extend(long u,long sum){
	if(u==vt)return sum;
	long r=0,t=0;
	for(re* p=a[u];p&&r<sum;p=p->next)
		if(p->z&&level[p->y]==level[u]+1){
			t=p->z;if(t>sum-r)t=sum-r;
			t=extend(p->y,t);
			p->z-=t;(p->opt)->z+=t;r+=t;
		}
	if(!r)level[u]=-1;
	return r;
}
long dinic(long s,long tt){
	long r=0,t;
	while(bfs(s,tt))
		while(t=extend(s,inf))r+=t;
	return r;
}
int main(int argc,char** argv){
	pair<long,long> d[len];long u,c;
	cin >>n>>m;
	vs=n+m+1,vt=n+m+2;
	rep(i,n){cin >>d[i].first>>d[i].second;add(vs,i,1);}
	rep(i,m){cin >>u>>c;add(i+n,vt,c);rep(j,n)if(u>=d[j].first&&u<=d[j].second)add(j,i+n,1);}
	long ans=dinic(vs,vt);
	cout <<ans<<endl;
	return 0;
}

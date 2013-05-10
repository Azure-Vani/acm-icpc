#include <iostream>
#include <fstream>
#define len 500
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
struct re{
	long y,z;re* next,*opt;
	re(long y,long z,re* next):y(y),z(z),next(next){}
}*a[len];
long n,n1,n2,vs,vt,level[len]={0};
inline void add(long u,long v){a[u]=new re(v,1,a[u]);a[v]=new re(u,0,a[v]);a[u]->opt=a[v];a[v]->opt=a[u];}
bool bfs(long s,long t){
	memset(level,-1,sizeof level);
	long d[len]={0},head=1,tail=1;
	d[1]=s;level[s]=0;
	while(head<=tail){
		long now=d[head++];
		for(re* p=a[now];p;p=p->next)
			if(p->z&&level[p->y]==-1)
				level[d[++tail]=p->y]=level[now]+1;
		}
	return level[t]!=-1;
}
long extend(long u,long sum){
	if(u==vt)return sum;
	long r=0,t=0;
	for(re* p=a[u];p&&r<sum;p=p->next)
		if(level[u]==level[p->y]-1&&p->z){
			t=p->z;
			if(t>sum-r)t=sum-r;
			t=extend(p->y,t);
			p->z-=t;(p->opt)->z+=t;r+=t;
		}
	if(!r)level[u]=-1;
	return r;
}
long dinic(long s,long t){
	long r=0,tt;
	while(bfs(s,t))
		while(tt=extend(s,0x6eeeeeee))r+=tt;
	return r;
}
int main(int argc,char** argv){
	cin >>n>>n1>>n2;long l1,l2,u;
	vs=2*n+n1+n2+1;vt=vs+1;
	rep(i,n){cin >>l1>>l2;add(i+n1,i+n1+n+n2);rep(j,l1)cin >>u,add(u,i+n1);rep(j,l2)cin >>u,add(i+n1+n+n2,u+n1+n);}
	rep(i,n1)add(vs,i);rep(i,n2)add(i+n1+n,vt);
	long ans=dinic(vs,vt);
	cout <<ans<<endl;
	return 0;
}

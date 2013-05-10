#include <cstdio>
#include <cctype>
namespace Solve{
	const long kMAX_ARRAY=200005;
	struct Edge{
		long y;Edge* next;
		Edge(){}
		Edge(long y,Edge* next):y(y),next(next){}
		void* operator  new(size_t,void* p){return p;}
	}*a[kMAX_ARRAY],POOL[kMAX_ARRAY],*data=POOL;
	struct Party{
		long y;Party* next;
		Party(){}
		Party(long y,Party* next):y(y),next(next){}
		void* operator  new(size_t,void* p){return p;}
	}*p[kMAX_ARRAY<<1],pPOOL[kMAX_ARRAY<<1],*temp=pPOOL;

	long Read(void){
		long r;int ch;
		while(ch=getchar(),!isdigit(ch));
		r=ch-'0';
		while(ch=getchar(),isdigit(ch))r=(r<<3)+(r<<1)+ch-'0';
		return r;
	}

	long n,k,party[kMAX_ARRAY]={0},root=0;long deep[kMAX_ARRAY]={0};
	void Input(void){
		n=Read(),k=Read();
		for(long i=1;i<=n;i++){
			long ki=Read(),pi=Read();
			party[i]=ki;
			p[ki]=new((void*)temp++) Party(i,p[ki]);
			if(pi)
				a[pi]=new((void*)data++) Edge(i,a[pi]);
			else root=i;
		}
		deep[root]=0;
	}

	long f[19][kMAX_ARRAY]={0},son[kMAX_ARRAY<<1]={0};
	void Dfs(){
		long d[kMAX_ARRAY]={0},head=1,tail=1;d[1]=root;
		while(head<=tail){
			long u=d[head++];
			for(long i=1;(1<<i)<=deep[u];i++)
				f[i][u]=f[i-1][f[i-1][u]];

			for(Edge* p=a[u];p;p=p->next){
				deep[p->y]=deep[u]+1;
				f[0][p->y]=u;
				d[++tail]=p->y;
			}
			if(deep[u]>deep[son[party[u]]])
				son[party[u]]=u;
		}
	}
	
	void GoUp(long& a,long delta){
		for(long i=0;i<=18;i++)
			if(delta & (1<<i))
				a=f[i][a];
	}
	long GetFather(long a,long b){
		if(deep[a]>deep[b]){long c=a;a=b;b=c;}
		GoUp(b,deep[b]-deep[a]);

		if(a==b)return a;
		for(long i=18;i>=0;i--)
			if(f[i][a]!=f[i][b])
				a=f[i][a],b=f[i][b];
		return f[0][a];
	}

	void Work(void){
		for(long i=1;i<=k;i++){
			long x=son[i],ans=0;
			for(Party* point=p[i];point;point=point->next){
				long y=point->y;
				long t=GetFather(x,y);
				if(deep[x]+deep[y]-(deep[t]<<1)>ans)
					ans=deep[x]+deep[y]-(deep[t]<<1);
			}
			if(i!=k)printf("%ld\n",ans);else printf("%ld",ans);
		}
	}
	void solve(void){
		Input();
		Dfs();
		Work();
	}
}
int main(int argc,char** argv){
	#define OJ
	#ifdef OJ
		Solve::solve();
	#else
		freopen("1.in","r",stdin);
		Solve::solve();
	#endif
	return 0;
}

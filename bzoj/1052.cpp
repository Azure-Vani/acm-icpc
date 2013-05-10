#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
namespace Solve{
	const long kMAX_ARRAY=21005;
	const long inf=0x7fffffff;

	struct pair{
		long x,y;
	}a[kMAX_ARRAY];
	long n;

	#define MAX(a,b) ((a)>(b)?(a):(b))
	#define MIN(a,b) ((a)<(b)?(a):(b))
	long maxx=-inf,maxy=-inf,minx=inf,miny=inf;
	void Input(void){
		scanf("%ld",&n);
		long x,y;
		for(long i=1;i<=n;i++){
			scanf("%ld%ld",&x,&y);
			a[i].x=x;a[i].y=y;
			maxx=MAX(maxx,x);minx=MIN(minx,x);
			maxy=MAX(maxy,y);miny=MIN(miny,y);
		}
	}
	
	int hash[kMAX_ARRAY]={0};

	bool Check(long l,long deep){
		std::pair<long,long> mode[4];

		mode[0].first=mode[0].second=inf;
		mode[3].first=mode[3].second=-inf;
		bool flag=false;
		for(long i=1;i<=n;i++)
			if(!hash[i]){
				flag=true;
				mode[0].first=MIN(a[i].x,mode[0].first);
				mode[3].first=MAX(a[i].x,mode[3].first);
				mode[0].second=MIN(a[i].y,mode[0].second);
				mode[3].second=MAX(a[i].y,mode[3].second);
		}
		mode[1].first=mode[0].first;
		mode[2].first=mode[3].first;
		mode[1].second=mode[3].second;
		mode[2].second=mode[0].second;

		if(deep==3){
			if(!flag||(mode[3].first-mode[0].first<=l&&mode[3].second-mode[0].second<=l))
				return true;
			else
				return false;
		}else{
			for(long i=0;i<4;i++){
				long x=mode[i].first,y=mode[i].second;
				for(long i=1;i<=n;i++)
					if(!hash[i])
						if(abs(a[i].x-x)<=l&&abs(a[i].y-y)<=l)
							hash[i]=deep;
				if(Check(l,deep+1))
					return true;
				for(long i=1;i<=n;i++)
					if(hash[i]==deep)
						hash[i]=0;
			}
		}
		return false;
	}
				
	void Work(void){
		long r=MAX(maxx-minx,maxy-miny),l=0;
		while(l<=r){
			long mid=(l+r)>>1;
			if(Check(mid,1))
				r=mid-1;
			else
				l=mid+1;
			memset(hash,0,sizeof(hash[0])*(n+1));
		}
		printf("%ld\n",l);
	}
	void solve(void){
		Input();
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

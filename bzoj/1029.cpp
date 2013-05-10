#include <queue>
#include <algorithm>
#include <cstdio>
#include <cctype>
namespace Solve{
	const long kMAX_ARRAY=150050;
	long Read(void){
		long r;int ch;
		while(ch=getchar(),!isdigit(ch));
		r=ch-'0';
		while(ch=getchar(),isdigit(ch))r=(r<<1)+(r<<3)+ch-'0';
		return r;
	}
	typedef std::pair<long,long> pair;
	pair a[kMAX_ARRAY];
	bool comp(pair a,pair b){
		if(a.second==b.second)
			return a.first<b.first;
		else return a.second<b.second;
	}

	long n;
	void Input(void){
		n=Read();
		for(long i=1;i<=n;i++)
			a[i].first=Read(),a[i].second=Read();
	}

	void Work(void){
		std::sort(a+1,a+n+1,comp);
		std::priority_queue<pair> Q;
		long now=a[1].first;Q.push(a[1]);
		for(long i=2;i<=n;i++){
			if(now+a[i].first<=a[i].second)Q.push(a[i]),now+=a[i].first;
			else if(a[i].first<=Q.top().first){
				long temp=Q.top().first;Q.pop();
				Q.push(a[i]);
				now+=(a[i].first-temp);
			}
		}
		printf("%ld\n",long(Q.size()));
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

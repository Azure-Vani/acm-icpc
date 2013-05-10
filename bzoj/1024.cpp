#include <iostream>
#include <cstdio>
#include <algorithm>
namespace Solve{
	double x,y;long k;
	double Cut(double x,double y,long q){
		if(x>y)std::swap(x,y);
		if(q==1)return y/x;
		double ret=1e20,t=1.0/q;
		for(long i=1;i<q;i++){
			ret=std::min(ret,std::max(Cut(x*i*t,y,i),Cut(x-x*i*t,y,q-i)));
			ret=std::min(ret,std::max(Cut(x,y*i*t,i),Cut(x,y-y*i*t,q-i)));
		}
		return ret;
	}
	void solve(){
		scanf("%lf %lf %ld",&x,&y,&k);
		printf("%.6lf\n",Cut(x,y,k));
	}
}
int main(int argc,char** argv){
	#define OJ
	#ifdef OJ
		Solve::solve();
	#else
		freopen("1.in","t",stdin);
		Solve::solve();
	#endif
	return 0;
}

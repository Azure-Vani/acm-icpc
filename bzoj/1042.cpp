#include <cstdio>
#include <iostream>
const long kMAX=100050;
long long f[kMAX]={0};
inline long long F(long x){
	if(x<0)return 0;else return f[x];
}
int main(int argc,char** argv){
	long c[5]={0},tot;
	for(long i=1;i<=4;i++)scanf("%ld",&c[i]);scanf("%ld",&tot);

	f[0]=1;
	for(long i=1;i<=4;i++)
		for(long j=c[i];j<=kMAX;j++)
			f[j]=f[j]+f[j-c[i]];

	while(tot--){
		long d[5],s;for(long i=1;i<=4;i++)scanf("%ld",d+i),d[i]++;scanf("%ld",&s);
		long long ans=f[s];

		for(long i=1;i<=4;i++)ans-=F(s-d[i]*c[i]);

		for(long i=1;i<=4;i++)
			for(long j=i+1;j<=4;j++)
				ans+=F(s-d[i]*c[i]-d[j]*c[j]);

		for(long i=1;i<=4;i++)
			for(long j=i+1;j<=4;j++)
				for(long k=j+1;k<=4;k++)
					ans-=F(s-d[i]*c[i]-d[j]*c[j]-d[k]*c[k]);

		ans+=F(s-d[1]*c[1]-d[2]*c[2]-d[3]*c[3]-d[4]*c[4]);
		std::cout <<ans<<std::endl;
	}
	return 0;
}

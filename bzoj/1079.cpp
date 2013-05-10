#include <cstdio>
#include <iostream>
namespace Solve{
	const long kMOD=1000000007;
	long n,hash[6]={0};
	long long f[17][17][17][17][17][6]={0};
	void Input(void){
		scanf("%ld",&n);
		long u;
		for(long i=1;i<=n;i++)
			scanf("%ld",&u),hash[u]++;
	}
	void Work(void){
		f[hash[1]][hash[2]][hash[3]][hash[4]][hash[5]][0]=1;
		for(long l5=hash[5];l5>=0;l5--)
			for(long l4=hash[5]+hash[4];l4>=0;l4--)
				for(long l3=hash[5]+hash[4]+hash[3];l3>=0;l3--)
					for(long l2=hash[5]+hash[4]+hash[3]+hash[2];l2>=0;l2--)
						for(long l1=hash[5]+hash[4]+hash[3]+hash[2]+hash[1];l1>=0;l1--){
							if(l5>0){
								for(long i=0;i<5;i++)
									f[l1][l2][l3][l4+1][l5-1][4]+=(f[l1][l2][l3][l4][l5][i]*l5);
								f[l1][l2][l3][l4+1][l5-1][4]%=kMOD;
							}
							if(l4>0){
								for(long i=0;i<5;i++)
									f[l1][l2][l3+1][l4-1][l5][3]+=(f[l1][l2][l3][l4][l5][i]*(i==4?(l4-1):l4));
								f[l1][l2][l3+1][l4-1][l5][3]%=kMOD;
							}
							if(l3>0){
								for(long i=0;i<5;i++)
									f[l1][l2+1][l3-1][l4][l5][2]+=(f[l1][l2][l3][l4][l5][i]*(i==3?(l3-1):l3));
								f[l1][l2+1][l3-1][l4][l5][2]%=kMOD;
							}
							if(l2>0){
								for(long i=0;i<5;i++)
									f[l1+1][l2-1][l3][l4][l5][1]+=(f[l1][l2][l3][l4][l5][i]*(i==2?(l2-1):l2));
								f[l1+1][l2-1][l3][l4][l5][1]%=kMOD;
							}
							if(l1>0){
								for(long i=0;i<5;i++)
									f[l1-1][l2][l3][l4][l5][0]+=(f[l1][l2][l3][l4][l5][i]*(i==1?(l1-1):l1));
								f[l1-1][l2][l3][l4][l5][0]%=kMOD;
							}
						}
		std::cout <<f[0][0][0][0][0][0]<<std::endl;
	}
	void solve(void){
		Input();
		Work();
	}

}
int main(int argc,char** argv){
	#define OJ true
	#ifdef OJ 
		Solve::solve();
	#else
		freopen("1.in","r",stdin);
		Solve::solve();
	#endif
	return 0;
}

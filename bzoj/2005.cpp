#include <iostream>
#include <fstream>
#define len 100100
#define min(a,b) ((a)<(b)?(a):(b))
#define l_ong long long
using namespace std;

l_ong n,m,f[len]={0};
l_ong ans=0;
int main(int argc,char** argv){
	cin >>n>>m;
	for(l_ong i=min(n,m);i>=1;i--){
		l_ong s=(n/i)*(m/i);
		for(l_ong j=2;j*i<=min(n,m);j++)
			s-=f[j*i];
		f[i]=s;
		ans+=(f[i]*i); 
	}
	cout <<ans*2-n*m<<endl;
	return 0;
}

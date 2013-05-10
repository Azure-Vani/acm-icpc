#include <iostream>
#define len 10050
using namespace std;
long n,m;long long f[len]={0};
int main(int argc,char** argv){
	cin >>n>>m;
	f[0]=1;
	for(long i=1;i<=n;i++){
		long v;
		cin >>v;
		for(long j=v;j<=m;j++)
			f[j]+=f[j-v];
	}
	cout <<f[m]<<endl;
	return 0;
}

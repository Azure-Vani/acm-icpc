#include <iostream>
#define len 13000
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
int main(int argc,char** argv){
	long n,m,f[13000]={0};
	cin >>n>>m;
	for(long i=1;i<=n;i++){
		long w,v;
		cin >>w>>v;
		for(long j=m;j>=w;j--)
			f[j]=max(f[j],f[j-w]+v);
	}
	cout <<f[m]<<endl;
	return 0;
}

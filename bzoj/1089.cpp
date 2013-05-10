#include <iostream>
#include <cstring>
#define len 20
#define MM 1000
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
void go(long *a){
	long temp=1;
	while(temp<a[0]||a[temp]>MM)
		a[temp+1]+=(a[temp]/MM),a[temp]%=MM,temp++;
	a[0]=temp;
}
void pluss(long *a){
	a[1]++;
	go(a);
}
void mult(long *a,long *b){
	long c[200]={0};
	rep(i,a[0])rep(j,b[0])c[i+j-1]+=a[i]*b[j];
	c[0]=a[0]+b[0]-1;
	go(c);
	memcpy(a,c,sizeof c);
}
void JJ(long *a,long *b){
	rep(i,a[0])a[i]-=b[i];
	long temp=a[0];
	rep(i,a[0])if(a[i]<0)a[i]+=MM,a[i+1]--;
	while(temp>0&&a[temp]==0)temp--;
	a[0]=temp;
}
long f[len][100]={0};long m,n;
int main(int argc,char** argv){
	cin >>m>>n;f[0][0]=f[0][1]=1;
	rep(i,n){f[i][1]=f[i][0]=1;rep(j,m)mult(f[i],f[i-1]);pluss(f[i]);}
	JJ(f[n],f[n-1]);
	cout <<f[n][f[n][0]];
	for(long i=f[n][0]-1;i>=1;i--){
		for(long j=MM/10;j>1&&f[n][i]<j;j/=10)
			cout <<0;
		cout <<f[n][i];
	}
	cout <<endl;
	return 0;
}
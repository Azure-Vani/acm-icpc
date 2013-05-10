#include <iostream>
#include <fstream>
#define fin cin
#define len 1005
using namespace std;

//ifstream fin("1.in");
long a[len]={0},n,m,b[len][len]={0};bool hash[len]={0};

long find(long x){
	while(a[x]!=x){
		a[x]=a[a[x]];
		x=a[x];
	}
	return x;
}
int main(int argc,char** argv){
	fin >>n>>m;fin.get();
	for(long i=1;i<=n;i++)a[i]=i;
	for(long i=1;i<=m;i++){
		long l1,l2;
		char ch;
		fin >>ch;
		fin >>l1>>l2;fin.get();
		if(ch=='E'){
			b[l1][++b[l1][0]]=l2;
			b[l2][++b[l2][0]]=l1;
		}
		if(ch=='F')
			a[find(l1)]=find(l2);
	}
	for(long i=1;i<=n;i++)
		for(long j=1;j<=b[i][0];j++){
			long u=b[i][j];
			for(long k=1;k<=b[u][0];k++)
				a[find(i)]=find(b[u][k]);
		}
	long ans=0;
	for(long i=1;i<=n;i++){
		long t=find(i);
		if(!hash[t]){
			hash[t]=true;
			ans++;
		}
	}
	cout <<ans<<endl;
	return 0;
}

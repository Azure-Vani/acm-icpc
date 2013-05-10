#include <fstream>
#include <iostream>
#define len 2000
using namespace std;

long a[len][len]={0},n,m,e,k,hash[len][len]={0},dis[len][len]={0};
long spfa(long l1,long l2){
	bool h[len]={0},ok[len]={0};
	long d[len<<1]={0},head=1,tail=1,c[len]={0};
	memset(ok,1,sizeof ok);
	for(long i=1;i<=e;i++)
		c[i]=0x7fffff;
	for(long j=1;j<=e;j++)
	for(long i=l1;i<=l2;i++)
		ok[j]&=(!hash[j][i]);
	c[1]=0;d[1]=1;h[1]=true;
	while(head<=tail){
		long now=d[head++];
		for(long i=1;i<=e;i++)
			if(a[i][now]&&c[now]+a[i][now]<c[i]&&ok[i]){
				c[i]=c[now]+a[i][now];
				if(!h[i])
					h[d[++tail]=i]=true;
			}
		h[now]=false;
	}
	return c[e]*(l2-l1+1);
}
int main(int argc,char** argv){
	cin >>n>>e>>k>>m;
	for(long i=1;i<=m;i++){
		long l1,l2,x;
		cin >>l1>>l2>>x;
		a[l1][l2]=a[l2][l1]=x;
	}
	long d=0;
	cin >>d;
	for(long i=1;i<=d;i++){
		long l1,l2,p;
		cin >>p>>l1>>l2;
		for(long j=l1;j<=l2;j++)
			hash[p][j]=true;
	}
	long f[len]={0};
	for(long i=1;i<=n;i++)
		for(long j=i;j<=n;j++)
			dis[i][j]=spfa(i,j);
	long g[len]={0};
	for(long i=1;i<=n;i++){
		long temp=0x7fffff,t=0;
		for(long j=0;j<i;j++)
			if(f[j]+dis[j+1][i]+k<temp){
				temp=f[j]+dis[j+1][i]+k;
				t=j;
			}
		g[i]=t;
		f[i]=temp;
	}
	cout <<f[n]-k<<endl;
	return 0;
}

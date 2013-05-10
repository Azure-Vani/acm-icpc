#include <cstdio>
#include <iostream>
#include <cctype>
#include <cstring>
#define cc(a,b) memcpy(a,b,sizeof a)
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define len 2008
#define rep(i,n) for(long i=1;i<=n;i++)
using namespace std;
void read(bool& r){char ch;r=0;while(ch=getchar(),!isdigit(ch));r=ch-'0';}
bool a[len][len]={0};
long n,m,l[len][len]={0},u[len][len]={0};
void work1(void){
	long f[len]={0},ff[len]={0},ans=1;
	for(long i=1;i<=n;i++){rep(j,m){
		if(a[i][j]==a[i-1][j]||a[i][j]==a[i][j-1]){f[j]=1;continue;}
		f[j]=min(ff[j],f[j-1]);f[j]+=(a[i-f[j]][j-f[j]]==a[i][j]);
		ans=max(ans,f[j]);
	}memcpy(ff,f,sizeof f);}
	cout <<ans*ans<<endl;
}
void work2(void){
	long l[len]={0},r[len]={0},h[len]={0},ans=1;
	long ll[len]={0},rr[len]={0},hh[len]={0};
	for(long i=0;i<=n+1;i++)r[m+1]=m+1;
	for(long i=1;i<=n;i++){
		rep(j,m){if(a[i][j]==a[i][j-1])l[j]=j-1;else l[j]=l[j-1];if(a[i][m-j+1]==a[i][m-j+2])r[m-j+1]=m-j+2;else r[m-j+1]=r[m-j+2];}
		rep(j,m){
			if(a[i][j]==a[i-1][j]){h[j]=1;ans=max(ans,r[j]-l[j]-1);continue;}else {
				h[j]=hh[j]+1;
				l[j]=max(l[j],ll[j]);
				r[j]=min(r[j],rr[j]);
				ans=max(ans,h[j]*(r[j]-l[j]-1));
			}
		}
		cc(ll,l);cc(rr,r);cc(hh,h);
	}
	cout <<ans<<endl;
}
int main(int argc,char** argv){
	cin >>n>>m;
	rep(i,n)rep(j,m)read(a[i][j]);
	work1();
	work2();
	return 0;
}

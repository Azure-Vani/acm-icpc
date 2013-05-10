#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <set>
#define rep(i,n) for(long i=1;i<=n;i++)
#define ex(a,b) {bool c=a;a=b;b=c;}
#define len 70000
using namespace std;
set<long> hash;
long fim[4][2]={{0,1},{1,0},{-1,0},{0,-1}};
bool check(bool a[][5],bool b[][5]){
	rep(i,4)rep(j,4)if(a[i][j]!=b[i][j])return false;
	return true;
}
long trans(bool a[][5]){
	long r=0;
	rep(i,4)rep(j,4)r=(r<<1)+a[i][j];
	return r;
}
int main(int argc,char** argv){
	bool a[5][5],b[5][5];char ch;
	rep(i,4)rep(j,4)cin >>ch,a[i][j]=ch-'0';
	rep(i,4)rep(j,4)cin >>ch,b[i][j]=ch-'0';
	if(check(a,b)){cout <<0<<endl;exit(0);}
	
	bool d[len][5][5]={0};long head=1,tail=1,step[len]={0};
	hash.insert(trans(a));
	memcpy(d[1],a,sizeof a);long sum=1;
	while(sum){
		bool now[5][5];memcpy(now,d[head],sizeof now);long tim=step[head++];
		if(head>len-3)head=1;sum--;
		rep(i,4)rep(j,4)if(now[i][j])
			for(long l1=0;l1<4;l1++){
				long lx=i+fim[l1][0],ly=j+fim[l1][1];
				if(lx>0&&lx<=4&&ly>0&&ly<=4&&!now[lx][ly]){
					ex(now[i][j],now[lx][ly]);
					if(check(now,b)){cout <<tim+1<<endl;exit(0);}
					long u=trans(now);
					if(hash.find(u)==hash.end()){
						hash.insert(u);
						++tail,++sum;if(tail>len-3)tail=1;
						memcpy(d[tail],now,sizeof now);step[tail]=tim+1;
					}
					ex(now[i][j],now[lx][ly]);
				}
			}
		}
	return 0;
}

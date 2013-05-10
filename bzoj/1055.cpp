#include <iostream>
#define rep(i,n) for(long i=1;i<=n;i++)
#define len 220
using namespace std;
long a[5][20][2];
char oo[4]={'W','I','N','G'};
long trans(char ch){
	for(long i=0;i<4;i++)
	if(oo[i]==ch)return i+1;
	return 1;}
int main(int argc,char** argv){
	long l[5];
	rep(i,4)cin >>l[i];cin.get();
	string st;
	rep(i,4)rep(j,l[i])getline(cin,st),a[i][j][0]=trans(st[0]),a[i][j][1]=trans(st[1]);
	getline(cin,st);long c[len]={0},n=st.length();
	bool f[len][len][5]={0};
	for(long i=0;i<st.length();i++)c[i+1]=trans(st[i]);
	for(long i=1;i<=n;i++)f[i][i][c[i]]=true;
	for(long i=n;i>=1;i--)
		for(long j=i;j<=n;j++)
			rep(k,4){
				if(i==3&&j==5)
					i=3;
				for(long p=i;p<j;p++)
					for(long h=1;h<=l[k];h++){
						f[i][j][k]=(f[i][j][k]||(f[i][p][a[k][h][0]]&&f[p+1][j][a[k][h][1]]));
					}
		}
	bool bo=false;
	for(long i=0;i<4;i++)if(f[1][n][i+1]){cout <<oo[i];bo=true;}
	if(!bo)cout <<"The name is wrong!";
	cout <<endl;
	return 0;
}

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MOD 1000000007
#define LL long long

using namespace std;

int c[450][450];
int n,tt;
int f[50][500];
int a[50];
int sum[50];

int main() {
	scanf("%d",&tt);
	memset(c,0,sizeof(c));
	c[0][0]=1;
	for (int i=1;i<=447;++i) {
		c[i][0]=1;
		for (int j=1;j<=i;++j)
			c[i][j]=(c[i-1][j]+c[i-1][j-1]) % MOD;
	}

	for (int ii=1;ii<=tt;++ii) {
		scanf("%d",&n);
		for (int i=0;i<n;++i) scanf("%d",&a[i]);
		sum[0]=a[0];
		for (int i=1;i<n;++i) sum[i]=sum[i-1]+a[i];
		memset(f,0,sizeof(f));
		for (int j=0;j<a[0];++j)
			f[0][j]=c[a[0]-1][a[0]-j-1];
		for (int i=1;i<n;++i)
			for (int j=0;j<sum[i];++j)
				for (int k=0;k<=min(a[i]-1,j);++k) {
					int pp=c[a[i]-1][a[i]-k-1];
					int pre=sum[i-1]-(j-k);
					LL tmp=(LL)pp*(LL)c[a[i]-k+pre][pre] % MOD;
					f[i][j]+=tmp*(LL)f[i-1][j-k] % MOD;
					f[i][j]%=MOD;
				}
		int ans=0;
		for (int i=0;i<sum[n-1];++i) {
			if (i & 1) ans+=MOD-f[n-1][i];
			else ans+=f[n-1][i];
			ans%=MOD;
		}
		for (int i=0;i<n;++i)
			for (int j=2;j<=a[i];++j)
				ans=(LL)ans*(LL)j % MOD;
		printf("Case %d: %d\n",ii,ans);
	}
}

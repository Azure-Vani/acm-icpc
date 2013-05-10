#include <cstdio>
#include <algorithm>
int n,ans;
long long a[55][55],b[55][55];
int f[55][55][55][55];
int main() {
	scanf("%d", &n);
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++) scanf("%lld", &a[i][j]);
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= n;j++) scanf("%lld", &b[i][j]);
	for (int i = 1;i <= n;i++) 
		for (int j = 1;j <= n;j++)
			for (int p = 1;p <= n;p++)
				for (int q = 1;q <= n;q++) 
					if (a[i][j] == b[p][q]) {
						f[i][j][p][q] = std::min(std::min(f[i - 1][j][p - 1][q],f[i][j - 1][p][q - 1]),f[i - 1][j - 1][p - 1][q - 1]) + 1;
						ans = std::max(ans,f[i][j][p][q]);
					}
					else f[i][j][p][q] = 0;
	printf("%d\n", ans);
	return 0;
}

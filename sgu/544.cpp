#include <cstdio>
#include <algorithm>
#include <functional>

using namespace std;

const int MAXN = 505, mod = 1000000009;

int n, k, f[MAXN][MAXN], sa[MAXN], sb[MAXN], a[MAXN], b[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++) scanf("%d", b + i);
	if ((n + k) & 1) puts("0"); else {
		k = (n + k) >> 1;
		sort(a + 1, a + n + 1, greater<int>());
		sort(b + 1, b + n + 1, greater<int>());
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) 
				sa[i] += (b[j] < a[i]), sb[i] += (a[j] < b[i]);
		}
		f[0][0] = 1;
		for (int i = 0; i <= n; i++) {
			for (int j = 0; j <= min(i, k); j++) if (f[i][j]) {
				if (a[i] < b[i]) {
					f[i + 1][j] = (f[i + 1][j] + (long long) f[i][j] * (sb[i + 1] + j)) % mod;
					f[i + 1][j + 1] = (f[i + 1][j + 1] + (long long) f[i][j] * (i + 1 - sb[i + 1] - j)) % mod;
				} else {
					f[i + 1][j] = (f[i + 1][j] + (long long) f[i][j] * (1 - sa[i + 1] + j)) % mod;
					f[i + 1][j + 1] = (f[i + 1][j + 1] + (long long) f[i][j] * (sa[i + 1] + i - j)) % mod;
				}
			}
		}
		printf("%d\n", f[n][k]);
	}
	return 0;
}


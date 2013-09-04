#include <cstdio>
#include <iostream>

using namespace std;

const int MAXN = 10000001, MAXP = 2;

int f[MAXP][MAXN], prime[MAXN], cnt = 0, num[MAXN], nFac[MAXN], res[MAXN]; bool tag[MAXN];

inline void Pre(int n) {
	f[0][1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!tag[i]) prime[++cnt] = i, f[0][i] = -1, nFac[i] = 1, num[i] = 1, res[i] = 1;
		for (int j = 1; j <= cnt && (long long)prime[j] * i <= n; j++) {
			tag[prime[j] * i] = true;
			nFac[prime[j] * i] = nFac[i] + 1;
			if (i % prime[j] == 0) {res[prime[j] * i] = res[i]; num[prime[j] * i] = num[i] + 1; break;}
			res[prime[j] * i] = i;
			num[prime[j] * i] = 1;
			f[0][prime[j] * i] = -f[0][i];
		}
	}
	for (int k = 1; k <= 1; k++) {
		for (int i = 2; i <= n; i++) if (nFac[i] >= k) {
			if (num[i] <= k) f[k][i] += f[k - num[i]][res[i]];
			if (num[i] - 1 <= k) f[k][i] -= f[k - num[i] + 1][res[i]];
		}
	}
	for (int k = 0; k <= 1; k++) {
		for (int i = 1; i <= n; i++) f[k][i] += f[k][i - 1];
	}
}

int main(void) {
	Pre(MAXN - 1);
	int q; scanf("%d", &q); while (q--) {
		int n, m, p; scanf("%d%d", &n, &m); p = 1; if (n > m) swap(n, m);
		long long Ans = 0;
		for (int i = 1, next; i <= n; i = next + 1) {
			next = min(n / (n / i), m / (m / i));
			Ans += (long long) (f[p][next] - f[p][i - 1]) * (n / i) * (m / i);
		}
		printf("%lld\n", Ans);
	}
	return 0;
}
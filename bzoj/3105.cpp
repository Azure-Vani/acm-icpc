#include <cstdio>
#include <algorithm>

int n, a[101], gss[31];
long long Ans = 0, S = 0;

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), S += (long long) a[i];
	std::sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--) {
		int tmp = a[i]; bool ok = false;
		for (int j = 0; j <= 30; j++) if (a[i] & (1 << j)) {
			if (!gss[j]) {ok = true; gss[j] = a[i]; break;} else a[i] ^= gss[j];
		}
		if (ok) Ans += (long long)tmp;
	}
	printf("%lld\n", S - Ans);
	return 0;
}


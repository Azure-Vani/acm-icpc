#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>

#pragma GCC optimize("O2")

using namespace std;

typedef long long Int64;

namespace Solve {
	const int MAXN = 200010;
	const int MAXM = 62;

	int n, L, last; Int64 a[MAXN], b[MAXN], mask, Min; int s[MAXN];

	Int64 f[MAXM][MAXN];

	inline int get(Int64 u, int t) {
		return (u >> (t - 1)) & 1ll;
	}

	inline bool cmp(Int64 x, Int64 y) {
		return (x & mask) < (y & mask);
	}

	void Work(void) {
		if (last % 2 == 0) f[1][0] += 1;
		if ((n - last) % 2 == 0) f[1][n - last] += 1;
		for (int i = 2; i <= L; i++) {
			int tmp = 0;
			for (int j = 1; j <= n; j++) if (get(a[j], i - 1) == 0) b[++tmp] = a[j];
			for (int j = 1; j <= n; j++) if (get(a[j], i - 1) == 1) b[++tmp] = a[j];
			memcpy(a, b, sizeof (a[0]) * (n + 1));
			for (int j = 1; j <= n; j++) s[j] = s[j - 1] + (get(a[j], i) == 0);
			for (int j = 0, c1 = n - s[n]; j <= n; j++) if (f[i - 1][j]) {
				int s0 = s[j], s1 = j - s[j], a0 = s[n] - s[j], a1 = c1 - (j - s[j]);
				if ((s0 + a1) % 2 == 0) {
					f[i][s0] += f[i - 1][j];
				}
				if ((s1 + a0) % 2 == 0) {
					f[i][j + a0] += f[i - 1][j];
				}
			}
		}
		Int64 Xor = 0;
		for (int i = 1; i <= n; i++) Xor ^= a[i] - Min;
		printf(LL "\n", f[L][0] - (Xor == 0));
	}

	void solve(void) {
		scanf("%d", &n);
		Min = 1000000000000000000ll;
		for (int i = 1; i <= n; i++) {
			scanf(LL, a + i);
			long long tmp = a[i];int t = 0; while (tmp) tmp >>= 1, t++;
			L = max(L, t);
			last += a[i] & 1ll; Min = min(a[i], Min);
		}
		Work();
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}


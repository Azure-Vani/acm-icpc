#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long Int64;

const int MAXN = 2012;

int n, a[MAXN], s, b[MAXN];

bool check(Int64 k, Int64 n2, Int64 n3, Int64 r) {
	if (k * r < s) return false;
	if (r & 1) {
		if (n3 >= k) n3 -= k, r -= 3; else {
			Int64 res = k - n3, odd = 0, cnt = 0; n3 = 0; if (res & 1) res--, odd = 1;
			for (Int64 i = 1; i <= n && res; i++) {
				Int64 d = min(res, a[i] / 3ll * 2);
				res -= d;
				a[i] -= d * 3 / 2; n2 -= d * 3 / 2;
				cnt += (a[i] < 3);
			}
			if (cnt == n) {
				return (r - 3) * (k - res - odd) + (r - 1) * (res + odd) >= n2 * 2;
			}
			n2 -= odd;
			r -= 3;
		}
	}
	Int64 t = r / 3, max_cap = t * k, t3 = n3;
	if (n3 > max_cap) return false;
	Int64 odd = 0;
	for (Int64 i = 1, tmp = t - t % 2; i <= k && n3; i++) {
		Int64 d = min(n3, tmp);
		n3 -= d;
	}
	if (n3) odd += n3, n3 = 0;
	return (r * k - t3 * 3 - odd) >= n2 * 2;
}

int main(void) {
	freopen("in", "r", stdin);
	int m; scanf("%d%d", &n, &m);
	Int64 n2 = 0, n3 = 0;
	for (Int64 i = 1; i <= n; i++) {
		scanf("%d", a + i), s += a[i];
		if (a[i] & 1) a[i] -= 3, n3++;
		n2 += a[i] >> 1;
		b[i] = (a[i] >>= 1);
	}
	int l = 1, r = s;
	while (l <= r) {
		Int64 mid = (l + r) >> 1;
		memcpy(a, b, sizeof (int) * (n + 1));
		if (check(mid, n2, n3, m)) r = mid - 1; else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}


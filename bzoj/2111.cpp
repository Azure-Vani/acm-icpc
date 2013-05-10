#include <cstdio>
const int MAXN = 1000100;
typedef long long Int64;
int n, p, g = 1, c[MAXN];
inline int _E(int a) {
	int t = p - 2, ret = 1;
	while (t) {
		if (t & 1) ret = (Int64)ret * a % p;
		t >>= 1;
		a = (Int64) a * a % p;
	}
	return ret;
}
inline int f(int u) {
	if (u > n) return 0;
	if (c[u]) return c[u];
	return c[u] = f(u<<1) + f((u<<1)+1) + 1;
}
int main(void) {
	scanf("%d%d", &n, &p);
	for (int i = 1; i <= n; i++)
		g = (Int64) g * i % p;
	for (int i = n; i >= 1; i--) g = (Int64) g * _E(f(i)) % p;
	printf("%d\n", g);
	return 0;
}

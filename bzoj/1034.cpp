//#define Debug
#include <cstdio>
#include <algorithm>
const long MAXN = 100050;
long n = 0;
inline void Add(long *c, long l, long r, long x) {
	if( r < 0 || l > r)return; if( l < 0 ) l = 0;
	c[l] += x; c[r + 1] -= x;
}
long Luangao(long *a, long *b, long n) {
	long W[MAXN] = {0}, c[MAXN] = {0};
	for (long i = 0; i < n; i++) {
		long l = std::lower_bound(b, b + n, a[i]) - b;
		long r = std::upper_bound(b, b + n, a[i]) - b;
		Add(c, i - l + 1, i, 2);
		Add(c, i - r + 1, i - l, 1);
	}
	long A = 0, ret = 0;
	for (long i = 0; i < n; i++) {
		ret += c[i];
		A = std::max(A, ret);
	}
	return A;
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif

	long a[MAXN] = {0}, b[MAXN] = {0};
	scanf("%ld", &n);
	for (long i = 0; i < n; i++) scanf("%ld", a + i);
	for (long i = 0; i < n; i++) scanf("%ld", b + i);
	std::sort(a , a + n);
	std::sort(b , b + n);
	long A1 = Luangao(a, b, n);
	long A2 = Luangao(b, a, n);
	printf("%ld %ld\n", A1, n * 2 - A2);
	return 0;
}

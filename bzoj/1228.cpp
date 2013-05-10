//#define Debug
#include <cstdio>
namespace Solve {
	long n;
	inline long SG(long a, long b) {
		long sg = 0;
		while ( (a & 1) || (b & 1) ) sg++, a >>= 1, b >>= 1;
		return sg;
	}
	inline void solve(void) {
		scanf("%ld", &n);
		n >>= 1;
		long A = 0;
		for (long i = 1; i <= n; i++) {
			long a, b; scanf("%ld %ld", &a, &b);
			A ^= SG(a - 1, b - 1);
		}
		puts(A?"YES":"NO");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	long T; scanf("%ld", &T);
	while (T--)
		Solve::solve();
	return 0;
}

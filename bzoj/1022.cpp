//#define Debug
#include <cstdio>
namespace Solve {
	const long MAXN = 55;
	void solve(void) {
		long n, u, A = 0; scanf("%ld", &n);
		bool onlyone = true;
		for (long i = 1; i <= n; i++) 
			scanf("%ld", &u), A ^= u, onlyone &= (u <= 1);
		puts((!A && onlyone) || (A && !onlyone) ? "John" : "Brother");
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

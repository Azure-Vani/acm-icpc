//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const int MOD = 10000;

	inline int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	inline int Pow(int a, int n) {
		int r = 1;
		while (n) {
			if (n & 1) r = (a * r) % MOD;
			n >>= 1;
			a = (a * a) % MOD;
		}
		return r;
	}

	void solve(void) {
		int S0 = 1, S1 = 0, N = ScanInt(), p, e, M = 1, last;
		for (int i = 1; i <= N; i++) {
			p = ScanInt(), e = ScanInt();
			M = (M * Pow(p, e)) % MOD;
			if (p == 2) continue;
			last = S0;
			S0 = (S0 + S1 * (p - 1)) % MOD;
			S1 = (S1 + last * (p - 1)) % MOD;
		}
		int A = M - S0 - S1; S0--;
		while (A < 0) A += MOD;
		printf("%d\n%d\n%d\n", S0, S1, A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

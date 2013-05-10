//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 300;
	int n, m;
	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c -'0';
		return r;
	}
	
	void solve(void) {
		n = ScanInt(), m = ScanInt();
		Int64 S1 = 0, S2 = 0;
		for (Int64 i = 1; i <= n; i++)
			for (Int64 j = 1; j <= m; j++)
				S1 += (i * i + j * j) * ScanInt();
		for (Int64 i = 1; i <= n; i++)
			for (Int64 j = 1; j <= m; j++)
				S2 += (i * i + j * j) * ScanInt();
		printf("%lld\n", (S1 - S2) >> 1);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

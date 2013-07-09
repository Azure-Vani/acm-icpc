#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 100010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int a[MAXN], n, fac[MAXN], f[MAXN];

	inline void solve(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
		sort(a + 1, a + n + 1); n = unique(a + 1, a + n + 1) - a - 1;
		int Ans = 0; 
		for (int i = 1; i <= n; i++) {
			int t = 0;
			for (int j = 1; j * j <= a[i]; j++) if (a[i] % j == 0) {
				if (j != 1) t = max(fac[j], t);
				t = max(fac[a[i] / j], t);
			}
			f[i] = t + 1;
			for (int j = 1; j * j<= a[i]; j++) if (a[i] % j == 0) {
				if (j != 1) fac[j] = max(fac[j], f[i]);
				fac[a[i] / j] = max(fac[a[i] / j], f[i]);
			}
			Ans = max(Ans, f[i]);
		}
		printf("%d\n", Ans);
	}
}

int main(void) {
	#ifdef FILEIO
//		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

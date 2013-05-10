//#define FILEIO

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
	const int MAXN = 1010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	bool f[MAXN][MAXN];

	inline void solve(void) {
		int n = ScanInt(), t = ScanInt(), m = ScanInt();
		f[0][t] = true;
		for (int i = 0; i < n; i++) {
			int tmp = ScanInt();
			for (int j = 0; j <= m; j++) if (f[i][j]) {
				if (j + tmp <= m) f[i + 1][j + tmp] = true;
				if (j - tmp >= 0) f[i + 1][j - tmp] = true;
			}
		}
		bool virgin = true;
		for (int i = m; i >= 0; i--) {
			if (f[n][i]) {
				printf("%d\n", i);
				virgin = false;
				break;
			}
		}
		if (virgin) puts("-1");
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
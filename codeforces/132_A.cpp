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
	int a[100], b[100], n, m;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	inline void solve(void) {
		n = ScanInt(); for (int i = 1; i <= n; i++) a[i] = ScanInt();
		m = ScanInt(); for (int i = 1; i <= m; i++) b[i] = ScanInt();
		int best = 0, cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (b[j] % a[i] == 0) {
					if (b[j] / a[i] == best) {
						cnt++;
					} else if (b[j] / a[i] > best) {
						cnt = 1;
						best = b[j] / a[i];
					}
				}
			}
		}
		printf("%d\n", cnt);
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

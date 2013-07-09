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
	const int MAXN = 200010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int a[MAXN], n, b[MAXN], cnt = 0, sum = 0;
	int zero = 0, l1 = 0, l2 = 0;
	bool c[MAXN];

	inline void solve(void) {
		n = ScanInt(); for (int i = 1; i <= n; i++) {
			a[i] = ScanInt(), sum += a[i];
			if (a[i] == 0) zero++;
		}
		if (!zero) {puts("-1"); return;}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) {
			if (a[i] % 3 == 0) b[++cnt] = a[i], c[i] = true;
			if (a[i] % 3 == 1) l1++;
			if (a[i] % 3 == 2) l2++;
		}
		if (sum % 3 == 1) {
			if (l1 == 0) {
				int t = 2;
				for (int i = 1; i <= n; i++) if (a[i] % 3 == 2 && t) c[i] = true, t--;
			} else {
				int t = 1;
				for (int i = 1; i <= n; i++) if (a[i] % 3 == 1 && t) c[i] = true, t--;
			}
		}
		if (sum % 3 == 2) {
			if (l2 == 0) {
				int t = 2;
				for (int i = 1; i <= n; i++) if (a[i] % 3 == 1 && t) c[i] = true, t--;
			} else {
				int t = 1;
				for (int i = 1; i <= n; i++) if (a[i] % 3 == 2 && t) c[i] = true, t--;
			}
		}
		for (int i = 1; i <= n; i++) if (!c[i]) b[++cnt] = a[i];
		sort(b + 1, b + cnt + 1); sum = 0;
		for (int i = 1; i <= cnt; i++) sum += b[i]; if (sum == 0) {puts("0"); return;}
		assert(sum % 3 == 0);
		for (int i = cnt; i >= 1; i--) printf("%d", b[i]); printf("\n");
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


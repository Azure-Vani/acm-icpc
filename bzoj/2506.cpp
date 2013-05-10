//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include <vector>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	const int MAXN = 100020;
	const int MAXM = 106;
	typedef std::vector<int> VII;

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	int n, m, a[MAXN], MaxH;
	VII c[MAXM][MAXM], T[MAXM * MAXM];

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (register int i = 1; i <= n; i++) {
			register int tmp = a[i] = ScanInt();
			for (register int j = 1; j <= 100; j++) {
				c[j][tmp % j].push_back(i);
			}
			T[tmp].push_back(i);
			MaxH = std::max(MaxH, tmp);
		}
	}

	inline void Work(void) {
		int l = ScanInt(), r = ScanInt(), p = ScanInt(), k = ScanInt();
		if (p <= 100) {
			int ret = upper_bound(c[p][k].begin(), c[p][k].end(), r) - lower_bound(c[p][k].begin(), c[p][k].end(), l);
			printf("%d\n",ret);
		}else{
			int ret = 0;
			while (k <= MaxH) {
				ret += upper_bound(T[k].begin(), T[k].end(), r) - lower_bound(T[k].begin(), T[k].end(), l);
				k += p;
			}
			printf("%d\n",ret);
		}
	}

	void solve(void) {
		Input();
		while (m--)
			Work();
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

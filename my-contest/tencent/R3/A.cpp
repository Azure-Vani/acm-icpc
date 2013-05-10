#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	const int MAXN = 520;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int f[MAXN][MAXN], n, m;

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			memset(f, 50, sizeof f);
			rep(i, m) {
				int t; scanf("%d", &t);
				f[1][t] = 0;
			}
			int Ans = 1000000000;
			for (int i = 2; i <= n; i++) {
				for (int j = 1; j <= m; j++) {
					int t; scanf("%d", &t);
					for (int k = 1; k <= 500; k++)
						f[i][t] = min(f[i][t], f[i - 1][k] + abs(k - t));
					if (i == n) Ans = min(Ans, f[i][t]);
				}
			}
			if (n != 1) printf("%d\n", Ans); else puts("0");
		}
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


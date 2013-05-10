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
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline void solve(void) {
		int kase = ScanInt(); rep(_,kase) {
			int x = ScanInt(), q = ScanInt();
			while (q--) {
				int t = ScanInt(), u = ScanInt();double Ans;
				if (t == 1) {
					Ans = (60.0 - x) * u;
				} else if (t == 2) {
					Ans = u * 60 * 60 / (60.0 - x);
				} else {
					if (x == 0) {
						Ans = u;
					} else 
					Ans = 12.0 * 60 * 60  * 60 / x * u;
				}
				printf("%.2lf\n", Ans);
			}
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

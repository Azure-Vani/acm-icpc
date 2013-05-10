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
#include <set>
#include <map>

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

	const int MAXN = 505;

	struct P {
		int a1, b1, a2, b2;
	}c[MAXN];

	inline void solve(void) {
		int kase = ScanInt(); rep(_,kase) {
			int n = ScanInt(), n1 = ScanInt(), n2 = ScanInt();
			rep(i,n) c[i].a1 = ScanInt(), c[i].b1 = ScanInt(), c[i].a2 = ScanInt(), c[i].b2 = ScanInt();
			long double l = 0, r = 1000000000;
			while (r - l > 1e-7) {
				long double mid = (l + r) / 2.0;
			}
		}
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

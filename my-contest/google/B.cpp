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

	const int MAXN = 200;
	
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int a[MAXN][MAXN];

	inline void solve(void) {
			int n = ScanInt(), m = ScanInt();
			rep(i,n) rep(j,m) a[i][j] = ScanInt();
			rep(i,n) rep(j,m) {
				int tr = 0, tc = 0;
				rep(k,m) tr = max(tr, a[i][k]);
				rep(k,n) tc = max(tc, a[k][j]);
				if (a[i][j] != tr && a[i][j] != tc) {puts("NO"); return;}
			}
			puts("YES");
	}

inline void T(void) {
		int kase = ScanInt(); rep(_,kase) {
		printf("Case #%d: ", _);
		solve();
		}
}}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::T();
	return 0;
}

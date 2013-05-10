//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <iostream>
#include <cstdio>
#include <cmath>
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
	typedef long long Int64;
	const int MAXN = 5010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	
	Int64 n, m, k, A, B;
	Int64 r1[MAXN], p1[MAXN], p2[MAXN], max_r;

	inline void solve(void) {
		n = ScanInt(); for (int i = 1; i <= n; i++) r1[i] = ScanInt(), max_r = max(max_r, r1[i]);
		m = ScanInt(); for (int i = 1; i <= m; i++) p1[i] = ScanInt();
		k = ScanInt(); for (int i = 1; i <= k; i++) p2[i] = ScanInt();
		A = ScanInt(), B = ScanInt();
		double best = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= k; j++) {
				double tmp = (double)(B * p1[i]) / (double)(A * p2[j] + B * p1[i]);
				if (tmp > best) best = tmp;
			}
		}
		best *= max_r * max_r;
		printf("%.10lf\n", sqrt(best));
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

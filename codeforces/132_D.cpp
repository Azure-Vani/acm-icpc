//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 1000100;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	Int64 n, m, t[MAXN], T[MAXN], x[MAXN], cost[MAXN];

	inline Int64 Cal(void) {
		Int64 Ans = 0, d;
		for (Int64 i = 1; i <= n; i++) {
			if (T[i] <= t[i]) {
				Ans += x[i] * m + cost[i]; continue;
			} else d = T[i] - t[i];
			Int64 l1 = 0, l2 = 0, t;
			Int64 add = m / d; if (m % d != 0) add++; add = max(add, 1ll);
			l1 = add * cost[i];
			l2 += cost[i];
			if (m > d) l2 += m * x[i];
			t = min(l1, l2);
			if (add > 1) {
				Int64 l3 = 0;
				add--;
				l3 += (m - d * (add - 1)) * x[i];
				l3 += add * cost[i];
				t = min(t, l3);
			}
			Ans += t;
		}
		return Ans;
	}

	inline void solve(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) {
			t[i] = ScanInt(), T[i] = ScanInt(), x[i] = ScanInt(), cost[i] = ScanInt();
		}
		cout <<Cal()<<endl;
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

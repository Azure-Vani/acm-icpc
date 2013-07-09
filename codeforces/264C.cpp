//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <iostream>
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
	const int MAXN = 100010;

	typedef long long Int64;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int c[MAXN];Int64 a, b, f[MAXN], Max1, Max2, w1, w2, v[MAXN];
	bool vis[MAXN];

	inline void solve(void) {
		int n = ScanInt(), q = ScanInt();
		for (int i = 1; i <= n; i++) v[i] = ScanInt();
		for (int i = 1; i <= n; i++) c[i] = ScanInt();
		for (int i = 1; i <= q; i++) {
			b = ScanInt(), a = ScanInt();
			memset(f, -60, sizeof f); Max1 = Max2 = w1 = w2 = 0;
			memset(vis, 0, sizeof vis);
			Int64 Ans = 0;
			for (int i = 1; i <= n; i++) {
				Int64 tmp = 0;
				Int64 t1 = f[c[i]] + b * v[i];
				Int64 t2 = (w1 == c[i] ? Max2 : Max1) + a * v[i];
				tmp = max(t1, t2);
				if (tmp > f[c[i]]) {
					f[c[i]] = tmp;
					if (w1 == c[i]) Max1 = tmp;
					else {
						if (tmp > Max1) Max2 = Max1, w2 = w1, Max1 = tmp, w1 = c[i];
						else if (tmp > Max2) Max2 = tmp, w2 = c[i];
					}
				}
				Ans = max(Ans, f[c[i]]);
			}
			cout <<Ans<<endl;
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

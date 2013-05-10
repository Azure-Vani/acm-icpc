#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <iostream>

#define cl(a) memset(a, 0, sizeof a);
#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
using namespace std;

namespace Solve {
	const int MAXN = 200100;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Rect {
		long long x1, y1, x2, y2;
		void Scan(void) {
			x1 = ScanInt(), y1 = ScanInt(), x2 = ScanInt(), y2 = ScanInt();
		}
	}a[MAXN]; int n;

	long long Ans[MAXN], Flag1[MAXN], Flag2[MAXN], Flag3[MAXN], Flag4[MAXN];

	inline void solve(void) {
		int kase = ScanInt(); rep(_, kase) {
			n = ScanInt();
			cl(Flag1);
			cl(Flag2);
			cl(Flag3);
			cl(Flag4);
			cl(Ans);
			rep(i,n) {
				a[i].Scan();
				long long begin = max(a[i].x1, a[i].y1), end = min(a[i].x2, a[i].y2);
				if (begin > end) {
					if (begin == a[i].x1) {
						Flag3[begin + 1] += a[i].y2 - a[i].y1;
						Flag3[a[i].x2 + 1] -= a[i].y2 - a[i].y1;
					} else {
						Flag3[begin + 1] += a[i].x2 - a[i].x1;
						Flag3[a[i].y2 + 1] -= a[i].x2 - a[i].x1;
					}
					continue;
				}
				Flag1[begin + 1] += 1; Flag1[end + 1] -= 1;
				Flag2[end] -= end - begin;
				Flag4[end + 1] += (end - begin) * (end - begin);
				if (begin == a[i].x1) {
					Flag3[begin + 1] += begin - a[i].y1;
					Flag3[end + 1] -= begin - a[i].y1;
					if (end == a[i].x2) {
						Flag3[end + 1] += a[i].x2 - a[i].x1;
						Flag3[a[i].y2 + 1] -= a[i].x2 - a[i].x1;
					} else {
						Flag3[end + 1] += a[i].y2 - a[i].y1;
						Flag3[a[i].x2 + 1] -= a[i].y2 - a[i].y1;
					}
				} else {
					Flag3[begin + 1] += begin - a[i].x1;
					Flag3[end + 1] -= begin - a[i].x1;
					if (end == a[i].x2) {
						Flag3[end + 1] += a[i].x2 - a[i].x1;
						Flag3[a[i].y2 + 1] -= a[i].x2 - a[i].x1;
					} else {
						Flag3[end + 1] += a[i].y2 - a[i].y1;
						Flag3[a[i].x2 + 1] -= a[i].y2 - a[i].y1;
					}
				}
			}
			rep(i, 200000) Flag1[i] += Flag1[i - 1], Flag3[i] += Flag3[i - 1];
			rep(i, 200000) Flag3[i] += Flag3[i - 1];
			rep(i, 200000) {
				Ans[i] = Ans[i - 1] + Flag2[i - 1] * 2 + Flag1[i] - Flag4[i];
				Flag2[i + 1] += Flag2[i] + Flag1[i + 1];
			}
			rep(i, 200000) Ans[i] += Flag3[i], Flag4[i] += Flag4[i - 1];
			rep(i, 200000) Ans[i] += Flag4[i];
			int x = ScanInt();
			rep(i, x) {
				int t = ScanInt();
				cout <<Ans[t]<<endl;
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

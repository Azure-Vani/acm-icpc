#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>
using namespace std;
namespace Solve {
	const int MAXN = 1000100;
	
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, m, a[MAXN], s[MAXN], l1, l2, s1, s2;

	inline void solve(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++) a[i] = (getchar() == 'T') + 1, s[i] = s[i - 1] + a[i], s1 += (a[i] == 1), s2 += (a[i] == 2);
		if (s2 == 0) {
			while (m--) {
				int x = ScanInt(); if (x <= s[n]) printf("1 %d\n", x); else puts("NIE");
			}
		} else
		if (s1 == 0) {
			while (m--) {
				int x = ScanInt(); if (x <= s[n] && x % 2 == 0) printf("1 %d\n", x >> 1); else puts("NIE");
			}
		} else {
			for (int i = 1; i <= n; i++) if (a[i] == 1) {l1 = i; break;}
			for (int i = n; i >= 1; i--) if (a[i] == 1) {l2 = i; break;}
			while (m--) {
				int x = ScanInt(); if (x > s[n]) {puts("NIE"); continue;} int L, R;
				if (x <= s[n] - s[l1 - 1]) {
					int l = l1, r = n;
					while (l <= r) {
						int mid = (l + r) >> 1;
						if (s[mid] - s[l1 - 1] == x) {L = l1, R = mid; break;}
						if (s[mid] - s[l1] == x) {L = l1 + 1, R = mid; break;}
						if (s[mid] - s[l1 - 1] > x)
							r = mid - 1;
						else
							l = mid + 1;
					}
				} else
				if (x % 2 == (s[n] - s[l1 - 1]) % 2) {
					//printf("%d %d\n", l1 - (x - (s[n] - s[l1 - 1])) / 2, n);
					L = l1 - (x - (s[n] - s[l1 - 1])) / 2, R = n;
				} else {
					if (x > s[l2 - 1]) {
						puts("NIE");
						continue;
					} else {
						L = l1 - (x - (s[l2 - 1] - s[l1 - 1])) / 2; R = l2 - 1;
					}
				}
				assert(s[R] - s[L - 1] == x);
				printf("%d %d\n", L, R);
//				puts("TAK");
			}
		}
	}
}

int main(void) {
//	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

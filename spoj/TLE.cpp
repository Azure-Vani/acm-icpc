#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

inline void Add(int &a, int b) {
	a += b;
	if (a >= 1000000000) a -= 1000000000;
}

int f[2][(1<<15) + 3], n, m, c[51], M;

int main(void) {
	freopen("in", "r", stdin);
	int kase; kase = ScanInt();
	while (kase--) {
		n = ScanInt(), m = ScanInt(); M = (1 << m) - 1;
		memset(f[0], 0, sizeof f[0]);
		f[0][0] = 1;
		for (int i = 1; i <= n * m; i++) {
			int now = i & 1, last = now ^ 1;
			memset(f[now], 0, sizeof f[now]);
			if (i % m == 0) {
				int c = ScanInt();
				for (int j = 0; j <= M; j++) {
					int tmp = (j & (M >> 1)) << 1, d = tmp % c, g = j >> (m - 1);
					if (d != 0) Add(f[now][tmp], f[last][j]);
					if (d != c - 1 && !g) Add(f[now][tmp + 1], f[last][j]);
				}
			} else {
				for (int j = 0; j <= M; j++) {
					int tmp = (j & (M >> 1)) << 1, d = j >> (m - 1);
					Add(f[now][tmp], f[last][j]);
					if (!d)
						Add(f[now][tmp + 1], f[last][j]);
				}
			}
		}
		int Ans = 0;
		for (int i = 0; i <= M; i++) Add(Ans, f[(n * m) & 1][i]);
		printf("%d\n", Ans);
	}
	return 0;
}


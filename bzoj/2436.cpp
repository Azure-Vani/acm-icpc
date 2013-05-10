//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include <vector>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	const int MAXN = 404;

	struct Interval {
		int l, r;
	}a[MAXN]; int n, c[MAXN], m;
	int cnt[MAXN][MAXN];

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) {
			a[i].l = ScanInt(), a[i].r = ScanInt();
			a[i].r += a[i].l;
			c[++m] = a[i].l;
			c[++m] = a[i].r;
		}
		std::sort(c + 1, c + m + 1);
		m = std::unique(c + 1, c + m + 1) - c - 1;
		for (int i = 1; i <= m; i++) 
			for (int j = i + 1; j <= m; j++) {
				cnt[i][j] = 0;
				for (int k = 1; k <= n; k++) 
					if (a[k].l >= c[i] && a[k].r <= c[j])
						cnt[i][j]++;
			}
	}

	int f[MAXN][MAXN], g[MAXN][MAXN];
	int H[MAXN][MAXN];

	inline void Dp(){
		memset(f, -60, sizeof f);
		memset(g, -60, sizeof g);
		f[1][0] = g[m][0] = 0;
		for (int i = 2; i <= m; i++) {
			for (int j = 0; j <= n; j++) {
				int &tmp = f[i][j];
				for (int k = 1; k < i; k++) {
					tmp = std::max(tmp, f[k][j] + cnt[k][i]);
					if (j >= cnt[k][i] && f[k][j - cnt[k][i]] >= 0)
						tmp = std::max(tmp, f[k][j - cnt[k][i]]);
				}
			}
		}
		for (int i = m - 1; i >= 1; i--) {
			for (int j = 0; j <= n; j++) {
				int &tmp = g[i][j];
				for (int k = i + 1; k <= m; k++) {
					tmp = std::max(tmp, g[k][j] + cnt[i][k]);
					if (j >= cnt[i][k] && g[k][j - cnt[i][k]] >= 0)
						tmp = std::max(tmp, g[k][j - cnt[i][k]]);
				}
			}
		}
		int Ans = 0;
		for (int i = 0; i <= n; i++) Ans = std::max(Ans, std::min(f[m][i], i));
		printf("%d\n", Ans);
		for (int i = 1; i <= m; i++) {
			for (int j = i + 1; j <= m; j++) {
				int &tmp = H[i][j], r = n;
				for (int l = 0; l <= n; l++) { 
					while (r > 0) {
						int cur = std::min(cnt[i][j] + l + r, f[i][l] + g[j][r]);
						int ncur = std::min(cnt[i][j] + l + r - 1, f[i][l] + g[j][r - 1]);
						if (ncur >= cur)
							r--;
						else 
							break;
					}
					int cur = std::min(cnt[i][j] + l + r, f[i][l] + g[j][r]);
					tmp = std::max(tmp, cur);
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			int ret = 0;
			for (int l = 1; l <= m; l++) if (c[l] <= a[i].l) {
				for (int r = l + 1; r <= m; r++) if (c[r] >= a[i].r) {
					ret = std::max(ret, H[l][r]);
				}
			}
			printf("%d\n", ret);
		}
	}

	void solve(void) {
		Input();
		Dp();
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

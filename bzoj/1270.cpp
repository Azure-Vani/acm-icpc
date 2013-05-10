//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 2011;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, h, delta;Int64 s[MAXN][MAXN];

	void Input(void) {
		n = ScanInt(), h = ScanInt(), delta = ScanInt();
		for (int i = 1; i <= n; i++) {
			int tmp = ScanInt();
			for (int j = 1; j <= tmp; j++) {
				int h = ScanInt();
				s[i][h]++;
			}
		}
	}

	Int64 f[MAXN][MAXN], M[MAXN][MAXN];

	void solve(void) {
		Input();
		for (int i = h; i >= 0; i--) {
			for (int j = 1; j <= n; j++) {
				f[j][i] = f[j][i + 1];
				if (i + delta <= h)
					f[j][i] = std::max(f[j][i], M[j][i + delta]);
				f[j][i] += s[j][i];
			}
			Int64 max = 0, which = 0, two_max = 0, two_which = 0;
			for (int j = 1; j <= n; j++) {
				if (f[j][i] > max) {
					two_max = max, two_which = which;
					max = f[j][i], which = j;
				}else if (f[j][i] > two_max) {
					two_max = f[j][i], two_which = j;
				}
			}
			for (int j = 1; j <= n; j++) if (j != which) 
				M[j][i] = max;
			else
				M[j][i] = two_max;
		}
		Int64 Ans = 0;
		for (int i = 1; i <= n; i++) Ans = std::max(f[i][0], Ans);
		printf("%lld\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

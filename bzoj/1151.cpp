//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
#define X(x) ((x) > n ? ((x) - n) : (x))
namespace Solve {
	const int MAXN = 100050;
	const int MAXS = 31;
	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int S[MAXN][MAXS + 5], n, Fear[MAXN], Love[MAXN];
	void Input(void) {
		n = ScanInt();int c = ScanInt();
		for (int i = 1; i <= c; i++) {
			int where = ScanInt() + 4;
			int nFear = ScanInt(), nLove = ScanInt();
			for (int j = 1; j <= nFear; j++) Fear[ScanInt()] = i;
			for (int j = 1; j <= nLove; j++) Love[ScanInt()] = i;
			for (int j = 0; j <= MAXS; j++)
				for (int v = 0; v < 5; v++)
					if (((j & (1 << v)) && Love[X(where - v)] == i) || (!(j & (1 << v)) && Fear[X(where - v)] == i)) {
							S[where][j]++;
							break;
					}
		}
	}

	int f[MAXN][MAXS + 5];
	void solve(void) {
		Input();
		int Ans = 0;
		for (int k = 0; k <= MAXS >> 1; k++) {
			memset(f, -101, sizeof f); f[4][k] = 0;
			for (int i = 5; i <= n + 4; i++)
				for (int j = 0; j <= MAXS; j++)
					f[i][j] = std::max(f[i - 1][(j >> 1) + 16], f[i - 1][j >> 1]) + S[i][j];
			Ans = std::max(Ans, std::max(f[n + 4][k + 16], f[n + 4][k]));
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

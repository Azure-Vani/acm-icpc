//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	const int MAXN = 50020;
	const int MAXP = 37;

	inline int X(int a) {
		return isdigit(a) ? a - '0' : a - 'a' + 10;
	}
	int f1[4][MAXP], f2[6][MAXP][MAXP], f3[4][MAXP][MAXP][MAXP];
	int n, d;

	typedef long long Int64;
	Int64 c1, c2, c3;
	inline void Input(void) {
		scanf("%d %d\n", &n, &d); d = 4 - d;
		for (int i = 1; i <= n; i++) {
			int a = X(getchar()), b = X(getchar()), c = X(getchar()), d = X(getchar()); scanf("\n");
			c1 += f1[0][a]++, c1 += f1[1][b]++, c1 += f1[2][c]++, c1 += f1[3][d]++;
			c2 += f2[0][a][b]++, c2 += f2[1][a][c]++, c2 += f2[2][a][d]++, c2 += f2[3][b][c]++, c2 += f2[4][b][d]++, c2 += f2[5][c][d]++;
			c3 += f3[0][a][b][c]++, c3 += f3[1][a][c][d]++, c3 += f3[2][a][b][d]++, c3 += f3[3][b][c][d]++;
		}
	}

	
	#define rep(i, b) for (int i = 0; i < b; i++)
	#define sqr(x) ((x)*((x) - 1))

	inline void solve(void) {
		Input();
		if (d == 0) printf(LL "\n", (n * (n - 1ll) >> 1ll) - c1 + c2 - c3);else
		if (d == 1) printf(LL "\n", c1 - 2ll * c2 + c3 * 3ll); else
		if (d == 2) printf(LL "\n", c2 - c3 * 3ll); else
		printf(LL "\n", c3);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

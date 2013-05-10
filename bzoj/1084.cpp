//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
long n, m, k;
namespace Solve2 {
	const long MAXN = 105;
	const long inf = 0x6eeeeeee;
	long s[2][MAXN] = {0}, f[12][MAXN][MAXN] = {0};
	void Input(void) {
		for (long i = 1; i <= n; i++)
			for (long j = 0; j <= 1; j++)
				scanf("%ld", &s[j][i]), s[j][i] += s[j][i - 1];
	}
	inline long Get(long l, long r, long* s) {
		return s[r] - s[l - 1];
	}
	#define max(a,b) ((a)>(b)?(a):(b))
	void Work(void) {
		Input();
		memset(f, -101, sizeof f);
		for (long i = 0; i <= n; i++)
			for (long j = 0; j <= n; j++)
				f[0][i][j] = 0;

		for (long i = 1; i <= k; i++)
			for (long l1 = 0; l1 <= n; l1++)
				for (long l2 = 0; l2 <= n; l2++)
					if (l1 == l2) {

						long temp = -inf;
						if (l1 > 0) temp = max(temp, f[i][l1 - 1][l2]);
						if (l2 > 0) temp = max(temp, f[i][l1][l2 - 1]);
						if (l1 > 0 && l2 > 0) temp = max(temp, f[i][l1 - 1][l2 - 1]);

						for (long j = l1 -1; j >= 0; j--) {
							temp = max(temp, f[i - 1][j][j]+Get(j + 1, l1, s[0]) + Get(j + 1, l1, s[1]));
							temp = max(temp, f[i - 1][j][l1]+Get(j + 1, l1, s[0]));
							temp = max(temp, f[i - 1][l1][j]+Get(j + 1, l2, s[1]));
						}

						f[i][l1][l2] = temp;
					} else {

						long temp = -inf;
						if (l1 > 0) temp = max(temp, f[i][l1 - 1][l2]);
						if (l2 > 0) temp = max(temp, f[i][l1][l2 - 1]);

						for (long j = l1 - 1; j >= 0; j--)
							temp = max(temp, f[i - 1][j][l2] + Get(j + 1, l1, s[0]));
						for (long j = l2 - 1; j >= 0; j--)
							temp = max(temp, f[i - 1][l1][j] + Get(j + 1, l2, s[1]));

						f[i][l1][l2] = temp;
					}
		printf("%ld\n", f[k][n][n]);
	}
}
namespace Solve1 {
	const long MAXN = 102;
	const long inf = 0x6eeeeeee;
	long s[MAXN] = {0}, f[12][MAXN] = {0};
	void Work(void) {
		memset(f, -101, sizeof f);
		for (long i = 1; i <= n; i++)
			scanf("%ld", s + i), s[i] += s[i - 1];
		for (long i = 0; i <= n; i++) f[0][i] = 0;
		for (long i = 1; i <= k; i++)
			for (long j = 0; j <= n; j++) {
				long temp = -inf;
				if (j > 0) temp = max(temp, f[i][j - 1]);
				for (long p = 0; p < j; p++)
					temp = max(f[i - 1][p] + s[j] - s[p], temp);
				f[i][j] = temp;
			}
		printf("%ld\n", f[k][n]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	scanf("%ld %ld %ld", &n, &m, &k);
	if (m == 1)
		Solve1::Work();
	else
		Solve2::Work();
	return 0;
}

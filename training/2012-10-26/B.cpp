#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

#define REP(i, l, r) for(int i = l; i <= r; i++)
#pragma GCC optimize("O2")

const int MAXN = 3010;
char c1[MAXN], c2[MAXN]; int n, f[MAXN][MAXN], m;

inline int Cal(char *c1, char *c2) {
	REP(j, n + 1, n * 2) c1[j] = c1[j - n];
	int Ans = 0;
	REP(_, 1, min(100, n)) {
		int k = rand() % n + 1;
		REP(i, 1, m) f[k - 1][i] = 0;
		REP(j, k - 1, k + n - 1) f[j][0] = 0;
		for (int i = k; i <= k + n - 1; i++) {
			for (int j = 1; j <= m; j++){
				f[i][j] = max(f[i - 1][j], f[i][j - 1]);
				if (c1[i] == c2[j]) f[i][j] = max(f[i][j], f[i - 1][j - 1] + 1);
				Ans = max(Ans, f[i][j]);
			}
		}
	}
	return Ans;
}

int main(void) {
	freopen("in", "r", stdin);
	srand((size_t)time(0));
	while (scanf("%s %s", c1 + 1, c2 + 1) == 2) {
		n = strlen(c1 + 1), m = strlen(c2 + 1);
		int a1 = Cal(c1, c2);
		std::reverse(c1 + 1, c1 + n + 1);
		int a2 = Cal(c1, c2);
		printf("%d\n", max(a1, a2) << 1);
	}
	return 0;
}

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 33;
const int P = 1001;
const int mod = 1000000009;

inline int Add(int &x, int y) {
	x += y; if (x >= mod) x -= mod; return x;
}

int n, m, C[P][P], f[12][MAXN][MAXN], g[12][MAXN][MAXN], a[MAXN], k;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= k; i++) scanf("%d", a + i);
	C[0][0] = 1;
	for (int i = 1; i < P; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) Add(C[i][j], (C[i - 1][j - 1] + C[i - 1][j]) % mod);
	}
	for (int _ = 1; _ <= k; _++) {
		int now = a[_];
		for (int X = 1; X <= n; X++)
			for (int Y = 1; Y <= m; Y++) if (max(X, Y) <= a[_]) {
				int &tmp = g[_][X][Y]; tmp = C[X * Y][now];
				for (int x = 1; x <= X; x++)
					for (int y = 1; y <= Y; y++) if (x < X || y < Y) {
						int t = mod - (long long)g[_][x][y] * C[X][x] % mod;
						t = (long long)t * C[Y][y] % mod;
						Add(tmp, t);
					}
			}
	}
	f[0][0][0] = 1;
	for (int i = 1; i <= k; i++)
		for (int X = 1; X <= n; X++)
			for (int Y = 1; Y <= m; Y++) {
				int &tmp = f[i][X][Y];
				for (int x = 1; x <= X; x++)
					for (int y = 1; y <= Y; y++) {
						int t = (long long) f[i - 1][X - x][Y - y] * g[i][x][y] % mod;
						t = (long long)t * C[X][x] % mod;
						t = (long long)t * C[Y][y] % mod;
						Add(tmp, t);
					}
			}
	int Ans = 0;
	for (int x = 0; x <= n; x++)
		for (int y = 0; y <= m; y++) {
			int t = (long long)C[n][x] * f[k][x][y] % mod;
			t = (long long)C[m][y] * t % mod;
			Add(Ans, t);
		}
	printf("%d\n", Ans);
	return 0;
}
//#define Debug
#include <cstring>
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const long MAXN = 52;
	const long MAXS = 102;
	const long MAXM = 2009;
	const long inf = 0x3ddddddd;
	inline long Read(void) {
		long r = 0; int c;
		while (c = getchar(), !isdigit(c)){}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline char ReadChar(void) {
		char c;
		while (c = getchar(), !isupper(c)){}
		return c;
	}
	struct Node {
		long v, n, w; long s[MAXS][2];
	}a[MAXN];

	long n, m, root;
	void Input(void) {
		n = Read(), m = Read();
		long inp[MAXN] = {0};
		for (long i = 1; i <= n; i++) {
			a[i].v = Read();
			if (ReadChar() == 'A') {
				a[i].s[0][0] = Read();
				for (long j = 1; j <= a[i].s[0][0]; j++)
					inp[ a[i].s[j][0] = Read() ]++, a[i].s[j][1] = Read();
			}else {
				a[i].w = Read(), a[i].n = Read();
			}
		}
		for (root = 1; inp[root]; root++){}
	}
	#define max(a,b) ((a)>(b)?(a):(b))
	#define min(a,b) ((a)<(b)?(a):(b))
	long limit[MAXN] = {0}, temp[MAXN][MAXS][MAXM] = {0}, f[MAXN][MAXS][MAXM] = {0}, d[MAXN][MAXS][MAXM] = {0};
	void Dfs(long u) {
		long delta = a[u].v;
		if (a[u].s[0][0] == 0) {
			limit[u] = a[u].n;
			for (long i = 0; i <= limit[u] && a[u].w * i <= m; i++)
				f[u][i][a[u].w * i] = 0;
		}else {
			limit[u] = inf;
			for (long i = 1; i <= a[u].s[0][0]; i++) {
				Dfs(a[u].s[i][0]);
				delta -= (a[ a[u].s[i][0] ].v * a[u].s[i][1]);
				limit[u] = min(limit[u], limit[ a[u].s[i][0] ] / a[u].s[i][1]);
			}
			
			for (long i = 0; i <= limit[u]; i++)
				for (long j = 0; j <= m; j++)
					f[u][i][j] = d[ a[u].s[1][0] ][ i * a[u].s[1][1] ][j];

			for (long i = 2; i <= a[u].s[0][0]; i++) {
				for (long k = 0; k <= limit[u]; k++)
					for (long s = 0; s <= m; s++) {
						temp[u][k][s] = -inf;
						for (long p = 0; p <= s; p++)
							temp[u][k][s] = max(temp[u][k][s], f[u][k][p] + d[ a[u].s[i][0] ][k * a[u].s[i][1]][s - p]);
					}
				for (long k = 0; k <= limit[u]; k++)
					for (long s = 0; s <= m; s++)
						f[u][k][s] = temp[u][k][s];
			}
		}
		for (long i = 0; i <= m; i++)
			d[u][limit[u]][i] = f[u][limit[u]][i] + limit[u] * delta;
		for (long i = limit[u] - 1; i >= 0; i--)
			for (long j = 0; j <= m; j++)
				d[u][i][j] = max(d[u][i + 1][j], f[u][i][j] + delta * i);
		return;
	}
	void Work(void) {
		Input();
		memset(f, 192, sizeof f);
		memset(d, 192, sizeof d);
		f[root][0][0] = 0;
		Dfs(root);
		long A = 0;
		for (long i = 0; i <= m; i++) A = max(A, d[root][0][i]);
		printf("%ld\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}

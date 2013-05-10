#include <cstdio>
#include <cstring>
#define rep(i, n) for (long i = 0; i < n; i++)
namespace Solve {
	const long MAXN = 206;
	long n, m, x0, y0, k, f[MAXN][MAXN] = {0}, fim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};char map[MAXN][MAXN];
	struct pair{long l, r, d;}a[MAXN];
	struct Node{long d, k;Node():d(0),k(0){}Node(long l1, long l2):d(l1), k(l2){}};
	void Input(void) {
		scanf("%ld %ld %ld %ld %ld\n", &n, &m, &x0, &y0, &k);
		rep(i, n) scanf("%s", map[i]);
		rep(i, k) scanf("%ld %ld %ld", &a[i].l, &a[i].r, &a[i].d);
	}
	long A = 0;
	void Gao(long x, long y, long t, long pos) {
		long head = 1, tail = 0, p = 0;Node d[MAXN];
		while (0 <= x && x < n && 0 <= y && y < m) {
			if (map[x][y] == 'x') head = 1, tail = 0; else {
				while (tail >= head && d[tail].k + p <= f[x][y]) tail--;
				d[++tail] = Node(p, f[x][y] - p);
				if (p - d[head].d > pos) head++;
				f[x][y] = d[head].k + p;
				if (f[x][y] > A) A = f[x][y];
			}
			x += fim[t][0], y += fim[t][1], p++;
		}
	}
	void Work(void) {
		Input();
		memset(f, -101, sizeof f);f[x0 - 1][y0 - 1] = 0;
		rep(k, Solve::k) {
			long t = a[k].r - a[k].l + 1;
			if (a[k].d == 1) rep(j, m) Gao(n - 1, j, 0, t); else
			if (a[k].d == 2) rep(j, m) Gao(0, j, 1, t); else
			if (a[k].d == 3) rep(j, n) Gao(j, m - 1, 2, t); else
			if (a[k].d == 4) rep(j, n) Gao(j, 0, 3, t);
		}
		printf("%ld\n", A);
	}
}
int main(int argc, char** argv) {
	Solve::Work();
	return 0;
}

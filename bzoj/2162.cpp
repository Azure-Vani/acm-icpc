#include <cstdio>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= (n); i++)
namespace Solve {
	typedef long long Int65;
	const int MAXN = 103;
	const int MAXM = MAXN * MAXN;
	const int Mod = 19921228;
	const int inf = ~0U >> 3;

	int a[MAXN][MAXN];int n, k, m, vs, vt;

	inline void Input(void) {
		scanf("%d%d%d", &n, &k,&m);
		rep(i,n) rep(j,n) a[i][j + n] = inf;
		rep(i,m) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[x][y + n] = 0;
		}
		vs = (n << 1) + 1, vt = vs + 1;
		rep(i,n) a[vs][i] = n, a[i + n][vt] = n - 1;
	}

	int vis[MAXN], cur = 1, flow = 0;

	inline int Dfs(int u, int sum) {
		if (u == vt) return sum;
		vis[u] = cur;
		rep(i,(n << 1) + 2) if (a[u][i] > 0 && vis[i] != cur) {
			int t = Dfs(i, std::min(sum, a[u][i]));
			if (t) return a[u][i] -= t, a[i][u] += t, t;
		}
		return 0;
	}

	int X, Y;

	int c[3000][3000]; bool V[3000][3000];

	inline int C(int n, int m) {
		if (V[n][m]) return c[n][m];
		V[n][m] = true;
		if (m > n) return 0;
		if (m == 0 || n == m) return c[n][m] = 1ll;
		if (n == 0) return 0;
		return (Int65) (c[n][m] = ((Int65) C(n - 1, m - 1) + (Int65) C(n - 1, m)) % (Int65)Mod);
	}

	Int65 f[MAXN][MAXN];

	inline void Dec(Int65 &a, Int65 b) {a = (a - b) % Mod; if (a < 0) a += Mod;}
	inline Int65 Dp(void) {
		for (int i = 1; i <= X; i++)
			for (int j = 1; j <= Y; j++) {
				f[i][j] = C(i * j, k) % Mod;
				for (int di = 1; di <= i; di++)
					for (int dj = 1; dj <= j; dj++) if (di != i || dj != j)
						Dec(f[i][j], (Int65) C(i, di) * C(j, dj) % Mod * f[di][dj] % Mod);
			}
		return f[X][Y];
	}

	inline void Dfs(int u) {
		if (vis[u] == cur) return;
		vis[u] = cur;
		rep (i, (n<<1)+2) if (a[u][i]) Dfs(i);
	}

	inline void solve(void) {
		Input();
		int tmp;
		while (tmp = Dfs(vs, inf)) flow += tmp, cur++;
		cur++, Dfs(vs), cur++;
		rep(i,n) X += (vis[i] == cur-1), Y += (vis[i + n] != cur-1);
		printf("%d %d\n%lld\n", X, Y, Dp());
	}
}
int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

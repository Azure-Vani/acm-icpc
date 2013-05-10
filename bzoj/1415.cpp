//#define Debug
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
namespace Solve {
	const int MAXN = 1005;
	int next[MAXN][MAXN], inp[MAXN], a[MAXN][MAXN];
	double f[MAXN][MAXN];
	bool vis[MAXN][MAXN], map[MAXN][MAXN];

	int vs, vt, n, m;
	void Input(void) {
		scanf("%d%d%d%d", &n, &m, &vs, &vt);
		while (m--) {
			int x, y; scanf("%d%d", &x, &y);
			a[x][++inp[x]] = y;
			a[y][++inp[y]] = x;
			map[x][y] = map[y][x] = true;
		}
	}

	int level[MAXN];

	void Bfs(int u) {
		std::queue<int> Q;
		Q.push(u);
		level[u] = 0;
		while (Q.size()) {
			int now = Q.front(), t; Q.pop();
			for (int i = 1; i <= inp[now]; i++)
				if (level[t = a[now][i]] == -1)
					level[t] = level[now] + 1, Q.push(t);
		}
		for (int i = 1; i <= n; i++) if (i != u) {
			int best = 0x6eeeeeee, what, t;
			for (int j = 1; j <= inp[i]; j++)
				if (level[t = a[i][j]] < best || level[t] == best && what > t)
					what = t, best = level[t];
			next[i][u] = what;
		}
		next[u][u] = u;
	}

	void Initialize(void) {
		for (int i = 1; i <= n; i++) {
			memset(level + 1, -1, sizeof(level[0]) * n);
			Bfs(i);
		}
	}

	double Dp(int x, int y) {
		if (vis[x][y]) return f[x][y];
		vis[x][y] = true;
		if (x == y) return f[x][y] = 0;
		if (next[next[x][y]][y] == y) return f[x][y] = 1;

		double& Now = f[x][y];
		for (int i = 1; i <= inp[y]; i++)
			Now += Dp(next[next[x][y]][y], a[y][i]);
		Now += Dp(next[next[x][y]][y], y);
		Now = Now / (inp[y] + 1) + 1;
		return Now;
	}

	void solve(void) {
		Input();
		Initialize();
		printf("%.3lf\n", Dp(vs, vt));
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

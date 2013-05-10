#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 13;

	int dis[MAXN][MAXN], c[MAXN], n, m;
	int X[MAXN * MAXN], Y[MAXN * MAXN];

	void Input(void) {
		scanf("%d%d", &n, &m);
		memset(dis, 60, sizeof dis);
		for (int i = 1; i <= n; i++) scanf("%d", c + i), dis[i][i] = 0;
		for (int i = 1, x, y; i <= m; i++) {
			scanf("%d%d", &x, &y);
			dis[x][y] = dis[y][x] = 1;
			X[i] = x, Y[i] = y;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					dis[i][j] = std::min(dis[i][j], dis[i][k] + dis[k][j]);
	}

	class Status {public:
		int a[MAXN], h, step;
		void Set(int c[]) {
			h = 0, step = 0;
			for (int i = 1; i <= n; i++) {
				a[i] = c[i];
				h += dis[i][a[i]];
			}
		}
		inline Status Renew(int v1, int v2) {
			Status ret;
			memcpy(ret.a, a, sizeof a);
			ret.step = step + 1;
			ret.h = h + dis[a[v2]][v1] + dis[a[v1]][v2] - dis[a[v1]][v1] - dis[a[v2]][v2];
			std::swap(ret.a[v1], ret.a[v2]);
			return ret;
		}
	};

	int deep;

	void Dfs(Status Now) {
		if (Now.h == 0) {
			printf("%d\n", Now.step);
			exit(0);
		}
		if (Now.h + Now.step * 2 > deep) return;
		for (int i = 1; i <= m; i++)
			Dfs(Now.Renew(X[i], Y[i]));
	}

	void solve(void) {
		Input();
		Status begin; begin.Set(c);
		for (deep = begin.h;; deep++)
			Dfs(begin);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}

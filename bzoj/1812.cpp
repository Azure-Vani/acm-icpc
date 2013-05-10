//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;
	const int MAXK = 55;
	const int inf = 0x6eeeeeee;
	
	struct Edge {
		int y; Edge* next;
		Edge(int y, Edge* next):y(y), next(next){}
	}*a[MAXN];

	int n, k, w[MAXN], dis[MAXN];
	void Input(void) {
		scanf("%d%d", &n, &k);
		int x;
		for (int i = 2; i <= n + 1; i++) {
			scanf("%d%d%d", w + i, &x, dis + i);
			a[x + 1] = new Edge(i, a[x + 1]);
		}
	}

	int f[MAXN][MAXK][MAXN], path[MAXN][MAXN];;
	void Getson(int father, int u, int sum) {
		path[u][father] = sum;
		for (Edge* p = a[u]; p; p = p->next)
			Getson(father, p->y, sum + dis[p->y]);
	}

	void Dfs(int u) {
		int d[MAXN], nSon = 0;;
		for (Edge* p = a[u]; p; p = p->next)
			Dfs(p->y), d[++nSon] = p->y;

		int g[MAXN][MAXK] = {0};
		for (int father = 1; father <= n; father++, memset(g, 0, sizeof g)) if (path[u][father] != -1) {
			g[0][0] = w[u] * path[u][father];
			for (int i = 1; i <= nSon; i++)
				for (int j = 0; j <= k; j++) {
					int Temp = inf;
					for (int k = 0; k <= j; k++)
						Temp = std::min(Temp, g[i - 1][k] + std::min(f[d[i]][j - k][d[i]], f[d[i]][j - k][father]));
					g[i][j] = Temp;
				}
			for (int j = father == u ? 1 : 0; j <= k; j++)
				f[u][j][father] = g[nSon][father == u ? j - 1 : j];
		}
	}
	void solve(void) {
		Input();++k;++n;
		memset(path, -1, sizeof path);
		memset(f, 101, sizeof f);
		for (int i = 1; i <= n; i++)
			Getson(i, i, 0);
		Dfs(1);
		printf("%d\n", f[1][k][1]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

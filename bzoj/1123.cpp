#include <cstdio>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100009;

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge* next):y(y), next(next){}
	}*a[MAXN];
	
	int n, m;
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
	}

	int tim[MAXN], low[MAXN], cnt, sum[MAXN];
	Int64 S[MAXN];
	int Dfs(int u, int f) {
		low[u] = tim[u] = ++cnt;
		int tmp = 0;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
			if (tim[p->y] == 0) {
				sum[u] += Dfs(p->y, u);
				low[u] = std::min(low[u], low[p->y]);
				if (low[p->y] >= tim[u]) 
					S[u] += (Int64) ((Int64)sum[p->y] * (Int64)(sum[p->y] - 1)),
					tmp += sum[p->y];
			}else low[u] = std::min(low[u], tim[p->y]);
		}
		if (n - tmp >= 2)
			S[u] += (Int64) ((Int64)(n - tmp - 1) * (Int64)(n - tmp - 2));
		return ++sum[u];
	}

	Int64 Ans[MAXN];
	void solve(void) {
		Input();
		Dfs(1, 0);
		for (int i = 1; i <= n; i++)
			printf(LL "\n", (Int64) ((Int64)n * (Int64)(n - 1) - (Int64)S[i]));
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 100010;

	struct Edge {
		int y; Edge *next;
		Edge (int y, Edge *next):y(y), next(next){}
	}*a[MAXN], *e[MAXN];

	int n, m, Mod;
	void Input(void) {
		scanf("%d%d%d", &n, &m, &Mod);
		for (int i = 1; i <= m; i++) {
			int x, y; scanf("%d%d", &x, &y);
			e[x] = new Edge(y, e[x]);
		}
	}

	int tim[MAXN], cnt, low[MAXN], belong[MAXN], sum, stack[MAXN], top, num[MAXN];
	bool instack[MAXN];
	
	void Dfs(int u) {
		tim[u] = low[u] = ++cnt;
		instack[ stack[++top] = u ] = true;
		for (Edge *p = e[u]; p; p = p->next) if (!tim[p->y]) {
			Dfs(p->y);
			low[u] = std::min(low[u], low[p->y]);
		}else if (instack[p->y]) low[u] = std::min(low[u], tim[p->y]);
		if (low[u] == tim[u]) {
			sum++; int j;
			do {
				instack[j = stack[top--]] = false;
				belong[j] = sum;
				num[sum]++;
			}while (j != u);
		}
	}

	int inp[MAXN];

	void MakeGraph(void) {
		for (int i = 1; i <= n; i++)
			for (Edge *p = e[i]; p; p = p->next) if (belong[i] != belong[p->y]) {
				a[belong[i]] = new Edge(belong[p->y], a[belong[i]]);
				inp[belong[p->y]]++;
			}
		n = sum;
	}

	int d[MAXN], f[MAXN], g[MAXN], father[MAXN];
	void TopSort(void) {
		int head = 1, tail = 0;
		for (int i = 1; i <= n; i++) if (!inp[i]) d[++tail] = i, g[i] = 1;
		while (head <= tail) {
			int now = d[head++]; f[now] += num[now];
			for (Edge *p = a[now]; p; p = p->next) {
				if (!--inp[p->y]) d[++tail] = p->y;
				if (father[p->y] == now) continue; father[p->y] = now;
				if (f[now] > f[p->y]) 
					g[p->y] = g[now], f[p->y] = f[now];
				else if (f[now] == f[p->y])
					g[p->y] = (g[p->y] + g[now]) % Mod;
			}
		}
	}

	void solve(void) {
		Input();
		for (int i = 1; i <= n; i++) if (!tim[i]) Dfs(i);
		MakeGraph();
		TopSort();
		int Ans = 0;
		for (int i = 1; i <= n; i++) Ans = std::max(Ans, f[i]);
		int Count = 0;
		for (int i = 1; i <= n; i++) if (f[i] == Ans) Count = (Count + g[i]) % Mod;
		printf("%d\n%d\n", Ans, Count);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

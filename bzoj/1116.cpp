//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 100020;

	struct Edge {
		int y; Edge *next;
		Edge(int y , Edge *next):y(y), next(next){}
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

	bool flag = false, vis[MAXN];
	void Dfs(int u, int f) {
		vis[u] = true;
		for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y]) 
			Dfs(p->y, u);
		else if (p->y != f) flag = true;
	}

	void solve(void) {
		Input();
		for (int i = 1; i <= n; i++) if (!vis[i]) {
			flag = false;
			Dfs(i, 0);
			if (!flag) {puts("NIE"); return;}
		}
		puts("TAK");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

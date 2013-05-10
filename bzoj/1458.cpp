//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>
namespace Solve {
	const int MAXN = 305;
	const int MAXV = 300;

	int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct Edge {
		int y, f, now; Edge *next, *opt;
		Edge(int y, int f, Edge* next):y(y), f(f), next(next){}
	}*a[MAXN];

	int n, m, k, Sum, vs, vt;
	int RowNeed[MAXN], LineNeed[MAXN];
	bool map[MAXN][MAXN] = {0};

	void AddEdge(int x, int y, int f) {
		a[x] = new Edge(y, f, a[x]);
		a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	void Input(void) {
		n =ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= n; i++) RowNeed[i]  = ScanInt();
		for (int i = 1; i <= m; i++) LineNeed[i] = ScanInt();
		for (int i = 1; i <= k; i++) map[ScanInt()][ScanInt()] = true;
	}

	void Fail(void) {
		puts("JIONG!");
		exit(0);
	}

	void MakeGraph(void) {
		vs = n + m + 1, vt = vs + 1;
		for (int i = 1; i <= n; i++)
			for(int j = 1; j <= m; j++) if (!map[i][j])
				Sum++, LineNeed[j]--, RowNeed[i]--;
		for (int i = 1; i <= n; i++) if (RowNeed[i]  > 0) Fail();
		for (int i = 1; i <= m; i++) if (LineNeed[i] > 0) Fail();

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) if (!map[i][j])
				AddEdge(i, j + n, 1);
		for (int i = 1; i <= n; i++) AddEdge(vs, i, -RowNeed[i]);
		for (int i = 1; i <= m; i++) AddEdge(i + n, vt, -LineNeed[i]);
	}

	bool vis[MAXV] = {0};

	int Dfs(int u, int sum) {
		if (u == vt) return sum;
		vis[u] = true;
		for (Edge* p = a[u]; p; p = p->next) if (!vis[p->y] && p->f > 0) 
			if (int t = Dfs(p->y, std::min(sum, p->f))) return p->f -= t, p->opt->f += t, t;
		return 0;
	}
	int Flow(void) {
		int ret = 0;

		while (true) {
			memset(vis, 0, sizeof vis);
			if (int t = Dfs(vs, 0x6eeeeeee))
				ret += t;
			else break;
		}
		return ret;
	}
	void solve(void) {
		Input();
		MakeGraph();
		printf("%d\n", Sum - Flow());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

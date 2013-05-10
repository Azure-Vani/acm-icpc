//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
namespace Solve {
	const int MAXN = 100050;

	struct Edge {
		int y; Edge *next; int value;
		Edge(int y, Edge *next, int value):y(y), next(next), value(value){}
	}*e[MAXN], *a[MAXN];
	
	inline void AddEdge(int x, int y, int c, bool flag = false) {
		if (flag) a[x] = new Edge(y, a[x], c); else e[x] = new Edge(y, e[x], c);
	}

	void Fail(void) {puts("-1"); exit(0);}
	int n, m;

	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int type, x, y;
			scanf("%d%d%d", &type, &x, &y);
			if (type == 1) AddEdge(x, y, 0), AddEdge(y, x, 0); else
			if (type == 2) AddEdge(y, x, 1); else
			if (type == 3) AddEdge(x, y, 0); else
			if (type == 4) AddEdge(x, y, 1); else
			if (type == 5) AddEdge(y, x, 0);
		}
	}

	int time[MAXN], stack[MAXN], low[MAXN], belong[MAXN], num[MAXN], sum = 0, tim = 0;
	bool instack[MAXN]; int top = 0;

	void Dfs(int u) {
		low[u] = time[u] = ++tim;
		stack[++top] = u;
		instack[u] = true;
		for (Edge *p = e[u]; p; p = p->next) if (p->value == 0) {
			if (!time[p->y]) {
				Dfs(p->y);
				low[u] = std::min(low[u], low[p->y]);
			}else if (instack[p->y])
				low[u] = std::min(low[u], time[p->y]);
		}

		if (low[u] == time[u]) {
			sum++;
			int t = 0;
			do {
				t = stack[top--];
				instack[t] = false;
				belong[t] = sum;
				num[sum]++;
			}while (t != u);
		}
	}

	int inp[MAXN];
	void Tarjan(void) {
		for (int i = 1; i <= n; i++) if (!time[i]) 
			Dfs(i);
		
		for (int i = 1; i <= n; i++) 
			for (Edge *p = e[i]; p; p = p->next) {
				int x = belong[i], y = belong[p->y];
				if (x == y) {
					if (p->value == 1) Fail();
					continue;
				}
				AddEdge(x, y, p->value, true);
				inp[y]++;
			}
		n = sum;
	}
	
	int f[MAXN];
	int d[MAXN], head = 1, tail = 0;

	void TopSort(void) {
		for (int i = 1; i <= n; i++) if (inp[i] == 0) d[++tail] = i;
		
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) 
				if (--inp[p->y] == 0)
					d[++tail] = p->y;
		}
		if (tail < n) Fail();
		for (int i = tail; i >= 1; i--) {
			int t = d[i], limit = 1;
			for (Edge *p = a[t]; p; p = p->next)
				limit = std::max(limit, f[p->y] + p->value);
			f[t] = limit;
		}
		long long Ans = 0;
		for (int i = 1; i <= n; i++) Ans += (long long) (f[i] * num[i]);
		printf("%lld\n", Ans);
	}

	void solve(void) {
		Input();
		Tarjan();
		TopSort();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

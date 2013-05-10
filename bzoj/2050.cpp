//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 400009;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct Edge {
		int y; bool flag; Edge *next, *opt;
		Edge(int y, Edge* next):y(y), next(next){flag = true;}
	}*a[MAXN];

	struct pair {
		int x, y;
	}E[600010];

	int n, m;
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(); y += n;
			E[i].x = x, E[i].y = y;
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
	}
	
	bool match[MAXN]; 
	int levelx[MAXN >> 1], levely[MAXN], link[MAXN];
	int d[MAXN];

	inline bool Bfs(void) {
		int head = 1, tail = 0;
		memset(levely, 0, sizeof levely);
		for (int i = 1; i <= n; i++) {
			if (!match[i]) d[++tail] = i;
			levelx[i] = 0;
		}
		bool ret = false;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (levely[p->y] == 0) {
				levely[p->y] = levelx[now] + 1;
				if (link[p->y] == 0) ret = true;
				else levelx[link[p->y]] = levely[p->y] + 1, d[++tail] = link[p->y];
			}
		}
		return ret;
	}
	bool Find(int u) {
		for (Edge *p = a[u]; p; p = p->next) if (levely[p->y] == levelx[u] + 1) {
			levely[p->y] = 0;
			if (link[p->y] == 0 || Find(link[p->y])) {
				match[u] = true; link[p->y] = u;
				return true;
			}
		}
		return false;
	}

	inline void Match(void) {
		while (Bfs())
			for (int i = 1; i <= n; i++)
				if (!match[i]) Find(i);
	}

	inline void Adjust(void) {
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next)
				if (link[p->y] == i)
					p->opt->flag = false;
				else
					p->flag = false;
	}

	int cnt = 0, tim[MAXN], belong[MAXN], low[MAXN], sum = 0, stack[MAXN], top;
	bool in_stack[MAXN];

	void Dfs(int u) {
		tim[u] = low[u] = ++cnt;
		in_stack[stack[++top] = u] = true;
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			if (tim[p->y] == 0) {
				Dfs(p->y);
				low[u] = std::min(low[u], low[p->y]);
			}else if (in_stack[p->y]) 
				low[u] = std::min(low[u], tim[p->y]);
		}
		if (low[u] == tim[u]) {
			sum++; int j;
			do {
				j = stack[top--];
				in_stack[j] = false;
				belong[j] = sum;
			}while (j != u);
		}
	}

	void solve(void) {
		Input();
		Match();
		Adjust();
		for (int i = 1; i <= n * 2; i++)
			if (!tim[i])
				Dfs(i);
		for (int i = 1; i <= m; i++) {
			int x = E[i].x, y = E[i].y;
			if (belong[x] == belong[y])
				putchar('0');
			else 
				putchar('2'- (x == link[y]));
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

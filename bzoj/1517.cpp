//#define Debug
#include <cctype>
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace Solve {
	const int MAXN = 1000020;
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y; Edge *next, *opt; bool flag;
		Edge(int y, Edge *next):y(y), next(next) {flag = true;}
	}*a[MAXN];

	int n, L;
	inline void Input(void) {
		n = ScanInt(), L = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
		}
	}

	struct _{
		int m1, m2, w1, w2;
	}f[MAXN];

	int d[MAXN]; bool hash[MAXN];

	void FindPath(int u) {
		int head = 1, tail = 1;
		d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge* p = a[now]; p; p = p->next) if (!hash[p->y]) {
				d[++tail] = p->y;
			}
			hash[now] = true;
		}
		memset(hash, 0, sizeof hash);
		for (int i = tail; i >= 1; i--) {
			int u = d[i];
			for (Edge *p = a[u]; p; p = p->next) if (hash[p->y]) {
				if (f[p->y].m1 > f[u].m1) {
					f[u].m2 = f[u].m1, f[u].w2 = f[u].w1;
					f[u].m1 = f[p->y].m1 + 1, f[u].w1 = p->y;
				}else if (f[p->y].m1 > f[u].m2) {
					f[u].m2 = f[p->y].m1 + 1, f[u].w2 = p->y;
				}
			}
			if (f[u].m1 == 0) f[u].m1++;
			hash[u] = true;
		}
	}

	int root, c[MAXN], cnt, path[MAXN];

	inline void Prepare(void) {
		int best = 0, ID = 0;
		for (int i = 1; i <= n; i++)
			if (f[i].m1 + f[i].m2 > best)
				best = f[i].m1 + f[i].m2, ID = i;
		for (int i = ID; i; i = f[i].w1) root = i;
		int head = 1, tail = 1; d[1] = root;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				p->opt->flag = false;
				d[++tail] = p->y;
			}
		}
		for (int _ = n; _ >= 1; _--) {
			int t = d[_], ID = 0, best = 0;
			for (Edge *p = a[t]; p; p = p->next) if (p->flag && best < path[p->y]) 
				best = path[p->y], ID = p->y;
			path[t] = best + 1;
			for (Edge *p = a[t]; p; p = p->next) if (p->flag && p->y != ID)
				c[++cnt] = path[p->y];
		}
		c[++cnt] = path[d[1]];
	}

	inline void solve(void) {
		Input();
		FindPath(1);
		Prepare();
		std::sort(c + 1, c + cnt + 1);
		int Ans = 0;
		for (int i = cnt, t = L * 2 - 1; i >= 1 && t > 0;i--, t--)
			Ans += c[i];
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

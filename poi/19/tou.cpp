//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next, *opt; bool flag, bridge;
		Edge(int y, Edge *next):y(y), next(next){flag = true;}
	}*a[MAXN];
	int n, m, k;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
	}

	struct Node {
		Edge *begin; int u;
	}stack[MAXN]; int top = 0;

	int dfs[MAXN], *low, tim = 0, father[MAXN];

	inline void Dfs(int uu) {
		top = 1; stack[1].u = uu, stack[1].begin = a[uu];
		while (top) {
			Node &now = stack[top];
			int u = now.u;
			if (now.begin == a[u]) 
				dfs[u] = low[u] = ++tim;
			if (now.begin) {
				while (now.begin) {
					Edge *p = now.begin; now.begin = p->next;
					if (p->y > k && p->flag) {
						if (!dfs[p->y]) {
							p->opt->flag = false;
							stack[++top].u = p->y, stack[top].begin = a[p->y];
							father[p->y] = u;
							break;
						}else low[u] = min(low[u], dfs[p->y]);
					}
				}
			} else {
				if (father[u]) low[father[u]] = min(low[father[u]], low[u]);
				for (Edge *p = a[u]; p; p = p->next) if (p->y > k && p->opt->flag == false && low[p->y] > dfs[u]) {
					p->bridge = p->opt->bridge = true;
					p->opt->flag = true;
				}
				top--;
			}
		}
	}

	int color = 0, *d = dfs, *belong = father;
	inline void Bfs(int u) {
		int head = 1, tail = 1;
		d[1] = u; color++; belong[u] = color;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (!p->bridge && !belong[p->y]) {
				belong[ d[++tail] = p->y ] = color;
			}
		}
	}

	
	bool *vis; bool tag[MAXN]; int ans = 0;

	inline void Bfs2(int u, int fuck = 0) {
		int head = 1, tail = 1; d[1] = u; tag[belong[u]] = true;
		vis[u] = true;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				if (tag[belong[p->y]] && belong[now] > belong[p->y]) {
					if (fuck == 0) ans++; else printf("%d %d\n", min(p->y, p->opt->y), max(p->y, p->opt->y));
				}
				if (!vis[p->y]) {
					if (!tag[belong[p->y]]) p->opt->flag = false;
					vis[p->y] = true;
					tag[belong[p->y]] = true;
					d[++tail] = p->y;
				} else p->flag = true;
			}
		}
	}

	inline void BCC(void) {
		low = new int[n + 2];
		for (int i = k + 1; i <= n; i++) if (!dfs[i]) 
			Dfs(i);
		memset(father, 0, sizeof father);
		memset(low, 0, sizeof low);
		memset(dfs, 0, sizeof dfs);
		for (int i = 1; i <= n; i++) if (!belong[i]) {
			if (i <= k) belong[i] = ++color;
			else Bfs(i);
		}
		delete[] low;
		vis = new bool[n + 2]; memset(vis, 0, sizeof(bool) * (n + 1));
		for (int i = 1; i <= color; i++) if (!vis[i]) {
			Bfs2(i);
		}
		printf("%d\n", ans);
		memset(tag, 0, sizeof tag); memset(vis, 0, sizeof(bool) * (n + 1));
		for (int i = 1; i <= color; i++) if (!vis[i]) {
			Bfs2(i, 1);
		}
	}

	inline void solve(void) {
		Input();
		BCC();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}


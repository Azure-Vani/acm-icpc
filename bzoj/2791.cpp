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
	const int MAXN = 500010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	int n, m, father[MAXN], inp[MAXN];
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) inp[ father[i] = ScanInt() ]++, a[father[i]] = new Edge(i, a[father[i]]);
	}

	int d[MAXN], circle[MAXN], ncir = 0, deep[MAXN], sum[MAXN], root[MAXN], belong[MAXN];

	inline void Bfs(int u) {
		int head = 1, tail = 1; d[1] = u;
		while (head <= tail) {
			int now = d[head++];
			root[now] = u;
			circle[now] = ncir;
			for (Edge *p = a[now]; p; p = p->next) if (inp[p->y] == 0) {
				deep[p->y] = deep[now] + 1;
				d[++tail] = p->y;
			}
		}
		for (int i = tail; i > 1; i--) sum[father[d[i]]] += ++sum[d[i]];
		for (int i = 1; i <= tail; i++) {
			int son = -1, best = 0;
			if (!belong[d[i]]) belong[d[i]] = d[i];
			for (Edge *p = a[d[i]]; p; p = p->next) if (inp[p->y] == 0 && sum[p->y] > best)
				son = p->y, best = sum[p->y];
			belong[son] = belong[d[i]];
		}
	}

	int pos[MAXN], len[MAXN];

	inline void Init(void) {
		int tail = 0, head = 1;
		for (int i = 1; i <= n; i++) if (!inp[i]) d[++tail] = i;
		while (head <= tail) {
			int now = d[head++], f = father[now];
			if (!--inp[f]) d[++tail] = f;
		}
		for (int i = 1; i <= n; i++) if (inp[i] > 0) {
			int tmp = i, &l = len[++ncir];
			do {
				inp[tmp] = -1;
				Bfs(tmp);
				tmp = father[tmp];
				pos[tmp] = ++l;
			} while (tmp != i);
		}
	}

	inline int Lca(int x, int y) {
		while (true) {
			if (deep[x] > deep[y]) swap(x, y);
			if (belong[x] == belong[y]) return x;
			if (deep[belong[x]] < deep[belong[y]]) y = father[belong[y]]; else x = father[belong[x]];
		}
	}

	inline void Out(int x, int y, int l1, int l2) {
		if (max(deep[x] + l1, deep[y]) < max(deep[x], deep[y] + l2))
			printf("%d %d\n", deep[x] + l1, deep[y]);
		else if (max(deep[x] + l1, deep[y]) > max(deep[x], deep[y] + l2))
			printf("%d %d\n", deep[x], deep[y] + l2);
		else if (min(deep[x] + l1, deep[y]) < min(deep[x], deep[y] + l2))
			printf("%d %d\n", deep[x] + l1, deep[y]);
		else if (min(deep[x] + l1, deep[y]) > min(deep[x], deep[y] + l2))
			printf("%d %d\n", deep[x], deep[y] + l2);
		else if (deep[x] + l1 >= deep[y])
			printf("%d %d\n", deep[x] + l1, deep[y]);
		else
			printf("%d %d\n", deep[x], deep[y] + l2);
	}

	inline void Work(void) {
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			if (circle[x] != circle[y]) {
				puts("-1 -1");
				continue;
			}
			if (root[x] == root[y]) {
				int t = Lca(x, y);
				printf("%d %d\n", deep[x] - deep[t], deep[y] - deep[t]);
				continue;
			}
			int l1 = pos[root[y]] - pos[root[x]], l2 = pos[root[x]] - pos[root[y]];
			if (pos[root[x]] > pos[root[y]]) l1 += len[circle[x]]; 
			if (pos[root[x]] < pos[root[y]]) l2 += len[circle[x]];
			Out(x, y, l1, l2);
		}
	}

	inline void solve(void) {
		Input();
		Init();
		Work();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
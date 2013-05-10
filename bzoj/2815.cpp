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
	const int MAXN = 100010;

	struct Edge {
		int y; Edge *next; bool flag;
		Edge(int y, Edge *next, bool flag):y(y), next(next), flag(flag){}
	}*a[MAXN], *e[MAXN];

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline void AddEdge(int i, int t, Edge *a[]) {
		a[i] = new Edge(t, a[i], true);
		a[t] = new Edge(i, a[t], false);
	}

	int n; int inp[MAXN], f[20][MAXN], deep[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1, t; i <= n; i++) {
			while ((t = ScanInt())) {
				AddEdge(t, i, a);
				inp[i]++;
			}
		}
		for (int i = 1; i <= n; i++) if (!inp[i]) AddEdge(n + 1, i, a), inp[i]++;
		n++;
	}

	inline void Goup(int &a, int d) {
		for (int i = 18; i >= 0; i--) if (d & (1 << i))
			a = f[i][a];
	}

	inline int LCA(int a, int b) {
		if (deep[a] > deep[b]) swap(a, b);
		Goup(b, deep[b] - deep[a]);
		if (a == b) return a;
		for (int i = 18; i >= 0; i--) if (f[i][a] != f[i][b])
			a = f[i][a], b = f[i][b];
		return f[0][a];
	}

	int Ans[MAXN];
	inline int Dfs(int u) {
		Ans[u] = 1;
		for (Edge *p = e[u]; p; p = p->next) if (p->flag)
			Ans[u] += Dfs(p->y);
		return Ans[u];
	}

	int d[MAXN];
	inline void solve(void) {
		Input();
		int head = 1, tail = 1;
		d[1] = n;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag && !--inp[p->y]) {
				d[++tail] = p->y;
			}
		}
		for (int i = 2; i <= n; i++) {
			int t = 0, now = d[i];
			for (Edge *p = a[now]; p; p = p->next) if (!p->flag) {
				if (t) t = LCA(t, p->y); else t = p->y;
			}
			AddEdge(t, now, e);
			deep[now] = deep[t] + 1;
			f[0][now] = t;
			for (int j = 1; (1 << j) <= deep[now]; j++) f[j][now] = f[j - 1][f[j - 1][now]];
		}
		Dfs(n);
		for (int i = 1; i < n; i++) printf("%d\n", Ans[i] - 1);
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
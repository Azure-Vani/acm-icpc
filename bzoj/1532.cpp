//#define Debug
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
namespace Solve {
	const int MAXN = 21050;
	const int inf = 0x6eeeeeee;

	struct Edge {
		int y, z; Edge* next, *opt;
		Edge(){}
		Edge(int y, int z, Edge* next):y(y), z(z), next(next) {}
		void* operator new(size_t, void* p) {return p;}
	}*a[MAXN], POOL[MAXN << 2], *data = POOL;

	inline int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = (r << 1) + (r << 3) + c - '0';
		return r;
	}

	inline void AddEdge(int x, int y, int c) {
		a[x] = new((void*)data++) Edge(y, c, a[x]);
		a[y] = new((void*)data++) Edge(x, 0, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int n, m, vs, vt;
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		vs = n + m + 1, vt = vs + 1;
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			AddEdge(i, x + m, 1);
			AddEdge(i, y + m, 1);
			AddEdge(vs, i, 1);
		}
		for (int i = m + 1; i <= n + m; i++)
			AddEdge(i, vt, 0);
	}

	int level[MAXN], d[MAXN];
	bool Bfs(void) {
		int head = 1, tail = 1;
		d[1] = vs;memset(level, -1, sizeof level);level[vs] = 0;
		while (head <= tail) {
			int now = d[head++];
			for (Edge* p = a[now]; p; p = p->next) if (p->z > 0 && level[p->y] == -1)
					level[d[++tail] = p->y] = level[now] + 1;
		}
		return level[vt] != -1;
	}
	int Extend(int u, int sum) {
		if (u == vt) return sum;
		int r = 0, t;
		for (Edge* p = a[u]; p && r < sum; p = p->next) if (p->z > 0 && level[p->y] == level[u] + 1)
			r += t = Extend(p->y, std::min(sum - r, p->z)), p->z -= t, p->opt->z += t;
		if (!r) level[u] = -1;
		return r;
	}
	int Dinic(void) {
		int r = 0, t;
		while (Bfs()) while (t = Extend(vs, inf)) r += t;
		return r;
	}
	
	void Add(void) {
		for (int i = m + 1; i <= m + n; i++)
			a[i]->z++;
	}
	void Work(void) {
		int A = 0, last = 0, t;
		for (int i = 1;; i++) {
			Add();
			if (last + (t = Dinic()) == m) {
				A = i;
				break;
			}
			last += t;
		}
		printf("%d\n", A);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

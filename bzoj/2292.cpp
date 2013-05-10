//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <cstring>
namespace Solve {
	const int MAXN = 2000050;
	const int MAXM = 2000050;

	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y; Edge* next;
		Edge(){}
		Edge(int y, Edge* next):y(y), next(next){}
		inline void* operator new(size_t, void* p){return p;}
	}*a[MAXN], POOL[MAXM], *data = POOL;

	inline void Add(int x, int y) {
		a[x] = new((void*)data++)  Edge(y, a[x]);
	}

	int n, m, vs, vt;
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		vs = 1, vt = n;
		for (int _ = 1; _ <= m; _++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			if (z == 1)
				Add(x, y);
			else 
				Add(x, ++n), Add(n, y);
		}
	}

	int dis[MAXN];
	void Bfs(void) {
		memset(dis, -1, sizeof(int) * (n + 1));
		dis[vs] = 0;
		std::queue<int> Q;
		Q.push(vs);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge* p = a[now]; p; p = p->next)
				if (dis[p->y] == -1)
					dis[p->y] = dis[now] + 1, Q.push(p->y);
		}
		printf("%d\n", dis[vt]);
	}

	void solve(void) {
		Input();
		Bfs();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

//#define Debug
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define mp std::make_pair
namespace Solve {
	const int MAXN = 505;
	const int MAXV = MAXN * MAXN;

	#define Lab(x, y) (((x) - 1) * (m + 1) + y)
	int n, m; char ch[MAXN];

	struct Edge {
		int y, c; Edge *next;
		Edge(int y, int c, Edge* next):y(y), c(c), next(next){}
	}*a[MAXV];
	inline void AddEdge(int x, int y, int c) {
		a[x] = new Edge(y, c, a[x]);
		a[y] = new Edge(x, c, a[y]);
	}

	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++) {
			gets(ch + 1);
			for (int j = 1; j <= m; j++) {
				int t1 = 1, t2 = 0;
				if (ch[j] == '\\') std::swap(t1, t2);
				AddEdge(Lab(i, j), Lab(i + 1, j + 1), t1);
				AddEdge(Lab(i, j + 1), Lab(i + 1, j), t2);
			}
		}
	}

	int vs, vt, dis[MAXV];
	int Dijkstra(void) {
		std::priority_queue< std::pair<int, int> > T;
		memset(dis, 60, sizeof dis);
		dis[vs] = 0;
		T.push(mp(0, vs));
		for (int i = 1; i < vt; i++) {
			while (!T.empty() && -T.top().first > dis[T.top().second]) T.pop();
			if (T.empty()) break;
			int now = T.top().second; dis[now] = -T.top().first; T.pop();
			for (Edge *p = a[now]; p; p = p->next)
				if (dis[p->y] > dis[now] + p->c)
					T.push(mp(-(dis[p->y] = dis[now] + p->c), p->y));
		}
		return dis[vt] == dis[0] ? -1 : dis[vt];
	}

	void solve(void) {
		Input();
		vs = 1, vt = Lab(n + 1, m + 1);
		int Ans = Dijkstra();
		if (Ans == -1) puts("NO SOLUTION"); else printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

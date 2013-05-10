//#define Debug
#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#define pb push_back
#define MP std::make_pair
namespace Solve {
	const int MAXN = 420;
	const int MAXV = MAXN << 1;
	const int inf = 1000000000;

	struct Point {
		int x, y; 
		Point(){}; Point(int x, int y):x(x), y(y) {}
		bool operator ==(const Point& b) const{
			return x == b.x && y == b.y;
		}
	};
	struct DoublePoint {double x, y;}P;
	struct rect {
		Point P1, P2;
	}c[MAXN];

	int n;
	std::vector<Point> T;

	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d%d%d", &c[i].P1.x, &c[i].P1.y, &c[i].P2.x, &c[i].P2.y);
			T.pb(c[i].P1); T.pb(c[i].P2);
			T.pb(Point(c[i].P1.x, c[i].P2.y));
			T.pb(Point(c[i].P2.x, c[i].P1.y));
		}
		P.x = (c[1].P1.x + c[1].P2.x) / 2.0;
		P.y = (c[1].P1.y + c[1].P2.y) / 2.0;
	}

	struct Edge {
		int y, z; Edge *next;
		Edge (int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXV];
	inline void AddEdge(int x, int y, int z) {
		a[x] = new Edge(y, z, a[x]);
		a[y] = new Edge(x, z, a[y]);
	}

	inline bool Cross(const Point& a, const Point& b, const rect& c) {
		return !(std::max(a.x, b.x) <= c.P1.x || std::min(a.x, b.x) >= c.P2.x ||
			std::max(a.y, b.y) <= c.P1.y || std::min(a.y, b.y) >= c.P2.y);
	}

	#define Lev1(x) ((x) * 2)
	#define Lev2(x) ((x) * 2 + 1)
	#define dis(a, b) (abs(a.x - b.x) + abs(a.y - b.y))

	void MakeGraph(void) {
		int nPoint = T.size();
		for (int i = 0; i < nPoint - 1; i++)
			for (int j = i + 1; j < nPoint; j++) if (!(T[i] == T[j])) {
				bool OK = true;
				for (int k = 1; k <= n; k++)
					if (Cross(T[i], T[j], c[k])) {
						OK = false;
						break;
					}
				if (!OK) continue;
				int t = dis(T[i], T[j]);
				if (T[i].y >= P.y && T[j].y >= P.y  && std::min(T[i].x, T[j].x) <= P.x && std::max(T[i].x, T[j].x) >= P.x) {
					AddEdge(Lev1(i), Lev2(j), t);
					AddEdge(Lev2(i), Lev1(j), t);
				}else {
					AddEdge(Lev1(i), Lev1(j), t);
					AddEdge(Lev2(i), Lev2(j), t);
				}
			}
		n = Lev2(nPoint - 1) + 1;
	}

	int dis[MAXV];
	int Dijkstra(int u) {
		int vs = Lev1(u), vt = Lev2(u);
		std::fill(dis, dis + n + 1, inf);
		dis[vs] = 0;
		std::priority_queue< std::pair<int, int> > Q;
		Q.push(MP(0, vs));
		for (int i = 2; i <= n; i++) {
			while (!Q.empty() && dis[Q.top().second] < -Q.top().first) Q.pop();
			if (Q.empty()) break;
			int now = Q.top().second; dis[now] = -Q.top().first; Q.pop();
			for (Edge *p = a[now]; p; p = p->next)
				if (dis[p->y] > dis[now] + p->z)
					Q.push(MP(-(dis[p->y] = dis[now] + p->z), p->y));
		}
		return dis[vt];
	}

	void solve(void) {
		Input();
		MakeGraph();
		int Ans = inf;
		for (int i = 0; i < T.size(); i++) {
			int tmp = Dijkstra(i);
			Ans = std::min(Ans, tmp);
		}
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

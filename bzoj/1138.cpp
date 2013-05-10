//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
namespace Solve {
	const int MAXN = 405;
	
	struct Edge {
		int y, z; Edge *next;
		Edge(int y, int z, Edge* next):y(y), z(z), next(next){}
	}*a[MAXN], *rev_a[MAXN];
	
	int n, m;
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y, z; char c;
			scanf("%d%d %c", &x, &y, &c);
			z = c - 'a' + 1;
			a[x] = new Edge(y, z, a[x]);
			rev_a[y] = new Edge(x, z, rev_a[y]);
		}
	}
	
	int f[MAXN][MAXN][27], fuck; bool vis[MAXN][MAXN][27];
	struct Node {
		int x, y, c;
		Node(int x, int y, int c):x(x), y(y), c(c){}
	};
	
	void Spfa(void) {
		std::queue<Node> Q;
		memset(f, 60, sizeof f); fuck = f[0][0][0];
		for (int i = 1; i <= n; i++) Q.push(Node(i, i, 0)), vis[i][i][0] = true, f[i][i][0] = 0;
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next)
				Q.push(Node(i, p->y, 0)), vis[i][p->y][0] = true, f[i][p->y][0] = 1;
		while (!Q.empty()) {
			Node now = Q.front(); Q.pop();
			int X = now.x , Y = now.y, C = now.c;
			int t = f[X][Y][C];
			if (C) {
				for (Edge *p = a[Y]; p; p = p->next) if (p->z == C)
					if (t + 1 < f[X][p->y][0]) {
						f[X][p->y][0] = t + 1;
						if (!vis[X][p->y][0]) {
							Q.push(Node(X, p->y, 0));
							vis[X][p->y][0] = true;
						}
					}
			}else {
				for (Edge *p = rev_a[X]; p; p = p->next)
					if (t + 1 < f[p->y][Y][p->z]) {
						f[p->y][Y][p->z] = t + 1;
						if (!vis[p->y][Y][p->z]) {
							Q.push(Node(p->y, Y, p->z));
							vis[p->y][Y][p->z] = true;
						}
					}
				}
			vis[X][Y][C] = false;
			}
	}
	
	void Work(void) {
		int D, last;
		scanf("%d %d", &D, &last);
		for (int _ = 1, now; _ < D; _++) {
			scanf("%d", &now);
			if (last == now) puts("0"); else
			printf("%d\n", f[last][now][0] == fuck ? -1 : f[last][now][0]);
			last = now;
		}
	}
	void solve(void) {
		Input();
		Spfa();
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

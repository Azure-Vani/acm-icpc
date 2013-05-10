//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define mp std::make_pair
namespace Solve {
	const int MAXN = 205;
	const int MAXS = (1 << 17);
	
	struct Edge {
		int y, z, s;
		Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];
	
	#define Set(S, x) ((S) |= (1 << (x) - 1))
	int n, m, p, k, V[MAXN];
	void Input(void) {
		scanf("%d%d%d%d", &n, &m, &p, &k);
		for (int i = 1, t, u, w; i <= k; i++){
			scanf("%d%d", &w, &t);
			while (t--) {
				scanf("%d", &u);
				Set(V[w], u);
			}
		}
		for (int i = 1; i <= m; i++) {
			int x, y, z, cnt;
			scanf("%d%d%d", &x, &y, &z);
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
			scanf("%d", &cnt);
			for (int j = 1, tmp; j <= cnt; j++) {
				scanf("%d", &tmp);
				Set(a[x]->s, tmp);
				Set(a[y]->s, tmp);
			}
		}
	}
	
	int dis[MAXN][MAXS], inf; bool vis[MAXN][MAXS];
	int Spfa(void) {
		memset(dis, 60, sizeof dis); int ret = dis[0][0]; inf = ret;
		std::queue< std::pair<int, int> > Q;
		Q.push(mp(1, V[1]));
		dis[1][V[1]] = 0; vis[1][V[1]] = true;
		while (!Q.empty()) {
			int u = Q.front().first, S = Q.front().second; Q.pop();
			if (u == n) ret = std::min(ret, dis[u][S]);
			for (Edge *p = a[u]; p; p = p->next) if ((S | p->s) == S) {
				int tmp = S | V[p->y];
				if (dis[u][S] + p->z < dis[p->y][tmp]) {
					dis[p->y][tmp] = dis[u][S] + p->z;
					if (!vis[p->y][tmp]) 
						vis[p->y][tmp] = true, Q.push(mp(p->y, tmp));
				}
			}
			vis[u][S] = false;
		}
		return ret;
	}

	void solve(void) {
		Input();
		int Ans = Spfa();
		printf("%d\n", Ans >= inf ? -1 : Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

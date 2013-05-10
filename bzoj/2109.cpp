//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <algorithm>
namespace Solve {
	const int MAXN = 2050;
	
	struct Edge {
		int y; Edge* next;
		Edge(int y, Edge* next):y(y), next(next) {}
	}*a[MAXN];
	struct Point {
		int ID, Limit;
		friend bool operator <(const Point& a, const Point& b) {
			return a.Limit < b.Limit;
		}
	}P[MAXN];

	int n, m;
	int inp[MAXN];
	
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", &P[i].Limit), P[i].ID = i;
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[y] = new Edge(x, a[y]);
			inp[x]++;
		}
	}

	void Topsort(void) {
		std::queue <int> Q;
		for (int i = 1; i <= n; i++)
			if (!inp[i])
				Q.push(i);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge* p = a[now]; p; p = p->next) {
				int t = p->y;
				P[t].Limit = std::min(P[t].Limit, P[now].Limit - 1);
				inp[t]--;
				if (!inp[t])
					Q.push(t);
			}
		}
	}

	int Res[MAXN];
	bool vis[MAXN];

	int Dfs(int u) {
		vis[u] = true;
		int res = 0;
		for (Edge* p = a[u]; p; p = p->next)
			if (!vis[p->y])
				res += Dfs(p->y);
		return res + 1;
	}

	void Cal(void) {
		std::sort(P + 1, P + n + 1);
		for (int i = 1; i <= n; i++) {
			memset(vis, 0, sizeof vis);
			int Num = 0;
			Res[i] = Num = Dfs(i);
			for (int j = 1; j <= n; j++)
				if (!vis[P[j].ID]) {
					Num++;
					if (P[j].Limit <= Res[i])
						Res[i]++;
					else 
					if (P[j].Limit < Num)
						Res[i] = P[j].Limit + 1;
				}
		}
	}

	void solve(void) {
		Input();
		Topsort();
		Cal();
		for (int i = 1; i < n; i++) printf("%d ", Res[i]);
		printf("%d\n", Res[n]);
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 210;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, m, S;

	struct Edge {
		int y, c; Edge *next; bool flag;
		Edge(int y, int c, Edge *next):y(y), c(c), next(next){flag = false;}
	}*a[MAXN], *e[MAXN];

	double P[MAXN][MAXN];

	inline void Input(void) {
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
		S = ScanInt();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= S; j++) {
				cin >>P[i][j];
			}
		}
	}

	priority_queue<pair<int, int> > Q;
	int dis[MAXN];

	inline void Dijkstra(int s) {
		memset(dis, 55, sizeof dis); dis[s] = 0; Q.push(mp(0, s));
		for (int i = 1; i < n; i++) {
			while (!Q.empty() && dis[Q.top().second] != -Q.top().first) Q.pop();
			if (Q.empty()) break; 
			int now = Q.top().second; Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (dis[p->y] > dis[now] + p->c) 
				Q.push(mp(-(dis[p->y] = dis[now] + p->c), p->y));
		}
	}

	double f[MAXN][MAXN];
	inline void Dfs(int u) {
		int son = 0;
		for (Edge *p = a[u]; p; p = p->next) if (dis[p->y] == dis[u] + p->c) {
			son++;
			Dfs(p->y);
		}
		if (!son) {
			for (int i = 1; i <= S; i++) f[u][i] = P[u][i];
		} else {
			for (int i = 0; i <= S; i++) f[u][i] = 1;
			for (Edge *p = a[u]; p; p = p->next) if (dis[p->y] == dis[u] + p->c) {
				for (int i = S; i >= 0; i--) {
					double tmp = 1;
					for (int j = 0; j <= i; j++) {
						tmp = min(tmp, f[u][j] * (1 - f[p->y][i - j]) / (double) son);
					}
					f[u][i] = tmp;
				}
			}
			for (int i = S; i >= 0; i--) {
				for (int j = 0; j <= i; j++) {
					f[u][i] = min(f[u][i], f[u][i - j] * (1 - P[u][j]));
				}
				f[u][i] = 1 - f[u][i];
			}
		}
	}

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			Input();
			Dijkstra(1);
			Dfs(1);
			printf("%.2lf\n", f[1][S]);
		}
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

//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
namespace Solve {
	const int MAXN = 65;

	double k, c[MAXN], pow[MAXN];
	int n, m, inp[MAXN], p[MAXN], dis[MAXN], temp[MAXN];
	double f[MAXN][MAXN][MAXN];

	typedef std::queue<int> V;
	struct Edge {
		int y; Edge* next;
		Edge(int y, Edge* next):y(y), next(next){}
	}*a[MAXN];

	void Input(void) {
		scanf("%d%d%lf", &n, &m, &k);
		for (int i = 1; i <= n; i++) scanf("%d", p + i), inp[p[i]]++, a[p[i]] = new Edge(i, a[p[i]]);
		for (int i = 1; i <= n; i++) scanf("%lf", c + i);
		pow[0] = 1;
		for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * k;
	}

	inline void OnlyDp(int u, int Q[], int n, int d, int m, bool change) {
		double g[MAXN][MAXN] = {0}, F[MAXN][MAXN] = {0};
		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= m; j++)
				g[i][j] = std::max(f[Q[i]][j][d + 1], f[Q[i]][j][1]);

		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= m; j++) {
				double Temp = 0;
				for (int k = 0; k <= j; k++)
					Temp = std::max(F[i - 1][k] + g[i][j - k], Temp);
				F[i][j] = Temp;
			}
		for (int j = 0; j <= m; j++)
			f[u][j + change][d] = F[n][j] + c[u] * pow[d];
	}

	void Dfs(int u) {
		int d[MAXN] = {0}, n = 0;
		for (Edge* p = a[u]; p; p = p->next)
			if (!temp[p->y])
				Dfs(d[++n] = p->y);

		for (int i = Solve::p[u] == 1 ? 1 : 2; i <= dis[u]; i++)
			OnlyDp(u, d, n, i, m, false);

		if (Solve::p[u] != 1 && u != 1)
			OnlyDp(u, d, n, 1, m - 1, true);
		if (u == 1)
			OnlyDp(u, d, n, 0, m, false);
	}
	int TreeDp(int inp[]) {
		memset(f, 0, sizeof f);
		V Q;
		for (int i = 1; i <= n; i++) if (!inp[i]) Q.push(i);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			if (!--inp[p[now]]) Q.push(p[now]);
		}
		int ret = 0;
		for (int i = 1; i <= n; i++) if (inp[i])
			Dfs(i), ret++;
		return ret;
	}

	double CircleDp(int inp[], bool flag) {
		int d[MAXN] = {0}, n = 0;
		for (int i = 1; i <= Solve::n; i++)
			if (inp[i]) d[++n] = i;

		double F[MAXN][MAXN] = {0};
		m -= flag;
		for (int i = 1; i <= n; i++)
			for (int j = 0; j <= m; j++) {
				double Temp = 0;
				for (int k = 0; k <= j; k++)
					Temp = std::max(Temp, F[i - 1][k] + f[d[i]][j - k][dis[d[i]]]);
				F[i][j] = Temp;
			}
		double ret = F[n][m]; m += flag;
		return ret;
	}
	void Bfs(void) {
		V Q; memset(dis + 1, 0, sizeof(int) * n);
		Q.push(1); dis[1] = 0;
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge* p = a[now]; p; p = p->next)
				if (!dis[p->y] && p->y != 1) {
					dis[p->y] = dis[now] + 1; Q.push(p->y);}
		}
	}

	void Dfs(int u, int delta) {
		if (u == 1) return;
		dis[u] += delta;
		for (Edge* p = a[u]; p; p = p->next)
			Dfs(p->y, delta);
	}

	void FuckFuckFuck(void) {
		double ret = 0;int len = 0;
		for (int i = 1; i <= n; i++) {
			ret += c[i] * pow[dis[i]];
			if (inp[i])
				len++;
		}
		printf("%.2lf\n", ret / (1 - pow[len]));
		exit(0);
	}
	void Work(void) {
		int seg[MAXN] = {0};
		memcpy(seg + 1, inp + 1, sizeof(int) * n);
		V Q;

		for (int i = 1; i <= n; i++) 
			if (!inp[i])
				Q.push(i);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			if (!--inp[ p[now] ])
				Q.push(p[now]);
		}

		Bfs();
		if (!m) FuckFuckFuck();
		int t, disbake[MAXN] = {0}; double Ans = 0;
		memcpy(disbake + 1, dis + 1, sizeof(int) * n);

		for (int i = 2; i <= n; i++) if (inp[i] && (t = p[i]) != 1){
			memcpy(temp + 1, seg + 1, sizeof (int) * n);
			memcpy(dis + 1, disbake + 1, sizeof(int) * n);
			Dfs(i, 1 - dis[i]);
			temp[1]++, temp[t]--;
			p[i] = 1;
			int len = TreeDp(temp);
			p[i] = t;
			double ret = CircleDp(temp, true);
			Ans = std::max(Ans, ret / (1 - pow[len]));
		}
		
		memcpy(temp + 1, seg + 1, sizeof(int) * n);
		memcpy(dis + 1, disbake + 1, sizeof(int) * n);
		int len = TreeDp(temp);
		double ret = CircleDp(temp, false);
		Ans = std::max(Ans, ret / (1 - pow[len]));

		printf("%.2lf", Ans);
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

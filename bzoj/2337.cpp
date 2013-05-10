#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;

	struct Edge {
		int y, c; Edge *next;
		Edge(int y, int c, Edge* next):y(y), c(c), next(next){}
	}*a[MAXN];

	int n, m, MaxH, inp[MAXN];
	inline void Input(void) {
		scanf("%d%d", &n, &m);
		while (m--) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			a[x] = new Edge(y, z, a[x]);
			if (x != y) a[y] = new Edge(x, z, a[y]);
			MaxH = std::max(MaxH, z);
			inp[x]++, inp[y] += (x != y);
		}
	}
	
	double f[MAXN], c[MAXN][MAXN], Ans;

	inline void Prepare(int bit) {
		memset(c, 0, sizeof c);
		for (int i = 1; i < n; i++) {
			int cnt = 0;
			for (Edge *p = a[i]; p; p = p->next)
				if (p->c & (1 << bit))
					c[i][p->y]++, cnt++;
				else
					c[i][p->y]--;
			c[i][i] += inp[i], c[i][n + 1] = cnt;
		}
		c[n][n] = 1;
	}

	inline void Gauss(void) {
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) if (c[j][i]) {
				double slope = c[j][i] / c[i][i];
				for (int k = i + 1; k <= n + 1; k++)
					c[j][k] -= c[i][k] * slope;
			}
		}
		for (int i = n; i >= 1; i--) {
			double sum = 0;
			for (int j = i + 1; j <= n; j++)
				sum += c[i][j] * f[j];
			f[i] = (c[i][n + 1] - sum) / c[i][i];
		}
	}

	inline void Work(void) {
		for (int i = 0; (1 << i) <= MaxH; i++) {
			Prepare(i);
			Gauss();
			Ans += f[1] * (1 << i);
		}
		printf("%.3lf\n", Ans);
	}
	
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}

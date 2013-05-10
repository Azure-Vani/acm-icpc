//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 100020;
	struct Edge {
		int y; Edge *next, *opt; bool flag;
		Edge(int y, Edge *next):y(y), next(next){flag = true;}
	}*a[MAXN];

	int n, v[MAXN];
	inline void Input(void) {
		scanf("%d", &n);
		for (int i = 1, x, y; i < n; i++) {
			scanf("%d%d", &x, &y);
			a[x] = new Edge(y, a[x]), a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
		}
		for (int i = 1, u; i <= n; i++) scanf("%d", &u), v[u] = i;
	}

	class BIT{public:
		int a[MAXN], n;
		#define Lowbit(x) ((x) & (-(x)))
		inline void Set(int _n){n = _n;}
		inline void Insert(int u, int t){for (int i = u; i <= n; i += Lowbit(i)) a[i] += t;}
		inline int Cal(int u) {int ret = 0; for (int i = u; i >= 1; i -= Lowbit(i)) ret += a[i];return ret;}
	}T;

	int Ans[MAXN];
	void Dfs(int u) {
		Ans[v[u]] = T.Cal(v[u] - 1);
		T.Insert(v[u], 1);
		for (Edge *p = a[u]; p; p = p->next) if (p->flag)
			p->opt->flag = false, Dfs(p->y);
		T.Insert(v[u], -1);
	}
	void solve(void) {
		Input();
		T.Set(n);
		Dfs(1);
		for (int i = 1; i <= n; i++) printf("%d\n", Ans[i]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
}

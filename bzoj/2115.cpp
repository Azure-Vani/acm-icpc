//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 50020;
	const int MAXM = 200020;
	struct Edge {
		int y; Int64 z; Edge *next;
		Edge(int y, Int64 z, Edge *next):y(y),next(next), z(z){}
	}*a[MAXN];

	int n, m;
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y; Int64 z;
			scanf("%d%d"LL, &x, &y, &z);
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
	}

	Int64 level[MAXN], s[MAXM]; int cnt = 0, deep[MAXN];;
	void Dfs(int u, Int64 sum) {
		level[u] = sum;
		for (Edge *p = a[u]; p; p = p->next) if (level[p->y] == -1) {
			deep[p->y] = deep[u] + 1;
			Dfs(p->y, sum ^ p->z);
		}else 
			if ((level[p->y] ^ p->z ^ sum) != 0 && deep[p->y] < deep[u]) 
				s[++cnt] = level[p->y] ^ p->z ^ sum;
	}

	Int64 gss[65];
	void solve(void) {
		Input(); memset(level, -1, sizeof level);
		Dfs(1, 0ll);
		Int64 Ans = level[n];
		for (int i = 1; i <= cnt; i++) for (int j = 60; j >= 0; j--)
			if (((s[i] >> j) & 1) > 0) if (gss[j] == 0) {gss[j] = s[i];break;}
			else s[i] ^= gss[j];
		for (int i = 60; i >= 0; i--)
			if (((Ans >> i) & 1) == 0 && gss[i] > 0) Ans ^= gss[i];
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

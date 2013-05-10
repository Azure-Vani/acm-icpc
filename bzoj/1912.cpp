//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#include <queue>
namespace Solve {
	const int MAXN = 100050;
	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, z; Edge *next;
		Edge(int y, Edge* next):y(y), next(next){z = 1;}
	}*a[MAXN];
	int n, k;

	void Input(void) {
		n = ScanInt(), k =ScanInt();
		for (int i = 1, x, y; i < n; i++) x = ScanInt(), y = ScanInt(), a[x] = new Edge(y, a[x]), a[y] = new Edge(x, a[y]);
	}
	
	struct pair {int d;Edge *index;}No1[MAXN], No2[MAXN];
	void Dfs(int u, int last) {
		for (Edge *p = a[u]; p; p = p->next) if (p->y != last) {
			Dfs(p->y, u);
		}
		No1[u].d = No2[u].d = -0x6eeeeeee; No1[u].index = No2[u].index = NULL;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != last) {
			int t = No1[p->y].d + p->z;
			if (t > No1[u].d) {
				No2[u] = No1[u];
				No1[u].index = p; No1[u].d = t;
			}else
			if (t > No2[u].d) {
				No2[u].d = t, No2[u].index = p;
			}
		}
		if (No1[u].d == -0x6eeeeeee) No1[u].d = 0; if (No2[u].d == -0x6eeeeeee) No2[u].d = 0;
	}
	void Change(Edge *p) {
		p->z *=-1;
		if (No1[p->y].index) Change(No1[p->y].index);
	}
	int Work(void) {
		Dfs(1, 0);
		int ret = 0, which = 0;
		for (int i = 1; i <= n; i++) if (ret < No1[i].d + No2[i].d) ret = No1[i].d + No2[i].d, which = i;
		if (No1[which].index) Change(No1[which].index);
		if (No2[which].index) Change(No2[which].index);
		return ret;
	}
	void solve(void) {
		Input();
		int Ans = 0;
		for (int i = 1; i <= k; i++)
			Ans += Work();
		printf("%d\n", (n - 1) * 2 - Ans + k);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

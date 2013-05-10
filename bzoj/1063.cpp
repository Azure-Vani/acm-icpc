//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
namespace Solve {
	const int MAXN = 100005;
	typedef long long ll;
	int Mod;

	inline int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y; bool flag; Edge* next, *opt;
		Edge(int y, Edge* next):y(y), next(next){flag = true;}
	}*a[MAXN];

	int n, m;
	void Input(void) {
		n = ScanInt(), m = ScanInt(), Mod = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
		}
	}
	
	int Dfs(int u) {
		int ret = 1;
		for (Edge* p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			ret += Dfs(p->y);
		}
		return ret;
	}

	int f[MAXN][10][3]; bool zero[MAXN][10][3];
	int Ans;

	void Dp(int u) {
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			Dp(p->y);
		}
		for (int b = 0; b <= Ans; b++) {
			f[u][b][0] = 1;
			zero[u][b][0] = true;
			for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
				int t = p->y, &a0 = f[u][b][0], &a1 = f[u][b][1], &a2 = f[u][b][2], l0 = 0, l1 = 0;
				l0 = f[t][b - 1][0] + f[t][b - 1][1] + f[t][b - 1][2];
				l1 = f[t][b][0] + f[t][b][1];
				bool t0 = zero[t][b - 1][0] || zero[t][b - 1][1] || zero[t][b - 1][2], t1 = zero[t][b][0] || zero[t][b][1];
				ll _a0, _a1, _a2;
				a2 = (_a2 = (ll)l1 * (ll)a1 + (ll)l0 * (ll)a2) % Mod;
				a1 = (_a1 = (ll)l0 * (ll)a1 + (ll)l1 * (ll)a0) % Mod;
				a0 = (_a0 = (ll)l0 * (ll)a0) % Mod;
				zero[u][b][2] = (t1 && zero[u][b][1]) || (t0 && zero[u][b][2]);
				zero[u][b][1] = (zero[u][b][1] && t0) || (t1 && zero[u][b][0]);
				zero[u][b][0] &= t0;
			}
		}
	}

	void Work(void) {
		for (Ans = 0; Ans <= 10; Ans++) {
			Dp(1);
			if (zero[1][Ans][0] || zero[1][Ans][1] || zero[1][Ans][2]) {
				printf("%d\n%d\n", Ans, (int)(((ll)f[1][Ans][0] + (ll)f[1][Ans][1] + (ll)f[1][Ans][2]) % Mod));
				return;
			}
			memset(f, 0, sizeof f);
			memset(zero, 0, sizeof zero);
		}
	}
	void solve(void) {
		Input();
		if (Dfs(1) != n) {printf("-1\n-1\n"); return;}
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

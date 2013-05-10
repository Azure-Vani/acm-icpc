//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 605;
	const int MAXM = 20010;

	struct Point {
		int x, y;
		inline void Scan(void) {scanf("%d%d", &x, &y);}
	}vertex[MAXN], sheep[MAXM];

	int Mod, nVerticex, nSheep;
	void Input(void) {
		scanf("%d%d%d", &nVerticex, &nSheep, &Mod);
		for (int i = 0; i < nVerticex; i++) vertex[i].Scan();
		for (int i = 1; i <= nSheep; i++) sheep[i].Scan();
	}
	
	bool OK[MAXN][MAXN]; Point Now;

	#define Cross(a, b, c) ((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x))

	int sum[MAXN][MAXN];
	void Prepare(void) {
		memset(OK, true, sizeof OK);
		for (int k = 1; k <= nSheep; k++) {
			int t = 1, d = 0;
			for (int i = 0; i < nVerticex; i++) {
				while (t != i && (d = Cross(vertex[t], sheep[k], vertex[i])) <= 0) {
					if (d == 0) OK[i][t] = OK[t][i] = false;
					t = (t + 1) % nVerticex;
				}
				if (t != i)
					sum[i][t]++;
			}
		}
		for (int i = 0; i < nVerticex; i++) {
			int s = 0;
			for (int delta = 2; delta < nVerticex; delta++) {
				s += sum[i][(i + delta) % nVerticex];
				if (s & 1)
					OK[i][(i + delta) % nVerticex] = OK[(i + delta) % nVerticex][i] = false;
			}
		}
	}

	int f[MAXN][MAXN]; bool vis[MAXN][MAXN];
	int DP(int l, int r) {
		if (r - l <= 2) return f[l][r] = 1;
		if (vis[l][r]) return f[l][r];
		vis[l][r] = true;
		int &ret = f[l][r];
		for (int i = l + 1; i <= r - 1; i++) if (OK[i][l] && OK[i][r]) {
			int t1 = DP(l, i);
			int t2 = DP(i, r);
			ret = (ret + t1 * t2 % Mod) % Mod;
		}
		return ret;
	}
	void solve(void) {
		Input();
		Prepare();
		DP(0, nVerticex - 1);
		printf("%d\n", f[0][nVerticex - 1]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("owc.in", "r", stdin);
		freopen("owc.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

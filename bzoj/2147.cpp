//#define Debug
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstdlib>
namespace Solve {
	const int MAXN = 102;
	const int MAXM = 901;
	const int MAXT = 10;

	int n, s1, s2, d;

	void Make(int s) {
		int Ans[105] = {0};
		for (int i = 1; i <= n; i++) {
			if(i != n) {
				Ans[i] = s > 9 ? 9 : s - 1;
				s -= Ans[i];
			}else Ans[i] = s;
		}
		for (int i = n; i >= 1; i--) printf("%d", Ans[i]);
		puts("");
	}

	unsigned int f[4][MAXM][MAXM][MAXT]; int Ans[MAXN];
	
	bool Read(int u, int s1, int s2, int rest, bool tmp = 0) {
		int t = (u - 1) / 31, r = (u - 1) % 31;
		unsigned int& ret = f[t][s1][s2][rest];
		if (tmp) ret |= (1ll << r);
		return (ret & (1ll << r));
	}
	int nn;
	bool Dfs(int u, int s1, int s2, int rest) {
		if (s1 < 0 || s2 < 0 || s1 > u * 9 || s2 > u * 9 || (s1 * d) % 9 != (s2 + rest) % 9) return false;
		if (u == 0) {
			if (s1 == 0 && s2 == 0 && rest == 0) {
				for (int i = nn; i >= 1; i--) printf("%d", Ans[i]);
				puts("");
				exit(0);
			}
			return false;
		}
		bool now = Read(u, s1, s2, rest);
		if (now) return false; Read(u, s1, s2, rest, 1);
		for (int i = u == n ? 1 : 0; i < 10; i++) {
			int t1 = (rest * 10 + i) / d, t2 = (rest * 10 + i) % d;
			if (u == nn && t1 == 0) continue;
			Ans[u] = t1;
			Dfs(u - 1, s1 - t1, s2 - i, t2);
		}
	}

	void solve(void) {
		scanf("%d%d%d%d", &n, &s1, &s2, &d); nn = n;
		if (d == 0) {
			if (s2 != 0) {puts("-1"); return;}
			Make(s1);
			return;
		}
		Dfs(n, s1, s2, 0);
		Dfs(++n, s1, s2, 0);
		puts("-1");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

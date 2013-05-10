//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 2005;
	
	int n, m;
	int f[MAXN], f_opt[MAXN], c[MAXN];
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
			scanf("%d", c + i);
	}

	int Mod(int a) {
		if (a > 0) a %= 10;
		else while (a < 0) a += 10;
		return a;
	}
	void Work(void) {
		f[0] = 1;
		for (int i = 1; i <= n; i++)
			for (int j = m; j >= c[i]; j--)
				f[j] = (f[j] + f[j - c[i]]) % 10;
		for (int i = 1; i <= n; i++) {
			memcpy(f_opt, f, sizeof (int) * c[i]);
			for (int j = c[i]; j <= m; j++)
				f_opt[j] = Mod(f[j] - f_opt[j - c[i]]);
			for (int j = 1; j <= m; j++)
				putchar(f_opt[j] + '0');
			puts("");
		}
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

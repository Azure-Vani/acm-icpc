#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
namespace Solve {
	const int MAXN = 1010;

	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	int n, root, p[MAXN], num[MAXN];
	int c[MAXN], Ans = 0;

	void Input(void) {
		Ans = 0;
		memset(p, 0, sizeof p); memset(c, 0, sizeof(c)); memset(num, 0, sizeof num);
		scanf("%d%d", &n, &root); if (!(n + root)) exit(0);
		for (int i = 1; i <= n; i++)
			Ans += (c[i] = ScanInt()), num[i] = 1;
		for (int i = 1, x, y; i < n; i++) {
			x = ScanInt(), y = ScanInt();
			p[y] = x;
		}
	}

	void Work(void) {
		for (int i = 1; i <= n; i++) {
			double max = 0;int which = 0;
			for (int i = 1; i <= n; i++) if (i != root && c[i]  > max * num[i]) {
				which = i;
				max = (double)c[i] / (double)num[i];
			}
			for (int i = 1; i <= n; i++)
				if (p[i] == which) p[i] = p[which];
			Ans += num[p[which]] * c[which];
			num[p[which]] += num[which];
			c[p[which]] += c[which];
			c[which] = 0;
		}
		printf("%d\n", Ans);
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	while (true)
	Solve::solve();
	return 0;
}

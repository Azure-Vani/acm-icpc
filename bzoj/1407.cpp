#define Debug
#include <cstdio>
#include <algorithm>
#include <cstdlib>
namespace Solve {
	const int MAXN = 17;
	struct {
		int c, p, l;
	}a[MAXN];

	int n, M = 0;
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].c, &a[i].p, &a[i].l), M = std::max(M, a[i].c), a[i].c--;
		M--;
	}
	inline int Mod(int a, int b) { return (a % b + b) % b; }
	inline int gcd(int a, int b) { return !b ? a : gcd(b, Mod(a, b));}

	void ex_gcd(int a, int b, int &x, int& y) {
		if (!b) {
			x = 1, y = 0;
			return;
		}
		ex_gcd(b, Mod(a, b), x, y);
		int t = x; x = y, y = t - a / b * y;
	}

	inline int Gao(int a, int b, int c) {
		int t = gcd(abs(a), abs(b)); if (a < 0 || b < 0) t = -t;
		if (Mod(c, t) != 0) return 1521521521;
		int x = 0, y = 0;
		a /= t, b /= t, c /= t;
		ex_gcd(a, b, x, y);
		x *= c;
		while (x < 0) x += b; while (x > b) x -= b;
		return x;
	}

	inline bool check(void) {
		for (int j = 2; j <= n; j++)
			for (int i = 1; i < j; i++) {
				int t = Gao(a[i].p - a[j].p, -M, a[j].c - a[i].c);
				if (t <= std::min(a[i].l, a[j].l)) return true;
			}
		printf("%d\n", M);
		exit(0);
	}

	void solve(void) {
		Input();
		while (++M, check());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
	#endif
	Solve::solve();
	return 0;
}

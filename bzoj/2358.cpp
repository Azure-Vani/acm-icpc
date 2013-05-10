//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define cl(a) memset(a, 0, sizeof a);
namespace Solve {
	const int MAXN = 10020;

	int a[MAXN], b[MAXN], c[MAXN], d[MAXN];

	inline int ScanInt(int a[]) {
		int c, l = 0;
		while (c = getchar(), !isdigit(c)) {}
		a[++l] = c - '0';
		while (c = getchar(),  isdigit(c)) a[++l] = c - '0';
		std::reverse(a + 1, a + l + 1);
		return l;
	}

	inline void Add(int a[], int b[]) {
		int c[MAXN] = {0}, n = std::max(a[0], b[0]);
		for (int i = 1; i <= n; i++) c[i] = a[i] + b[i];
		for (int i = 1; i <= n; i++)
			c[i + 1] += c[i] / 10, c[i] %= 10;
		if (c[n + 1]) n++;
		c[0] = n;
		memcpy(a, c, sizeof c);
	}

	void solve(void) {
		cl(a) cl(b) cl(c) cl(d)
		a[0] = ScanInt(a);
		b[0] = ScanInt(b);
		c[0] = ScanInt(c);
		d[0] = ScanInt(d);
		Add(b, d);
		int t1 = (a[1]&1)^(c[1]&1), t2 = 0;
		for (int i = 1; i <= b[0]; i++) t2 += b[i];
		puts(t1==(t2%3)?"0":"1");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int p; scanf("%d", &p); while (p--)
	Solve::solve();
	return 0;
}

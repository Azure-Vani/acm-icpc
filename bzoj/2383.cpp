//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 200010;

	inline int ScanInt(void) {
		int c = 0, r = 0, d;
		while (c = getchar(), !isdigit(c) && c != '-') {}
		if (c != '-') r = c - '0'; d = c;
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	
	int a[MAXN], r[MAXN], n;

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt(), r[i] = ScanInt();
	}

	long double f[MAXN];

	inline long double Cal(int j, int i) {
		return (long double) (a[i] - a[j]) * (a[i] - a[j]) / (4 * f[j]);
	}

	int stack[MAXN], top = 0;

	inline void Work(void) {
		f[1] = r[1]; stack[++top] = 1;
		for (int i = 2; i <= n; i++) {
			long double &tmp = f[i]; tmp = r[i];
			while (top) {
				tmp = std::min(tmp, Cal(stack[top], i));
				if (tmp >= f[stack[top]]) top--; else break;
			}
			stack[++top] = i;
		}
		for (int i = 1; i <= n; i++) printf("%.3Lf\n", f[i]);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w",stdout);
	#endif
	Solve::solve();
	return 0;
}

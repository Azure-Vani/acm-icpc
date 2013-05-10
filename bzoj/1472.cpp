//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <stack>
#include <cstring>
namespace Solve {
	const int MAXN = 100050;
	int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int f[MAXN], L[MAXN], R[MAXN], n, g[MAXN];
	int h[MAXN], p[MAXN];
	void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) p[i] = ScanInt(), h[i] = ScanInt();
	}

	void Iniliatize(void) {
		std::stack<int> Q, T;
		for (int i = 1, t; i <= n; i++) {
			L[i] = i;
			while (Q.size() && p[i] - p[t = Q.top()] <= h[i]) L[i] = L[t], Q.pop();
			Q.push(i);
		}
		for (int i = n, t; i >= 1; i--) {
			R[i] = i;
			while (T.size() && p[t = T.top()] - p[i] <= h[i]) R[i] = R[t], T.pop();
			T.push(i);
		}
	}

	void Work(void) {
		memset(g, 60, sizeof g); memset(f, 60, sizeof f);
		f[0] = g[0] = 0;
		for (int i = 1; i <= n; i++) {
			f[i] = std::min(f[i - 1], g[i - 1]) + 1;
			for (int j = L[i]; j <= i; j++)
				f[i] = std::min(f[j], f[i]);
			g[i] = std::min(g[i], std::min(f[i - 1], g[i - 1]) + 1);
			for (int j = i; j <= R[i]; j++)
				g[j] = std::min(g[j], g[i]);
		}
		printf("%d\n", std::min(f[n], g[n]));
	}
	void solve(void) {
		Input();
		Iniliatize();
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

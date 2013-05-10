#include <cstdio>
#include <algorithm>
#include <cctype>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 20010;
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, c; Edge *next;
		Edge(int y, int c, Edge *next):y(y), c(c), next(next){}
	}*a[MAXN];
	int n;

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt(), c = ScanInt() % 3;
			a[x] = new Edge(y, c, a[x]);
			a[y] = new Edge(x, c, a[y]);
		}
	}

	int f[MAXN][3], p[MAXN], d[MAXN], g[MAXN];
	Int64 Ans = 0;
	inline Int64 gcd(Int64 a, Int64 b) {
		return !b?a:gcd(b,a%b);
	}

	inline void Work(void) {
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->y != Solve::p[now]) {
				Solve::p[d[++tail] = p->y] = now;
			}
		}
		for (int u = n; u >= 1; u--) {
			register int i = d[u];
			g[i] = Ans;
			for (Edge *p = a[i]; p; p = p->next) if (p->y != Solve::p[i]) {
				f[i][p->c]++;
				for (int j = 0; j < 3; j++) 
					f[i][(j + p->c) % 3] += f[p->y][j];
				register int t = (p->c ^ 3) % 3, l1, l2;
				Ans -= (Int64) f[p->y][t] * (f[p->y][t] - 1);
				t = (p->c * -2) % 3; if (t < 0) t += 3;
				Ans -= f[p->y][t] * 2;
				if (p->c == 2) l1 = 2; else l1 = p->c ^ 1;
				if (p->c == 1) l2 = 1; else l2 = p->c ^ 2;
				Ans -= (Int64) f[p->y][l1] * f[p->y][l2] * 2ll;
			}
			Ans += (Int64) f[i][0] * f[i][0] + 1 + f[i][0];
			Ans += (Int64) f[i][1] * f[i][2] * 2ll;
			g[i] = Ans - g[i];
		}
		Int64 t = gcd(Ans, n * n);
		printf(LL "/%d\n", Ans / t, n * n / t);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}
int main(void) {
	//freopen("1.in", "r", stdin);
	Solve::solve();
	return 0;
}

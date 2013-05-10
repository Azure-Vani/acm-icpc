//#define Debug
#include <cstdio>
namespace Solve {
	const int MAXN = 125;
	const int MAXM = 300;
	const int LL = 1000000;
	struct Big {
		int a[MAXM], n;
		inline int& operator ()(int u) {return a[u];}
		void Go(void) {
			for (int i = 1; i <= n; i++)
				a[i + 1] += a[i] / LL, a[i] %= LL;
			if (a[n + 1]) n++;
		}
		void Put(void) {
			printf("%d", a[n]);
			for (int i = n - 1; i >= 1; i--) {
				for (int j = 10; j < LL; j *= 10)
					if (a[i] < j) putchar('0');
				printf("%d", a[i]);
			}
			puts("");
		}
	};

	void Add(Big& a, Big& b) {
		for (int i = 1; i <= b.n; i++)
			a(i) += b(i);
		if (b.n > a.n) a.n = b.n;
		a.Go();
	}
	Big f[MAXN][MAXN];
	int n;

	void solve(void) {
		scanf("%d", &n);
		f[1][1].n = f[1][1](1) = 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				int u; scanf("%d", &u);
				if (!u) continue;
				/*if (i + u <= n)*/ Add(f[i + u][j], f[i][j]);
				/*if (j + u <= n)*/ Add(f[i][j + u], f[i][j]);
			}
		f[n][n].Put();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		//freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

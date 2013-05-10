//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
namespace Solve {
	const long MAXN = 10050;
	struct Edge {
		long y; bool flag; Edge* next, *opt;
		Edge(long y, Edge* next):y(y), next(next){flag = true;}
	}*a[MAXN];
	inline long Read(void) {
		long r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c))  r = r * 10 + c - '0';
		return r;
	}

	long n;
	inline void Input(void) {
		n = Read();
		memset(a, 0, sizeof (a[0]) * (n + 1));
		for (long i = 1; i < n; i++) {
			long x = Read(), y = Read();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
		}
	}
	long A = 0;
	bool Dfs(long u) {
		long t = 0;
		for (Edge* p = a[u]; p; p = p->next)
			if (p->flag) {
				p->opt->flag = false;
				t += Dfs(p->y);
			}
		A += (t >= 2 ? t - 1 : 0);
		return (t < 2);
	}
	void solve(void) {
		Input();
		A = 0;
		A += Dfs(1);
		printf("%ld\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	long T; scanf("%ld", &T);
	while (T--)
		Solve::solve();
	return 0;
}

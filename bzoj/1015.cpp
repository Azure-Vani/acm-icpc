//#define Debug
#include <cstdio>
#include <cctype>
namespace Solve {
	const long MAXN = 400050;

	inline long Read(void) {
		long r = 0; int ch;
		while(ch = getchar(), !isdigit(ch)){}
		r = ch - '0';
		while(ch = getchar(), isdigit(ch)) r = r * 10 + ch - '0';
		return r;
	}
	long n, m, D[MAXN] = {0}, k, f[MAXN] = {0}, A;
	bool hash[MAXN] = {0};
	struct Edge {
		long y; Edge* next;
		Edge(long y, Edge* next):y(y), next(next){}
	}*a[MAXN];

	long Find(long x) {if (f[x] == x) return x; else return f[x] = Find(f[x]);}
	inline void Mix(long x, long y) {
		long l1 = Find(x), l2 =Find(y);
		if (l1 != l2) {
			f[l1] = f[l2];
			A--;
		}
	}
	bool F[MAXN] = {0};
	void Input(void) {
		n = Read(), m = Read();
		for (long i = 1; i <= m; i++) {
			long x = Read(), y = Read();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
		k = Read();
		for (long i = 1; i <= k; i++) hash[ D[i] = Read() ] = true;
		for (long i = 0; i < n; i++) f[i] =i;
		for (long i = 0; i < n; i++)
			if (!hash[i]) {
				for (Edge* p = a[i]; p; p = p->next)
					if (!hash[p->y])
						Mix(i, p->y);
			}
		A = 0;
		long t;
		for (long i = 0; i < n; i++)
			if (!hash[i] && !F[ t = Find(i)]) A++, F[t] = true;
	}
	long Q[MAXN] = {0};
	void Work(void) {
		Input();
		Q[k + 1] = A;
		for (long i = k; i >= 1; i--) {
			long u = D[i];
			hash[u] = false;
			A++;
			for (Edge *p = a[u]; p; p = p->next)
				if (!hash[p->y]) 
					Mix(u, p->y);
			Q[i] = A;
		}
		for (long i = 1; i <= k + 1; i++)
			printf("%ld\n", Q[i]);
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}

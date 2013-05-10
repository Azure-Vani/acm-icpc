//#define Debug
#include <cstdio>
#include <cctype>
namespace Solve {
	const long MAXN = 1000050;
	inline long Read(void) {
		long r = 0; char c;
		while (c = getchar(), !isdigit(c)) {};
		r = c- '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	long n, f[MAXN] = {0};
	long Find(long x) {
		if (f[x] == x) return x;
		else return f[x] = Find(f[x]);
	}
	void Input(void) {
		n = Read();
		long u;
		for (long i = 1; i <= n; i++) f[i] = i;
		for (long i = 1; i <= n; i++) {
			u = Read();
			f[Find(i)] = Find(u);
		}
	}
	bool hash[MAXN] = {0};
	void Work(void) {
		Input();
		long A = 0;
		for (long i = 1; i <= n; i++) {
			long t = Find(i);
			if (!hash[t]) {
				A++;
				hash[t] = true;
			}
		}
		printf("%ld\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}

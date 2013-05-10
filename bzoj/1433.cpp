//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
namespace Solve {
	const long MAXN = 52;
	bool c[MAXN][MAXN] = {0}, inS[MAXN] = {0}, Back[MAXN] = {0}, a[MAXN][MAXN] = {0};
	long n;
	inline long Read(void) {
		long r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	void Input(void) {
		n = Read();
		for (long i = 1; i <= n; i++) inS[i] = Read();
		for (long i = 1; i <= n; i++) Back[i] = Read();
		for (long i = 1; i <= n; i++)
			for (long j = 1;  j <= n; j++) 
				c[i][j] = Read();
		for (long i = 1; i <= n; i++) c[i][i] = true;
	}
	long r[MAXN] = {0}; bool vis[MAXN] = {0};
	bool Dfs(long u) {
		for (long i = 1; i <= n; i++)
			if (a[u][i] && !vis[i]) {
				vis[i] = true;
				if (!r[i] || Dfs(r[i])) {
					r[i] = u;
					return true;
				}
			}
		return false;
	}
	void Work(void) {
		memset(a, 0, sizeof a);
		memset(Back, 0, sizeof Back);
		memset(r, 0, sizeof r);
		Input();
		long N = 0;
		for (long i = 1; i <= n; i++) if (!inS[i] || !Back[i]) {
			N++;
			for (long j = 1; j <= n; j++) 
				if (inS[j] && c[i][j])
					a[i][j] = true;
		}
		long A = 0;
		for (long i = 1; i <= n; i++) {
			memset(vis, 0, sizeof vis);
			A += Dfs(i);
		}
		puts(A == N ? "^_^" : "T_T");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	long T; scanf("%ld", &T);
	while (T--)
		Solve::Work();
	return 0;
}

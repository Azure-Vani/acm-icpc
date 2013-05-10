//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
namespace Solve {
	const long MAX = 222;
	inline long Read(void) {
		long r = 0; char c;
		while (c = getchar(), !isdigit(c)){}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	long n, M[MAX][MAX] = {0}, r[MAX] = {0}, vis[MAX] = {0};
	bool Dfs(long u) {
		for (long i = 1; i <= n; i++)
			if (M[u][i] && !vis[i]) {
				vis[i] = true;
				if (!r[i] || Dfs(r[i])) {
					r[i] = u;
					return true;
				}
			}
		return false;
	}
	void Work(void) {
		n = Read();
		memset(M, 0, sizeof M);
		memset(r, 0, sizeof r);
		for (long i = 1; i <= n; i++)
			for (long j = 1; j <= n; j++)
				M[i][j] = Read();
		long A = 0;
		for (long i = 1; i <= n; i++) {
			memset(vis, 0, sizeof vis);
			A += Dfs(i);
		}
		puts(A == n ? "Yes" : "No");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	long T;
	scanf("%ld\n", &T);
	while (T--) 
		Solve::Work();
	return 0;
}

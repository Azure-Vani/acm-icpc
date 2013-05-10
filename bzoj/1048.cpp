#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
namespace Solve{
	const long inf = 1000000000;
	const long MAXN = 12;

	long Read(void) {
		long r; int ch, cs;
		while(ch = getchar(), !isdigit(ch) && ch != '-');
		if(ch != '-') r = ch - '0';
		while(cs = getchar(), isdigit(cs)) r = (r << 1) + (r << 3) + cs - '0';
		if(ch == '-') return -r;else return r;
	}
	
	long n, m, K, S[MAXN][MAXN] = {0}, f[MAXN][MAXN][MAXN][MAXN][MAXN] = {0};
	#define Sum(lx,ly,rx,ry) (S[rx][ry] - S[lx - 1][ry] - S[rx][ly - 1] + S[lx - 1][ly - 1])
	#define Sqr(x) ((x) * (x))
	long Dfs(long lx, long ly, long rx, long ry, long k) {
		if( (rx - lx + 1) * (ry - ly + 1) < k ) return inf;
		if(f[lx][ly][rx][ry][k] != -1) return f[lx][ly][rx][ry][k];
		if(k == 1)
			return f[lx][ly][rx][ry][k] = Sqr( Sum(lx, ly, rx, ry) );
		
		long r = inf;
		for (long i = lx; i < rx; i++)
			for (long j = 1; j < k; j++){
				long l1 = Dfs(lx, ly, i, ry, j);
				long l2 = Dfs(i + 1, ly, rx, ry, k - j);
				r = std::min(r, l1 + l2);
			}

		for (long i = ly; i < ry; i++)
			for (long j = 1; j < k; j++) {
				long l1 = Dfs(lx, ly, rx, i, j);
				long l2 = Dfs(lx, i + 1, rx, ry, k - j);
				r = std::min(r, l1 + l2);
			}
		return f[lx][ly][rx][ry][k] = r;
	}

	void Input(void) {
		memset(f, -1, sizeof f);
		n = Read(), m = Read(), K = Read();
		for(long i = 1; i <= n; i++)
			for (long j = 1; j <= m; j++)
				S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + Read();
		double avg = S[n][m] / double(K);
		long long P = Dfs(1,1,n,m,K);

		printf("%.2lf\n", std::sqrt(double(P) / double(K) - Sqr( avg ) ) );
	}
}
int main(int arge, char ** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Input();
	return 0;
}

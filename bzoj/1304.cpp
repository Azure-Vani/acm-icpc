#include <cstdio>
#include <cctype>
#include <cstring>
namespace Solve{
	#define min(a,b) ( (a) < (b) ? (a) : (b) )
	const long MAXN = 10500;
	
	long Read(void) {
		long r; int ch;
		while (ch = getchar(), !isdigit(ch) );
		r = ch - '0';
		while (ch = getchar(),isdigit(ch) ) r = ( r << 1) + ( r <<3 ) + ch - '0';
		return r;
	}
	struct Edge {
		long y; Edge *next, *opt; bool flag;
		Edge( long y,Edge* next ) : y(y), next(next) { flag = true; }
	}*a[MAXN];
	
	long m,n; bool c[MAXN] = {0};
	void Input(void) {
		n = Read(), m = Read();
		for (long i = 1; i <= m; i++) c[i]=Read();
		for (long i = 1; i < n; i++) {
			long x = Read(), y = Read();
			a[x] = new Edge (y, a[x]);
			a[y] = new Edge (x, a[y]);
			a[x] -> opt = a[y], a[y] -> opt = a[x];
		}
	}
	
	long f[MAXN][3]={0};
	
	long Dfs(long u, long flag) {
		if ( f[u][flag] != -1 ) return f[u][flag];
		if ( u <= m) {
			if (c[u] == flag) f[u][flag] = 0;
			else f[u][flag] = 1;
			return f[u][flag];
		}
		
		long l1 = 0, l2 = 1, l3 = 1;
		for (Edge *p = a[u]; p; p = p ->next)
			if (p->flag) {
				p -> opt -> flag= false;
				l1 += Dfs(p->y, flag);
				l2 += Dfs(p->y, 1);
				l3 += Dfs(p->y, 0);
			}
		return f[u][flag] = min( l1, min( l2, l3) );
	}
	void solve(void) {
		memset (f, -1, sizeof f);
		Input();
		Dfs ( m+1, 2 );
		printf( "%ld\n", f[m+1][2]);
	}
}
int main(int argc,char** argv){
	#ifdef Debug
		freopen("1.in","r",stdin);
	#endif
	Solve::solve();
	return 0;
}

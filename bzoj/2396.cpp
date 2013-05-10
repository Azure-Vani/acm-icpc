//#define Debug
#include <cstring>
#include <cctype>
#include <cstdio>
#include <algorithm>
#define cl(a) memset(a, 0, sizeof a);
#define rep(i,n) for(int i = 1; i <= n; i++)
namespace Solve {
	typedef unsigned long long Int64;
	const int MAXN = 1005;

	inline int ScanInt(void) {
		int c, r = 0;
		while(!isdigit(c = getchar()));
		r = c - '0';
		while(isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}
	
	Int64 a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN], M[MAXN];
	int n;

	inline void read(Int64 a[MAXN][MAXN]) {
		rep(i,n) rep(j,n) a[i][j] = ScanInt();
	}

	void Input(void) { n = -1;
		scanf("%d", &n); if (n < 0) exit(0);
		cl(a); cl(b); cl(c);
		read(a); read(b); read(c);
	}
	
#define Multi(a, b, c) {\
	rep(i, n) {Int64 tmp = 0; rep(j, n) tmp += a[j] * b[j][i]; c[i] = tmp;}\
}

	Int64 t1[MAXN], t2[MAXN], t3[MAXN];
	bool Work(void) {
		cl(t1); cl(t2); cl(M); cl(t3);
		for (int i = 1; i <= n; i++) M[i] = rand();
		Multi(M, a, t1);
		Multi(t1, b, t3); 
		Multi(M, c, t2);
		for (int i = 1; i <= n; i++) if (t3[i] != t2[i]) return false;
		return true;
	}

	void solve(void) {
		Input();
		puts((Work())?"Yes":"No");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	while (true)
	Solve::solve();
	return 0;
}
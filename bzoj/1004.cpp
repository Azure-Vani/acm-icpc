//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const long MAXN = 62;
	inline long Read(void) {
		long r = 0;int ch;
		while(ch = getchar(), !isdigit(ch) );
		r = ch - '0';
		while(ch = getchar(), isdigit(ch) ) r = r * 10 + ch -'0';
		return r;
	}
	long s1, s2, s3, m, p, k;

	inline long MOD(long x, long y){ if( x > y ) return x % y;else return x < 0 ? x + y : x;}
	long EX_E(long a, long b, long& x, long& y) {
		if( b == 0 ) {
			x = 1, y= 0;
			return a;
		}else{
			long r = EX_E(b, a % b, x, y);
			long t = x;x = y, y = t - a / b * y;
			return r;
		}
	}
	inline long Get(long a, long b) {
		if( b <= 0 ) return -1;
		long x, y;
		long r = EX_E(a, b, x, y);
		if( r != 1 ) return -1;else
		return MOD(x, b);
	}
	void solve(void) {
		s1 = Read(), s2 = Read(), s3 = Read(), m = Read(), p = Read();
		long A = 0;
		for(long oo = 0; oo <= m; oo++) {
			long N[MAXN] = {0}, S[MAXN] = {0}, l = 0;
			if(oo)
				for (long i = 1; i <= s1 + s2 + s3; i++) N[i] = Read();
			else
				for (long i = 1; i <= s1 + s2 + s3; i++) N[i] = i;

			bool hash[MAXN] = {0};
			for (long i = 1; i <= s1 + s2 + s3; i++) 
				if( !hash[i] ) {
					hash[i] = true;
					long j = N[i];
					S[ ++l ] = 1;
					while(j != i) {
						hash[j] = true;
						S[l]++;
						j = N[j];
					}
				}

			long f[MAXN][MAXN][MAXN] = {0};
			f[0][0][0] = 1;
			for (long i = 1; i <= l; i++) 
				for (long l1 = s1; l1 >= 0; l1--)
					for (long l2 = s2; l2 >= 0; l2--)
						for (long l3 = s3; l3 >= 0; l3--) {
							if( S[i] <= l1) f[l1][l2][l3] = (f[l1][l2][l3] + f[l1 - S[i]][l2][l3]) % p;
							if( S[i] <= l2) f[l1][l2][l3] = (f[l1][l2][l3] + f[l1][l2 - S[i]][l3]) % p;
							if( S[i] <= l3) f[l1][l2][l3] = (f[l1][l2][l3] + f[l1][l2][l3 - S[i]]) % p;
						}
			A = (A + f[s1][s2][s3]) % p;
		}
		A = (A * Get(m + 1, p)) % p;
		printf("%ld\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

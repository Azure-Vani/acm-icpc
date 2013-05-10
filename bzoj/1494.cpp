//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
long k;
namespace Solve {
	const long MAXN = 60;
	const long MAXA = 55556;
	const long K = 10;
	long MOD = 65521;
	typedef long long ll;

	long connect[K] = {0}, state[MAXN][K] = {0}, S = 0, fim[MAXA] = {0};
	ll M[MAXN][MAXN] = {0};
	ll n;

	inline long Cal(long *a) {
		long r = 0;
		for (long i = 1; i <= k; i++)
			r = r * 10 + a[i];
		return r;
	}
	void Dfs(long u, long p) {
		if (u == k + 1) {
			memcpy(state[++S], connect, sizeof connect);
			return;
		}
		for (long i = 1; i <= p + 1; i++){
				connect[u] = i;
				Dfs(u + 1, i > p ? i : p);
		}
	}

	void Adjust(long* a) {
		long base = 0, c[K] = {0};
		for (long i = 1; i <= k; i++)
			if (!c[i]) {
				base++;
				for (long j = i; j <= k; j++)
					if (a[j] == a[i])
						c[j] = base;
			}
		memcpy(a, c, sizeof c);
	}

	long temp[K] = {0};
	void Find(long k, long p, bool flag) {
		if (p > ::k) {
			long now[K] = {0}, c = temp[0] ? state[k][ temp[1] ] : 6;
			for (long i = 2; i <= ::k; i++)
				for (long j = 1; j <= temp[0]; j++)
					if (state[k][i] == state[k][temp[j]])
						now[i - 1] = c;
			for (long i = 2; i <= ::k; i++)
				if (!now[i - 1])
					now[i - 1] = state[k][i];
			now[::k] = c;
			Adjust(now);
			long start = fim[ Cal(state[k]) ];
			long end = fim[ Cal(now) ];
			M[end][start]++;
			return;
		}
		bool check = true;
		for (long i = 1; i <= temp[0]; i++)
			if (state[k][p] == state[k][temp[i]]) {
				check = false;
				break;
			}
		if (check) {
			temp[ ++temp[0] ] = p;
			Find(k, p + 1, flag);
			temp[ temp[0]-- ] = p;
		}
		if (p != 1 || !flag)
			Find(k, p + 1, flag);
	}

	#define Mult(a, b) {\
		ll c[MAXN][MAXN] = {0};\
		for (long i = 1; i <= S; i++)\
			for (long j = 1; j <= S; j++) {\
				ll temp = 0;\
				for (long k = 1; k <= S; k++) \
					temp = (temp + a[i][k] * b[k][j]) % MOD; \
				c[i][j] = temp; \
			} \
		memcpy(a, c, sizeof c);\
	}
	void Power(ll n) {
		ll r[MAXN][MAXN] = {0};;
		for (long i = 1; i <= S; i++)
			r[i][i] = 1;
		while (n > 0) {
			if (n & 1) Mult(r, M);
			Mult(M, M);
			n >>= 1;
		}
		memcpy(M, r, sizeof M);
	}
	long Pow(long a, long n) {
		long r = 1;
		for (long i = 1; i <= n; i++)
			r *= a;
		return r;
	}

	void Work(void) {
		scanf("%ld %I64d", &k, &n);
		Dfs(1, 0);
		for (long i = 1; i <= S; i++) 
			fim[ Cal(state[i]) ] = i;

		for (long i = 1; i <= S; i++) {
			bool onlyone = true;
			for (long j = 2; j <= ::k; j++)
				if (state[i][j] == state[i][1]) {
					onlyone = false;
					break;
				}
			memset(temp, 0, sizeof temp);
			Find(i, 1, onlyone);
		}

		long Q[MAXN] = {0};
		for (long i = 1; i <= S; i++) {
			long number[K] = {0};
			for (long j = 1; j <= k; j++)
				number[ state[i][j] ]++;
			ll A = 1;
			for (long j = 1; j <= k; j++)
				A *= Pow(number[j], number[j] - 2);
			Q[i] = A % MOD;
		}
		Power(n - k);
		long A = 0;
		for (long i = 1; i <= S; i++)
			A = ( A + ll(M[1][i] * Q[i]) ) % MOD;
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

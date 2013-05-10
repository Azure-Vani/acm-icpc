//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 605;
	const int MAXP = 1000000;
	const int MAXM = 100000;

	Int64 a[MAXN]; int n;
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n;i ++) scanf(LL , a + i);
	}
	
	int prime[MAXM + 3], cnt = 0; int tag[MAXP + 3];

	void GetPrime(void) {
		memset(tag + 2, -1, sizeof(int) * (MAXP + 1));
		for (int i = 2; i <= MAXP; i++) {
			if (tag[i] == -1) prime[++cnt] = i, tag[i] = cnt;
			for (int j = 1; j <= cnt && i * prime[j] <= MAXP; j++) {
				tag[i * prime[j]] = 0;
				if (i % prime[j] == 0) break;
			}
		}
	}
	
	int fim[4] = {2, 7, 61, 1200007};

	inline Int64 Mult(Int64 a, Int64 n, Int64 p) {
		Int64 r = 0;
		while (n) {
			if (n&1) r = (r + a) % p;
			n >>= 1;
			a = (a << 1) % p;
		}
		return r;
	}

	inline Int64 Pow(Int64 a, Int64 n, Int64 p) {
		Int64 r = 1;
		while (n) {
			if (n&1) r = Mult(r, a, p);
			n >>= 1;
			a = Mult(a, a, p);
		}
		return r;
	}

	inline bool Check(Int64 n) {
		if (n == 1) return false;
		if (n == 2) return true;
		for (int i = 0; i < 4; i++) {
			int a = fim[i];
			Int64 d = n - 1;
			while (!(d&1)) d >>= 1;
			Int64 t = Pow(a, d, n);
			while (d != n - 1 && t != 1 && t != n - 1) {
				d <<= 1;
				t = Mult(t, t, n);
			}
			if (t != n - 1 && ((d & 1) != 1)) return false;
		}
		return true;
	}

	Int64 gcd(Int64 a, Int64 b) {return !b ? a : gcd(b, a % b);}
	
	int max = 0, num = 0;

	inline void Gao(Int64 p, int tmp = 1) {
		int c = 0;
		for (int i = 1; i <= n; i++) if (a[i] != 1) {
			while (a[i] % p == 0) 
				a[i] /= p, c++;
		}
		if (c > max) max = c, num = tmp;
		else if (c == max) num += tmp;
	}

	void Work(void) {
		for (int i = 1; i <= cnt; i++)
			Gao(prime[i]);
		for (int i = 2; i <= n; i++) if (a[i] != 1)
			for (int j = 1; j < i; j++) if (a[j] != 1) {
				Int64 t = gcd(a[i], a[j]);
				if (t != 1 && (t != a[i] || t != a[j]))
					Gao(t);
			}
		for (int i = 1; i <= n; i++) if (a[i] != 1) {
			Int64 t = round(sqrt(a[i]));
			if (t * t == a[i])
				Gao(t);
		}
		for (int i = 1; i <= n; i++) if (a[i] != 1) {
			if (Check(a[i]))
				Gao(a[i]);
			else
				Gao(a[i], 2);
		}
		printf("%d\n", max);
	}
	
	inline void Pow2(void) {
		int a[500] = {0}, l = 1; a[1] = 1;
		#define Len 10000
		for (int i = 1; i <= num; i++) {
			for (int j = 1; j <= l; j++)
				a[j] <<= 1;
			for (int j = 1; j <= l; j++) if (a[j] >= Len)
				a[j + 1] += a[j] / Len, a[j] %= Len;
			if (a[l + 1]) l++;
		}
		int t = 1; while (a[t] == 0) t++; a[t]--; for (int i = t - 1; i >= 1; i--) a[i] = Len - 1;
		printf("%d", a[l]);
		for (int i = l - 1; i >= 1; i--) {
			for (int j = 10; j < Len; j *= 10)
				if (a[i] < j) putchar('0');
			printf("%d", a[i]);
		}
		puts("");
	}

	void solve(void) {
		Input();
		GetPrime();
		Work();
		Pow2();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

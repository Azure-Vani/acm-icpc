#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

typedef long long Int64;

map<Int64, int> M;

inline Int64 gcd(Int64 a, Int64 b) {return !b?a:gcd(b, a % b);}
inline Int64 f(Int64 x, Int64 c, Int64 p, Int64 n = 0) {
	Int64 ret = 0; x %= p; if (!n) n = x; c %= p;
	while (n) {
		if (n & 1) {ret += x; if (ret >= p) ret -= p;}
		n >>= 1;
		x <<= 1; if (x >= p) x -= p;
	}
	ret += c; if (ret < 0) ret += p; if (ret >= p) ret -= p;
	return ret;
}

inline Int64 pow(Int64 a, Int64 n, Int64 p) {
	Int64 ret = 1;
	while (n) {
		if (n&1) ret = f(ret, 0, p, a);
		n >>= 1;
		a = f(a, 0, p);
	}
	return ret;
}

inline bool Mr(Int64 n, int a) {
	Int64 d = n - 1, x, y;
	while (!(d & 1)) d >>= 1;
	x = pow(a, d, n);
	while (d != n - 1) {
		y = f(x, 0, n);
		if (y == 1 && x != n - 1 && x != 1) return false;
		x = y; d<<=1;
	}
	return x == 1;
}

inline bool isPrime(Int64 n) {
	for (int i = 2; i <= 200 && i < n; i++) if (n % i == 0) return false;
	if (n <= 40000) return true;
	if (!Mr(n, 17)) return false;
	if (!Mr(n, 24251)) return false;
	if (!Mr(n, 61)) return false;
	if (!Mr(n, 7)) return false;
	if (!Mr(n, 2)) return false;
	if (!Mr(n, 3)) return false;
	return true;
}

inline Int64 rho(Int64 n, int c) {
	for (int i = 2; i <= 20; i++) if (n % i == 0) return i;
	for (Int64 x = 2, y = 2, p = 1; ;) {
		x = f(x,c,n), y = f(f(y,c,n),c,n);
		p = gcd(abs(x - y), n);
		if (p != 1) return p;
	}
}

inline void fac(Int64 n) {
	if (isPrime(n)) {M[n]++; return;}
	int c = -1; Int64 tmp = n;
	while ((tmp = rho(n, c--)) == n) ;
	fac(n / tmp); fac(tmp);
}

int main(void) {
	int kase; scanf("%d", &kase);
	while (kase--) {
		M.clear();
		Int64 n; scanf("%lld", &n);
		Int64 t = (Int64)(sqrt(n) + 0.5);
		if (t * t == n) {puts("1"); continue;}
		fac(n); bool check = true;
		foreach(it, M) if ((it->first & 3) == 3 && (it->second & 1) == 1) {check = false; break;}
		if (check) {puts("2"); continue;}
		for (Int64 i = 1; i <= n ;) {
			if (n % i == 0 && (n / i) % 8 == 7) {puts("4"); check = true; break;}
			i *= 4;
		}
		if (!check) puts("3");
	}
	return 0;
}


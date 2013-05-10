//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int64;
	int MOD = 999999599;
	int factory[4] = {2, 13, 5281, 7283};
	
	int Mod, n, m;

	inline int Pow(int a, int n, int p) {
		int r = 1;
		while (n) {if (n&1) r = (Int64) r * a % p; a = (Int64) a * a % p; n >>= 1;}
		return r;
	}

	inline int Ex_gcd(int a, int b, int& x, int& y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		int r = Ex_gcd(b, a % b, x, y);
		int t = x; x = y; y = t - a / b * y;
		return r;
	}

	inline int _E(int a, int b, int p) {
		int x, y;
		int t = Ex_gcd(a, p, x, y);
		x = (Int64) x * b / t % p;
		return x < 0 ? x + p : x;
	}

	inline int Fac(int a, int p) {
		if (a < p) {
			int ret = 1;
			for (int i = 1; i <= a; i++) ret = (Int64) ret * i % p;
			return ret;
		}
		int ret = Fac(a / p, p), t = a / p;
		ret = (Int64) ret * Pow(p - 1, t, p) % p;
		for (int i = p * t + 1; i <= a; i++) ret = (Int64) ret * i % p;
		return ret;
	}


	inline int Cal(int n, int p) {
		int ret = 0;
		while (n > 0) ret += n / p, n /= p;
		return ret;
	}
	
	int _n, num;
	
	inline int Gao(int d, int k) {
		int t1 = Cal(d, Mod), t2 = Cal(k, Mod) * d;
		if (t1 + t2 < num) return 0;
		int _d = Fac(d, Mod);
		int _k = Fac(k, Mod);
		_k = Pow(_k, d, Mod);
		int opp = (Int64) _d * _k % Mod;
		opp = _E(opp, 1, Mod);
		d = (Int64) _n * opp % Mod;
		return d;
	}

	inline int Work(void) {
		int res[4] = {0};
		for (int _ = 0; _ < 4; _++) {
			Mod = factory[_];
			_n = Fac(n, Mod); num = Cal(n, Mod);
			int &tmp = res[_];
			for (int i = 1; i * i <= n; i++) if (n % i == 0) {
				tmp = (Int64) ((Int64) tmp + (Int64) Gao(i, n / i)) % Mod;
				if (i * i != n)
					tmp = (Int64) ((Int64) tmp + (Int64) Gao(n / i, i)) % Mod;
			}
		}
		int M = MOD - 1, t = 0;
		for (int i = 0; i < 4; i++) {
			int w = M / factory[i];
			int opp = _E(w, 1, factory[i]);
			t = (Int64) ((Int64)t + (Int64) opp * w % M * res[i] % M) % M;
		}
		return Pow(m, t, MOD);
	}

	void solve(void) {
		scanf("%d%d", &n, &m);
		printf("%d\n", Work());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int T; scanf("%d", &T); while (T--)
	Solve::solve();
	return 0;
}

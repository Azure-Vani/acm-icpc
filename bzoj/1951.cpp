//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int65;
	const int Mod = 999911659;
	const int fim[4] = {2, 3, 4679, 35617};
	const int MAXN = 35619;

	int P, fac[MAXN];

	inline void GetPow(void) {
		fac[0] = 1;
		for (int i = 1; i < P; i++)
			fac[i] = (Int65) fac[i - 1] * i % P;
	}

	inline int Pow(int a, int n, int p) {
		int ret = 1;
		while (n) {if (n&1) ret = (Int65) ret * a % p; a = (Int65) a * a % p, n >>= 1;}
		return ret;
	}

	inline int C(int n, int m) {
		if (m > n) return 0;
		int opp = Pow(fac[m] * fac[n - m], P - 2, P);
		return (Int65) fac[n] * opp % P;
	}

	inline int GetC(int n, int m) {
		int ret = 1, a, b;
		while (n||m) {
			a = n % P;
			b = m % P;
			ret = (Int65) ret * C(a, b) % P;
			n /= P, m /= P;
		}
		return ret;
	}

	void Ex_gcd(int a, int b, int &x, int &y) {
		if (!b) {
			x = 1, y = 0;
			return;
		}
		Ex_gcd(b, a % b, x, y);
		int t = x; x = y, y = t - a / b * y;
	}

	int Work(int g, int n) {
		int res[4];
		for (int _ = 0; _ < 4; _++) {
			P = fim[_];
			GetPow();
			int tmp = 0;
			for (int j = 1; j * j <= n; j++) if (n % j == 0) {
				tmp = (Int65) ((Int65) tmp + (Int65) GetC(n, j)) % P;
				int oth = n / j;
				if (oth != j) 
					tmp = (Int65) ((Int65) tmp + (Int65) GetC(n, oth)) % P;
			}
			res[_] = tmp;
		}
		P = Mod - 1;
		int t = 0, x, y;
		for (int i = 0; i < 4; i++) {
			int mi = P / fim[i];
			Ex_gcd(mi, fim[i], x, y);
			x %= fim[i]; if (x < 0) x += fim[i];
			t = (Int65) ((Int65) t + (Int65) res[i] * x % P * mi % P) % P;
		}
		return Pow(g, t, Mod);
	}

	void solve(void) {
		int G, n;
		scanf("%d%d", &n, &G);
		if (G % Mod == 0) {
			puts("0");
			return;
		}
		printf("%d\n", Work(G, n));
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

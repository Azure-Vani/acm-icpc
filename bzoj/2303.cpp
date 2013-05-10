//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstdlib>
namespace Solve {
	typedef unsigned long long Int64;
	const int MAXN = 1000020;
	const int MAXM = 2000020;
	const int Mod = 1000000000;

	void Fail(void) {puts("0"); exit(0);}
	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct pair {
		int x, y, c;
	}a[MAXN];
	int n, m, k, p;

	void Input(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= k; i++)
			a[i].x = ScanInt(), a[i].y = ScanInt(), a[i].c = ScanInt(), p |= (a[i].x == 1 && a[i].y == 1 && a[i].c == 1);
	}

	int f[MAXM], d[MAXM];
	int Get(int x) {
		if (f[x] == x) return x;
		int ret = Get(f[x]);
		d[x] ^= d[f[x]];
		f[x] = ret;
		return ret;
	}

	int M = 0;

	inline Int64 Pow(int n) {
		Int64 r = 1, d = 2;
		while (n) {
			if (n & 1) r = r * d % Mod;
			d = d * d % Mod;
			n >>= 1;
		}
		return r;
	}

	void Work(void) {
		M = n + m - 1;
		for (int i = 1; i <= k; i++) a[i].c ^= p;
		for (int i = 1; i <= n + m + 1; i++) f[i] = i;
		f[n + m] = n + m + 1;
		d[n + m] = 1;
		for (int i = 1; i <= k; i++) {
			if (a[i].x == 1) {
				int t = Get(a[i].y);
				if (t == n + m + a[i].c) 
					if (d[a[i].y] ^ d[n + m + a[i].c] == a[i].c) continue; else Fail();
				f[t] = n + m + a[i].c;
				d[t] = d[n + m + a[i].c] ^ a[i].c ^ d[a[i].y];
				M--;
				continue;
			}
			if (a[i].y == 1) {
				int t = Get(a[i].x + m - 1);
				if (t == n + m + a[i].c)
					if (d[a[i].x + m - 1] ^ d[n + m + a[i].c] == a[i].c) continue; else Fail();
				f[t] = n + m + a[i].c;
				d[t] = d[a[i].x + m - 1] ^ a[i].c ^ d[n + m + a[i].c];
				M--;
				continue;
			}
			int Now = 1;
			if ((a[i].x & 1) || (a[i].y & 1)) Now = 0;
			int flag = (a[i].c != Now);
			int l1 = a[i].y, l2 = a[i].x + m - 1;
			int t1 = Get(l1), t2 = Get(l2);
			if (t1 == t2) {
				if ((d[l1] ^ d[l2]) != flag) 
					Fail();
				else continue;
			}
			if (t1 > m + n) std::swap(t1, t2);
			f[t1] = t2;
			d[t1] = d[l1] ^ d[l2] ^ flag;
			M--;
		}
		printf("%lld\n", Pow(M));
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

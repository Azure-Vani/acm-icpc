//#define Debug
#include <cctype>
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100020;
	const int Mod = 1 << 16;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, a[MAXN], m; int s[17][MAXN];

	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) {
			a[i] = ScanInt();
			for (int j = 1; j <= 16; j++)
				s[j][a[i] % (1 << j)]++;
		}
		for (int i = 1; i <= 16; i++)
			for (int j = 1; j <= Mod; j++)
				s[i][j] += s[i][j - 1];
	}

	int delta = 0;

	inline int Cal(int k, int l, int r) {
		int mod = 1 << k;
		if (l < 0) {
			while (l < 0)l += mod;
			return (s[k][Mod] - s[k][l - 1]) + (s[k][r]);
		}
		return s[k][r] - s[k][l - 1];
	}

	void Work(void) {
		char type;
		Int64 T = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%c", &type);
			if (type == 'A')
				delta += ScanInt(), delta &= Mod - 1;
			else {
				int k = ScanInt(); k++;
				if (k > 16){puts("0"); continue;}
				int Ans = Cal(k, (1 << k - 1) - delta % (1 << k), ((1 << k) - 1) - delta % (1 << k));
				T += Ans;
			}
		}
		printf("%lld\n", T);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

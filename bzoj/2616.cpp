//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <cassert>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

typedef long long Int64;

namespace Solve {
	const int MAXN = 521;
	const int MOD = 1000000007;
	const int MAXP = 50000;
	const int inf = ~0U>>1;
	
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline int Add(int a, int b) {
		a += b;
		if (a >= MOD) a -= MOD;
		return a;
	}

	int f[MAXP][MAXN], C[MAXN][MAXN], a[MAXN], n, k, sid = 0, P[MAXN];
	map<pair<pair<int,int>, int>, int> T;

	inline void Input(void) {
		n = ScanInt(), k = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
		C[0][0] = 1;
		for (int i = 1; i <= MAXN - 1; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= MAXN - 1; j++) 
				C[i][j] = Add(C[i - 1][j - 1], C[i - 1][j]);
		}
	}

	inline int Pow(int a, int n) {
		int ret = 1;
		while (n) {
			if (n&1) ret = (Int64) ret * a % MOD;
			n >>= 1;
			a = (Int64) a * a % MOD;
		}
		return ret;
	}

	inline void Cal(int N) {
		memset(P, 0, sizeof P); P[0] = 1;
		int pre = 1;
		for (int i = 1; i <= k && i <= N; i++) {
			pre = (Int64) pre * (N - i + 1ll) % MOD;
			P[i] = (Int64) pre % MOD;
		}
	}

	int* Dfs(int l, int r, int delta) {
		if (r < l) return f[0];
		int &pid = T[mp(mp(l, r), delta)]; if (!pid) pid = ++sid;
		int *ret = f[pid], Len = r - l + 1;
		bool same = true; int Min = inf, pos = l;
		for (int i = l; i <= r; i++) {
			if (i != l && a[i] != a[i - 1]) same = false;
			if (a[i] < Min) Min = a[i], pos = i;
		}
#ifdef FILEIO
		cout <<l<<' '<<r<<' '<<delta<<' '<<pid<<endl;
#endif
		if (Min == delta) {
			if (same) ret[0] = 1;
			else {
				int *L = Dfs(l, pos - 1, delta);
				int *R = Dfs(pos + 1, r, delta);
				for (int i = 0; i <= k && i <= Len; i++) {
					for (int j = 0; j <= i; j++) 
						ret[i] = Add(ret[i], (Int64) L[j] * R[i - j] % MOD);
				}
			}
		} else {
			int *U = Dfs(l, r, Min);
			Cal(Min - delta);
			for (int i = 0; i <= k && i <= Len; i++) {
				for (int j = 0; j <= i; j++) {
					int tmp = (Int64) U[j] * C[Len - j][i - j] % MOD;
					tmp = (Int64) tmp * P[i - j] % MOD;
					ret[i] = Add(ret[i], tmp);
				}
			}
		}
		return ret;
	}

	inline void solve(void) {
		Input();
		f[0][0] = 1;
		int *Ans = Dfs(1, n, 0);
#ifdef FILEIO
		for (int i = 0; i <= sid; i++) {
			cout <<i<<": ";
			for (int j = 0; j <= k; j++) 
				cout <<f[i][j]<<' ';
			cout <<endl;
		}
#endif
		printf("%d\n", *(Ans + k));
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
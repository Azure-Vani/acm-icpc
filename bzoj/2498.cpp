#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
#include <complex>
#include <cctype>
#define REP(i,l,r) for(register int i = l; i <= r; i++)
#define pi 3.14159265358979324

using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 140000;

	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar())) ;
		r = c - 48;
		while ( isdigit(c = getchar())) r = r * 10 + c - 48;
		return r;
	}

	int n, a[MAXN], p, pow[9];Int64 wtmp[MAXN];

	inline void Input(void) {
		n = ScanInt(); p = ScanInt(); REP(i,1,n) a[i] = ScanInt();
		sort(a + 1, a + n + 1);
	}

	typedef complex<double> ii;
	const int M2 = 1 << 17;
	ii DATA[MAXN << 1], *e = DATA + MAXN, g[2][MAXN];

	inline void Init(int N) {
		e[0] = ii(1, 0); 
		for(register int i = 1; i < N; i *= 2) e[i] = ii(cos(pi * i * 2 / N), sin(pi * i * 2 / N));
		for(register int i = 1; i < N; i++) if ((i & -i) != i) e[i] = e[i & - i] * e[i - (i & - i)];
		REP(i, 1, N - 1) e[-i] = e[N - i];
	}


	inline void Dft(ii *a, int Len, int f) {
		register int d = M2 / Len * f; ii t;
		for (int n = Len, m; m = n >> 1, m >= 1; n = m, d <<= 1)
			for (int i = 0, k = 0; i < m; i++, k += d)
				for (int j = i; j < Len; j += n)
					t = a[j] - a[j + m], a[j] += a[j + m], a[j + m] = t * e[k];
		for (int i = 0, j = 1; j < Len - 1; j++) {
			for (int k = Len >> 1; k > (i ^= k); k >>= 1); if (j < i) swap(a[j], a[i]);
		}
	}

	vector<vector<int> > T, M[6];

	inline void Dfs(vector<int> now, int res, vector<vector<int> > &T) {
		if (res == 0) {
			sort(now.begin(), now.end());
			T.push_back(now);
			return;
		}
		REP(i, 1, res) {
			now.push_back(i);
			Dfs(now, res - i, T);
			now.pop_back();
		}
	}

	inline bool cmpT(vector<int> a, vector<int> b) {
		return a.size() < b.size();
	}

	struct Node {
		long long a[MAXN]; int n;
		inline void operator -=(const Node &oth) {
			if (oth.n > n) n = oth.n;
			REP(i, 0, n) a[i] -= (Int64) oth.a[i];
		}
	}f[10];

	inline void Make(Node &res, const vector<int>& now) {
		int L = now.size(), N = 0, vis = false; REP(i, 0, L - 1) N += now[i] * a[n]; while (N & (N - 1)) ++N;
		REP(i, 0, L - 1) {
			REP(j, 1, n) g[1][a[j] * now[i]] = ii(1, 0);
			Dft(g[1], N, 1);
			REP(j, 0, N - 1) {if (vis) g[0][j] *= g[1][j]; else g[0][j] = g[1][j]; g[1][j] = ii(0, 0);}
			vis = true;
		}
		Dft(g[0], N, -1); res.n = N;
		REP(i, 0, N - 1) res.a[i] = (long long)(g[0][i].real() / N + 0.5);
	}

	vector<int> List[8][8];

	inline void D(vector<int> S, const vector<int>& now, vector<int> &ret) {
		if (now.size() == 0) {
			sort(S.begin(), S.end());
			int del = find(T.begin(), T.end(), S) - T.begin();
			ret.push_back(del);
			return;
		}
		int L = now.size();
		for (int i = 0; i < (1 << (L - 1)); i++) {
			vector<int> next; int t = now[0];
			for (int j = 1; j < L; j++) if (i & (1 << (j - 1))) t += now[j]; else next.push_back(now[j]);
			S.push_back(t);
			D(S, next, ret);
			S.pop_back();
		}
	}

	inline void solve(void) {
		int Tcase = ScanInt(); 
		Init(M2);
		pow[0] = 1; REP(i, 1, 10) pow[i] = pow[i - 1] * i;
		REP(i, 1, 5) 
			Dfs(vector<int>(), i, M[i]), sort(M[i].begin(), M[i].end()), M[i].erase(unique(M[i].begin(), M[i].end()), M[i].end()), sort(M[i].begin(), M[i].end(), cmpT);
		REP(i, 1, 5) {
			T = M[i];
			REP(j, 0, (int)T.size() - 1) D(vector<int>(), T[j], List[i][j]);
		}
		REP(kase, 1, Tcase) {
			memset(f, 0, sizeof f);
			T.clear();
			printf("Case #%d:\n",kase);
			Input(); T = M[p];
			for (int i = 0; i < (int)T.size(); i++) {
				Make(f[i], T[i]);
				REP(j, 1, (int)List[p][i].size() - 1) 
					f[i] -= f[List[p][i][j]];
			}
			int pos = T.size() - 1;
			for (int i = 1; i <= f[pos].n; i++) {
				long double ret = (long double)f[pos].a[i] / pow[p];
				if (ret > 0.5) printf("%d: %.0LF\n", i, ret);
			}
			puts("");
		}
	}
}

int main(void) {
	Solve::solve();
	return 0;
}

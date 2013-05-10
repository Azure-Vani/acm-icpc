#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#define REP(i,l,r) for(register int i = l; i <= r; i++)

using namespace std;

const int Mod = 1000000007;
const int MAXN = 107;

inline void Add(int &a, long long b) {
	a += b; if (a >= Mod) a -= Mod;
}

struct Matrix {
	int a[MAXN][MAXN], n, m;
	Matrix(int _n = 0, int _m = 0):n(_n), m(_m){memset(a, 0, sizeof a);}
	inline void operator =(const Matrix& oth) {
		n = oth.n, m = oth.m;
		REP(i, 1, n) REP(j, 1, m) a[i][j] = oth.a[i][j];
	}
	inline Matrix operator *(const Matrix& oth) {
		Matrix ret(n, oth.m);
		REP(i, 1, n) REP(j, 1, oth.m) {
			int tmp = 0;
			REP(k, 1, m) Add(tmp, (long long) a[i][k] * oth.a[k][j] % Mod);
			ret.a[i][j] = tmp;
		}
		return ret;
	}
}init, f[32], Q[MAXN];

inline void Make(Matrix &a, int v[], int L, int t) {
	a.n = a.m = L;
	REP(i, 2, L) a.a[i][i - 1] = 1;
	REP(i, L - t + 1, L) a.a[i][L] = v[i - (L - t + 1) + 1];
}

struct Node {
	int pos, len, s[MAXN];
	inline void operator =(const Node& oth) {
		pos = oth.pos, len = oth.len;
		memcpy(s, oth.s, sizeof s);
	}
}J[MAXN];
inline bool cmp(const Node& a, const Node& b) {
	return a.pos < b.pos;
}

int n, m, q, t, c[MAXN], L, I[MAXN];

int main(void) {
	int kase = 0;
	while (scanf("%d%d%d", &n, &m, &q) == 3) {
		memset(f, 0, sizeof f); memset(init.a, 0, sizeof init.a); memset(Q, 0, sizeof Q); memset(J, 0, sizeof J);
		memset(c, 0, sizeof c); memset(I, 0, sizeof I);
		REP(i, 1, m) scanf("%d", I + i);
		scanf("%d", &t); REP(i, 1, t) scanf("%d", c + t - i + 1); L = t;
		int Y = 0;
		REP(i, 1, q) {
			++Y;
			scanf("%d%d", &J[Y].pos, &J[Y].len);
			REP(j, 1, J[Y].len) scanf("%d", &J[Y].s[J[Y].len - j + 1]);
			if (J[Y].pos <= m || J[Y].pos > n) {Y--; continue;}
			L = max(L, J[Y].len);
		}
		q = Y;
		J[++q].pos = n + 1, J[q].len = 1, J[q].s[1] = 1;
		sort(J + 1, J + q + 1, cmp);
		init.n = 1, init.m = L;
		REP(i, m - L + 1, m) if (i < 1) init.a[1][i - (m - L + 1) + 1] = 0; else init.a[1][i - (m - L + 1) + 1] = I[i];
		Make(f[0], c, L, t);
		REP(i, 1, q) Make(Q[i], J[i].s, L, J[i].len);
		REP(i, 1, 31) f[i] = f[i - 1] * f[i - 1]; J[0].pos = m;
		REP(i, 1, q) {
			int tmp = J[i].pos - J[i - 1].pos - 1, v = 0;
			while (tmp) {
				if (tmp & 1) init = init * f[v];
				v++, tmp >>= 1;
			}
			init = init * Q[i];
		}
		printf("Case %d: %d\n", ++kase, init.a[1][L]);
	}
	return 0;
}


#include <cstdio>
#include <cstring>
#include <complex>
#include <algorithm>
#define pi 3.14159265358979323846
#define REP(i,l,r) for(register int i = l; i <= r; i++)

#pragma GCC optimize("O2")

using namespace std;

const int MAXN = 1 << 17;

//typedef complex<double> ii;

struct ii {
	double x, y;
	ii(){}
	inline ii(double x, double y):x(x), y(y){}
	inline void operator +=(const ii& oth) {
		x += oth.x, y += oth.y;
	}
	inline void Minus(const ii& a, const ii& b) {
		x = a.x - b.x; y = a.y - b.y;
	}
	inline void Mul(ii a, const ii& b) {
		x = a.x * b.x - a.y * b.y; y = a.x * b.y + a.y * b.x;
	}
};

ii DATA[(MAXN << 1) + 5], *e = DATA + MAXN, a[MAXN + 5], b[MAXN + 4];

int kase, T, n, X[MAXN], Y[MAXN]; long long Ans[MAXN + 5];

inline void Init(void) {
	e[0] = ii(1, 0);
	for (int i = 1; i < MAXN; i <<= 1) e[i] = ii(cos(2 * pi * i / MAXN), sin(2 * pi * i / MAXN));
	REP(i, 1, MAXN - 1) if (i & (i - 1)) e[i].Mul(e[i & -i], e[i - (i & -i)]);
	REP(i, 1, MAXN - 1) e[-i] = e[MAXN - i];
}

char c1[300001], c2[300001];
int Pow[] = {1, 10, 100, 1000, 10000};

inline int Compress(char c[], ii a[], int n, int b[]) {
	register int t = 0, L = 0;
	for (register int i = 0, x; i < n; i++) {
		t += Pow[x = i % 5] * (c[n - 1 - i] - 48);
		if (x == 4) b[L++] = t, t = 0;
	}
	b[L++] = t;
	return L;
}

inline void Dft(ii a[], int L, int f) {
	register int d = MAXN / L * f; ii t;
	for (register int n = L, m; m = n >> 1, m >= 1; n = m, d <<= 1)
		for (register int i = 0, x = 0; i < m; i++, x += d)
			for (register int j = i; j < L; j += n)
				t.Minus(a[j], a[j + m]), a[j] += a[j + m], a[j + m].Mul(t, e[x]);
	for (register int i = 0, j = 1; j < L - 1; j++) {
		for (register int k = L >> 1; k > (i ^= k); k >>= 1); if (j < i) swap(a[j], a[i]);
	}
}

char c3[10], Buffer[600000 * 101 + 101], *pos = Buffer, iBuffer[600000 * 101 + 404], *data = iBuffer;
inline void Out(int t) {
	if (t == 0) {*pos++ = 48; return; }
	register int L = 0;
	while (t) c3[L++] = t % 10 + 48, t /= 10;
	for (register int i = L - 1; i >= 0; i--) *pos++ = c3[i];
}

inline int Getchar(void) {return *data++;}

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = Getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = Getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

inline int get(char ret[]) {
	register int c, L = 0; while (!isdigit(c = Getchar()));
	ret[L++] = c;
	while (isdigit(c = Getchar())) 
		ret[L++] = c;
	ret[L] = 0;
	return L;
}

int main(void) {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	fread(iBuffer, 1, 600000 * 101 + 403, stdin);
	for (Init(), kase = 1, T = ScanInt(); kase <= T; kase++) {
		n = 0; 
		int n1 = get(c1); 
		int n2 = get(c2);
		n1 = Compress(c1, a, n1, X); n2 = Compress(c2, b, n2, Y); n = max(n1, n2);
		while ((n & -n) != n) n -= n & -n; n <<= 2;
		REP(i, 0, n - 1) a[i].x = a[i].y = b[i].x = b[i].y = 0;
		REP(i, 0, n1 - 1) a[i].x = X[i]; REP(i, 0, n2 - 1) b[i].x = Y[i];
		Dft(a, n, 1); 
		Dft(b, n, 1);
		REP(i, 0, n - 1) a[i].Mul(a[i], b[i]);
		Dft(a, n, -1);
		int L = 0;
		REP(i, 0, n - 1) Ans[i] = (long long)(a[i].x / n + 0.5);
		REP(i, 0, n - 1) Ans[i + 1] += Ans[i] / 100000, Ans[i] %= 100000, L = (Ans[i] ? i : L);
		Out(Ans[L]);
		for (int i = L - 1; i >= 0; i--) {
			register long long t = Ans[i];
			if (t < 10000) *pos++ = 48;
			if (t < 1000) *pos++ = 48;
			if (t < 100) *pos++ = 48;
			if (t < 10) *pos++ = 48;
			Out(t);
		}
		*pos++ = '\n';
	}
	fwrite(Buffer, 1, pos - Buffer, stdout);
	return 0;
}


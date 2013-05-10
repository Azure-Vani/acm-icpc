//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
namespace Solve {
	typedef long long int64;
	const int MAXN = 10005;
	const int64 M10 = 10000000000ll;
	int Length = 10;
	#ifdef Debug
		#define LL "%I64d"
	#else
		#define LL "%lld"
	#endif
	
	int64 x[MAXN], y[MAXN];
	
	void Trans(int64 ret[], int M[]) {
		int n = M[0];
		std::reverse(M + 1, M + 1 + n);
		
		int64 t = 0, l = 1;
		for (int i = 1; i <= n; i++) {
			t += M[i] * l, l *= 10;
			if (i % Length == 0) ret[ ++ret[0] ] = t, t = 0, l = 1;
		}
		if (t) ret[ ++ret[0] ] = t;
	}
	
	void Input(void) {
		int c, seg[MAXN] = {0};
		while (c = getchar(), isdigit(c)) seg[++seg[0]] = c - '0';
		Trans(x, seg);
		while (c = getchar(), !isdigit(c)) {}
		seg[0] = 0;
		seg[ ++seg[0] ] = c - '0';
		while (c = getchar(), isdigit(c)) seg[++seg[0]] = c - '0';
		Trans(y, seg);
	}
	
	void Print(int64* a) {
		printf(LL, a[a[0]]);
		for (int i = a[0] - 1; i >= 1; i--) {
			for (int64 j = 10; j < M10; j *= 10)
				if (a[i] < j) putchar('0');
			printf(LL, a[i]);
		}
		puts("");
	}
	
	bool Cmp(int64* a, int64* b) {
		if (a[0] != b[0]) return a[0] < b[0];
		int l = a[0];
		while (a[l] == b[l] && l > 1) l--;
		return a[l] < b[l];
	}
	
	int64 delta[MAXN] = {1, 1}, *a = x, *b = y;
	
	void Decreas(int64* &a, int64* &b) {
		bool less = Cmp(b, a);
		if (!less) std::swap(a, b);
		for (int i = 1; i <= a[0]; i++) a[i] -= b[i];
		for (int i = 1; i <= a[0]; i++)
			if (a[i] < 0) {
				a[i + 1]--;
				a[i] += M10;
			}
		int64& l = a[0];
		while (!a[l] && l > 1) l--;
	}
	
	void Mult(int64*  a, int64* b) {
		int64 c[MAXN] = {0};
		c[0] = a[0] + b[0] - 1;
		for (int i = 1; i <= a[0]; i++)
			for (int j = 1; j <= b[0]; j++)
				c[i + j - 1] += a[i] * b[j];
		for (int i = 1; i <= c[0]; i++) {
			c[i + 1] += c[i] / M10;
			c[i] %= M10;
		}
		if (c[c[0] + 1]) c[0]++;
		memcpy(a, c, sizeof(int64) * (c[0] + 1));
	}
	
	void Div(int64* a) {
		int l = a[0];
		if (a[a[0]] < 2) l--;
		int last = 0;
		for (int64 i = a[0]; i >= 1; i--)
			a[i] = a[i] + M10 * last, last = a[i] & 1, a[i] >>= 1;
		a[0] = l;
	}
	
	#define Zero(a) (a[0] == 1 && a[1] == 0)
	void Work(void) {
		int64 P[5] = {1, 2};
		while (!Zero(a) && !Zero(b)) {
			bool Odda = a[1] & 1, Oddb = b[1] & 1;
			if (Odda && Oddb) {
				Decreas(a, b);
			}else
			if (!Odda && !Oddb) {
				Div(a);
				Div(b);
				Mult(delta, P);
			}else
			if (Odda && !Oddb) {
				Div(b);
			}else
			if (!Odda && Oddb) {
				Div(a);
			}
		}
		if (Zero(a)) {
			Mult(b, delta);
			Print(b);
		}
		else {
			Mult(a, delta);
			Print(a);
		}
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

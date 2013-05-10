#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cassert>

using namespace std;

namespace Solve {
	const int MAXN = 12010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int L = 0;

	struct Node {
		Node *ch[2]; int size;
		Node(){size = 0; ch[0] = ch[1] = NULL;}
	}*root[MAXN], null, POOL[MAXN * 33], *pid = POOL;

	inline Node* Insert(Node *now, int u, int j) {
		Node *ret = pid++; if (now) *ret = *now; ret->size++;
		if (j == 0) return ret;
		int d = !!(u & j);
		ret->ch[d] = Insert(ret->ch[d], u, j >> 1);
		return ret;
	}

	int a[MAXN], n, m, belong[MAXN];

	inline void Input(void) {
		n = ScanInt(), m = ScanInt(); n++;
		int tmp = 0;
		for (int i = 2; i <= n; i++) a[i] = ScanInt() ^ a[i - 1], tmp |= a[i];
		while (tmp) tmp >>= 1, L++; if (!L) L = 1;
		root[0] = &null;
	}

	inline int sgn(const Node *x) {
		return x == NULL ? 0 : x->size;
	}

	int q, P[125][MAXN];

	inline int Cal(int l, int r, int u) {
		Node *X = root[l - 1], *Y = root[r]; int ret = 0;
		for (int i = 0, j = 1 << (L - 1); i < L; i++, j >>= 1) {
			bool d = !(u & j);
			if (sgn(Y->ch[d]) - sgn(X->ch[d]) > 0) {
				ret |= j;
			} else d ^= 1;
			if (Y->ch[d]) Y = Y->ch[d]; else Y = &null;
			if (X->ch[d]) X = X->ch[d]; else X = &null;
		}
		return ret;
	}

	inline void Init(void) {
		for (int i = 1; i <= n; i++) {
			root[i] = Insert(root[i - 1], a[i], 1 << (L - 1));
		}
		while (q * q < n) q++;
		for (int i = 1; i <= n; i++) {
			int t = (i - 1) / q + 1; belong[i] = t;
			if ((i - 1) % q == 0) {
				for (int j = i; j <= n; j++) {
					int tmp = Cal(i, j, a[j]);
					P[t][j] = max(P[t][j - 1], tmp);
				}
			}
		}
	}

	inline void Work(void) {
		int Ans = 0;
		for (int i = 1; i <= m; i++) {
			int l = (ScanInt() + (long long) Ans) % (n - 1) + 1, r = (ScanInt() + (long long) Ans) % (n - 1) + 1;
			if (l > r) swap(l, r); r++;
			Ans = P[belong[l] + 1][r];
			for (int j = l; belong[j] == belong[l] && j <= r; j++) {
				int tmp = Cal(l, r, a[j]);
				Ans = max(Ans, tmp);
			}
			printf("%d\n", Ans);
		}
	}

	inline void solve(void) {
		Input();
		Init();
		Work();
	}
}

int main(void) {
	Solve::solve();
	return 0;
}


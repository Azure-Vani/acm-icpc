#include <cstdio>
#include <cctype>
#include <cstring>

#define ScanChar(p) while(islower(c = getchar())) *p++ = c, n++;

const int MAXN = 500010;

char ch[MAXN], *p = ch + 1;
int n, c, Len, trans[MAXN][27], l[MAXN], S[MAXN];

inline int Cal(int p1, int p2) {
	if (!p2) return 0;
	else {
		if (--p2 == S[p1]) return l[p1] + 1;
		else while (S[p2] != S[p1]) p2 = S[p2];
		return (l[p2]<l[p1]?l[p2]:l[p1])+ 1;
	}
}

int main(void) {
	freopen("in", "r", stdin);
	ScanChar(p);Len = ++n, *p++ = 'a' - 1;ScanChar(p);
	S[0] = -1;
	for (int i = 1; i <= n; i++) {
		register int k = S[i - 1], tmp = ch[i] - 'a' + 1, p = i - 1;
		trans[i - 1][tmp] = i;
		while (k != -1 && !trans[k][tmp]) {
			trans[k][tmp] = i;
			k = S[p = k];
		}
		if (k == -1) S[i] = 0; else S[i] = trans[k][tmp];
		l[i] = Cal(p, S[i]);
	}
	register int Ans = 0;
	for (int i = Len + 1; i <= n; i++) if (S[i] <= Len && l[i] > Ans) Ans = l[i];
	printf("%d\n", Ans);
}

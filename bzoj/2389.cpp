#include <cstdio>
#include <algorithm>
#include <cctype>
inline int ScanInt(void) {
	int r = 0, c;
	while (c = getchar(), !isdigit(c)) {}
	r = c - '0';
	while (isdigit(c = getchar())) r = r * 10 + c - '0';
	return r;
}
int n, m, f[500010], Mod = 1000000009;
inline int Find(int x) {return (x == f[x])?x:(f[x] = Find(f[x]));}
int main(int argc, char** argv) {
	n = ScanInt(), m = ScanInt();
	for (int i = 1; i <= n; i++) f[i] = i;
	int Ans = 0, delta = 1;
	for (int i = 1; i <= m; i++) {
		int x = ScanInt(), y = ScanInt();
		int t1 = Find(x), t2 = Find(y);
		if (t1 == t2) {
			Ans = (long long) (delta + Ans) % Mod;
			delta = (long long) delta * 2ll % Mod;
		}else f[t1] = t2;
		printf("%d\n", Ans);
	}
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <cstring>
const int MAXN = 2000010;
char a[MAXN], b[MAXN]; int n;
int main(int argc, char** argv) {
	gets(a + 1); scanf("\n"); gets(b + 1);
	n = strlen(a + 1);
	for (int i = 1; i <= n; i++) a[i + n] = a[i], b[i + n] = b[i];;
	bool ok = false; int p, q;
	for (p = 1, q = 1; p <= n * 2 && q <= n * 2; ) {
		int k = 0;
		while (k < n && a[p + k] == b[q + k]) k++;
		if (k >= n) {ok = true; break;}
		if (a[p + k] > b[q + k]) p += k + 1; else q += k + 1;
	}
	puts(ok?"Yes":"No");
	if (ok) {
		p = 1, q = 2;
		while (p <= n && q <= n + 1) {
			int k = 0;
			while (k < n && a[p + k] == a[q + k]) k
				++;
			if (k >= n) break;
			if (a[p + k] > a[q + k]) {p += k + 1;p += (p==q);}
			else {q += k + 1;q += (p==q);}
		}
		for (int i = std::min(p, q), k = 0; k < n; k++) putchar(a[i+k]);
		puts("");
	}
	return 0;
}

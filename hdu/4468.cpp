#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 1000010;

char ch[MAXN], s[MAXN]; int p[MAXN];

int main(void) {
	int kase = 0, n;
	while (scanf("%s", ch + 1) == 1) {
		n = strlen(ch + 1); memset(s, 0, sizeof s);
		int m = 1, last = 0; s[1] = ch[1];
		for (int i = 1, j = 0; i <= n; i++) {
			while (j && ch[i] != s[j + 1]) j = p[j];
			if (ch[i] == s[j + 1]) j++;
			if (!j) {
				for (int k = last + 1, t = p[m]; k <= i; k++) {
					s[++m] = ch[k];
					while (t && s[m] != s[t]) t = p[t];
					if (s[t + 1] == s[m]) t++;
					p[m] = t;
				}
				j = m;
			}
			if (j == m) last = i;
		}
		printf("Case %d: %d\n", ++kase, m + n - last);
	}
	return 0;
}


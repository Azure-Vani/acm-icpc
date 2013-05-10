#include <cstdio>
#include <algorithm>
#include <cmath>
#define Is(x) (((x)  - 1)/ MAXQ + 1)
#define Make(i) {\
	register int t = i + a[i];\
	if (belong[t] == belong[i]) step[i] = step[t] + 1, next[i] = next[t];\
	else step[i] = 1, next[i] = t;\
}
const int MAXN = 400010;
int MAXQ;
int a[MAXN], n, m, next[MAXN], step[MAXN], belong[MAXN];
int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d", &n);
	MAXQ = sqrt(n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), belong[i] = Is(i);
	for (int i = n; i >= 1; i--) Make(i);
	scanf("%d", &m);
	while (m--) {
		int type; scanf("%d\n", &type);
		if (type == 1) {
			int x, Ans = 0; scanf("%d", &x);x++;
			while (x <= n) Ans += step[x], x = next[x];
			printf("%d\n", Ans);
		}else {
			int x, y; scanf("%d %d\n", &x, &y); a[++x] = y;
			for (int i = x; i >= 1 && belong[i] == belong[x]; i--) 
				Make(i);
		}
	}
	return 0;
}

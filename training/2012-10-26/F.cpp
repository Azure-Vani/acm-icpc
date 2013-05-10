#include <cstdio>
int T, s = 0, a[1000];
int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		s = 1;
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		int flag = 0, tmp;
		for (;;s++) {
			if (n == 1) {
				tmp = (a[1] != 0);
				flag = a[1];
				break;
			}
			int t = 0;
			for (int j = 1; j <= n - s; j++) a[j] = a[j + 1] - a[j], t += (a[j] != 0);
			if (t == 0 || t == 1) {tmp = t; flag = a[1]; break;}
		}
		if (tmp == 0) {
			while (s--) putchar('z'); puts("ap!");
		} else {
			if (flag > 0) puts("*fizzle*"); else puts("*bunny*");
		}
	}
	return 0;
}


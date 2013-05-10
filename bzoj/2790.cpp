#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1000010;
int a[MAXN], n, list[MAXN], cnt = 0, tag[MAXN], num[MAXN], M = 0;
int l1[MAXN], l2[MAXN], Ans[MAXN], p1[MAXN], p2[MAXN], best[MAXN];

void GenPrimer(void) {
	for (int i = 2; i <= M; i++) {
		if (!tag[i]) list[++cnt] = i, num[i] = 1;
		for (int j = 1; j <= cnt && (long long) i * list[j] <= M; j++) {
			tag[i * list[j]] = true;
			num[i * list[j]] = num[i] + 1;
			if (i % list[j] == 0) break;
		}
	}
}

int main(void) {
//	freopen("in", "r", stdin);
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), M = max(M, a[i]);
	GenPrimer();
	memset(l1, 60, sizeof l1); memset(l2, 60, sizeof l2); memset(best, 60, sizeof best);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= a[i]; j++) if (a[i] % j == 0) {
			int l = 2; if (j * j == a[i]) l--;
			for (int k = 0; k < l; k++) {
				int t = a[i] / j, v = num[j];
				if (v < l1[t]) l2[t] = l1[t], p2[t] = p1[t], l1[t] = v, p1[t] = i; else
				if (v < l2[t]) l2[t] = v, p2[t] = i;
				j = a[i]  / j;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j * j <= a[i]; j++) if (a[i] % j == 0) {
			for (int k = 0; k < 2; k++) {
				int t = a[i] / j, v = num[j], oth = l1[t], w = p1[t];
				if (p1[t] == i) oth = l2[t], w = p2[t];
				if (v + oth < best[i] || (v + oth == best[i] && w < Ans[i])) best[i] = v + oth, Ans[i] = w;
				j = a[i] / j;
			}
		}
	}
	for (int i = 1; i <= n; i++) printf("%d\n", Ans[i]);
	return 0;
}

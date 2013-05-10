#include <cstdio>
int level[5000100], d[5000010], head = 1, tail = 1, sum = 1, n, k, u;
inline int Trans(int t) {return t >= 5000000 ? 1 : t;}
int main(void) {
	scanf("%d%d", &n, &k); level[n] = 1; d[1] = n; if (n > k) u = n; else u = k;
	while (sum) {
		int now = d[head++]; if (now >= u * 2) continue; Trans(head); sum--;
		if (!level[now + 1]) level[d[Trans(++tail)] = now + 1] = level[now] + 1, sum++;
		if (now > 0 && !level[now - 1]) level[d[Trans(++tail)] = now - 1] = level[now] + 1, sum++;
		if (!level[now * 2]) level[d[Trans(++tail)] = now * 2] = level[now] + 1, sum++;
		if (level[k]) break;
	}
	printf("%d\n", level[k] - 1);
}

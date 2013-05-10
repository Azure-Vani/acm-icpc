#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAXN = 202;
const int inf = 100000000;

int h[MAXN], a[MAXN], n, sky, star[MAXN], N;
struct Interval {
	double l, r;
	inline bool operator <(const Interval& oth) const {
		return l < oth.l;
	}
}c[MAXN], b[MAXN];

inline double Get(int i, int j) {
	if (a[i] == a[j]) return a[i];
	double k = (double)(h[i] - h[j]) / (double) (a[i] - a[j]);
	return (sky - h[i] + k * a[i]) / k;
}

bool vaild[MAXN];

int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d%d", &sky, &N);
	for (int i = 1; i <= N; i++) scanf("%d", star + i); star[0] = -inf * 2;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d",  h + i, a + i);
	for (int i = 1; i <= n; i++) {
		c[i].r = inf; c[i].l = -inf;
		for (int j = 1; j < i; j++) if (h[j] > h[i]) c[i].l = max(c[i].l, Get(i, j));
		for (int j = i + 1; j <= n; j++) if (h[j] > h[i]) 
			c[i].r = min(c[i].r, Get(i, j));
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) if (i != j && c[j].l <= c[i].l && c[i].r <= c[j].r) vaild[j] = true;
	int tmp = 0;
	for (int i = 1; i <= n; i++) if (!vaild[i]) b[++tmp] = c[i]; memcpy(c + 1, b + 1, sizeof(c[0]) * tmp); n = tmp;
	sort(c + 1, c + n + 1);
	int pos = 1, Ans = 0, s = 0;
	for (int i = 1; i <= n; i = pos) {
		while (s + 1 <= N && star[s + 1] - c[i].l < -0.001) s++;
		while (s + 1 <= N && star[s + 1] - c[i].r < -0.001) s++;
		if (star[s] < c[i].l) {
			puts("Shit..I can't see rins...");
			return 0;
		}
		while (pos <= n && c[pos].l - star[s] < -0.001) pos++;
		Ans++;
	}
	printf("%d\n", Ans);
	return 0;
}

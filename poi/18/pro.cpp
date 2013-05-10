#include <cstdio>
#include <algorithm>
#define rep(i,r) for(int i = 1; i <= r; i++)

const int MAXN = 50000;

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

int acc[MAXN], vis[MAXN], cur = 1, Link[MAXN], n, m, r, t, k;
int list[MAXN];

int Dfs(int u) {
	for (Edge *p = a[u]; p; p = p->next) if (vis[p->y] != cur) {
		vis[p->y] = cur;
		if (!Link[p->y] || Dfs(Link[p->y])) {
			Link[p->y] = u;
			return 1;
		}
	}
	return 0;
}

inline bool cmp(int x, int y) {return acc[x] < acc[y];}

long long sum[MAXN];

int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d%d%d%d%d", &n, &m, &r, &t, &k);int limit = t / r;
	rep(i,k) {
		int x, y; scanf("%d%d", &x, &y); y += n;
		a[x] = new Edge(y, a[x]);
	} acc[0] = 505;
	while (true) {
		rep(i, n) list[i] = i;
		std::sort(list + 1, list + n + 1, cmp);
		bool ok = false;
		rep(i, n) if (acc[list[i]] < limit && Dfs(list[i])) {
			cur++, ok = true; acc[list[i]] += 1;
		}
		if (!ok) break;
	}
	int Ans = 0; long long delay = 0;
	rep(i,n) Ans += acc[i], delay += (long long)acc[i] * (acc[i] + 1) / 2;
	printf("%d %lld\n", Ans, delay * r);
	for (int i = n + 1; i <= n + m; i++) if (Link[i]) {
		printf("%d %d %lld\n", Link[i], i - n, sum[Link[i]]);
		sum[Link[i]] += r;
	}
	return 0;
}

#include <cstdio>
#include <cstring>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,n) for(int i = 1; i <= n; i++)

using namespace std;

const int MAXN = 1000010;

int sum[MAXN], n, d[MAXN], father[MAXN], deep[MAXN], height[MAXN], far[MAXN], f[MAXN];

long long S[MAXN], Ans[MAXN];

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d", &n);
	rep(i,n - 1) { int x, y; scanf("%d%d", &x, &y); a[x] = new Edge(y, a[x]), a[y] = new Edge(x, a[y]); }
	int head = 1, tail = 1; d[1] = 1;
	while (head <= tail) {
		int now = d[head++];
		S[1] = S[1] + deep[now];
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			deep[p->y] = deep[now] + 1;
			father[p->y] = now;
			d[++tail] = p->y;
		}
	}
	memset(height, -1, sizeof height);
	for (int i = n; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]], height[father[d[i]]] = max(height[father[d[i]]], ++height[d[i]]);
	for (int i = 1; i <= n; i++) {
		int now = d[i], m1 = -1, w1 = 0, m2 = -1;
		for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
			if (height[p->y] > m1) {
				m2 = m1;
				m1 = height[p->y], w1 = p->y;
			} else if (height[p->y] > m2) {
				m2 = height[p->y];
			}
		}
		f[now] = max(height[now], far[now]);
		for (Edge *p = a[now]; p; p = p->next) if (father[now] != p->y) {if (p->y != w1) {
			far[p->y] = max(m1 + 1, far[now]) + 1;
		} else far[p->y] = max(m2 + 1, far[now]) + 1;}
	}
	rep(_,n) {
		int i = d[_], Max = 0, w = n + 1;
		for (Edge *p = a[i]; p; p = p->next) if (p->y != father[i]) if (sum[p->y] > sum[w]) Max = sum[p->y], w = p->y;
		Max = max(Max, n - sum[i]);
		if (i != 1) S[i] = S[father[i]] + n - (sum[i] << 1);
		if (n < (Max << 1)) {
			Ans[i] = -1;
		} else {
			Ans[i] = S[i];
		}
		if (n == (Max << 1)) {if (sum[w] == Max) f[i] = height[w] + 1; else f[i] = far[i];}
	}
	rep(i,n) if (Ans[i] != -1) printf("%lld\n", Ans[i] * 2 - f[i]); else puts("-1");
	return 0;
}


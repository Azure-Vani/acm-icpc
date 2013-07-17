#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 10010;

struct Edge {
	int y, id; Edge *next;
	Edge(int y, int id, Edge *next):y(y), id(id), next(next){}
}*a[MAXN];

int n, m; 

int deep[MAXN], father[MAXN], vis[MAXN], mark[MAXN], odd = 0, where = -1, even[MAXN], mark_E[MAXN];

void Dfs(int u) {
	vis[u] = true;
	for (Edge *p = a[u]; p; p = p->next) if (p->y != father[u]) {
		if (!vis[p->y]) {
			father[p->y] = u;
			deep[p->y] = deep[u] + 1;
			Dfs(p->y);
		} else if (deep[p->y] < deep[u]) {
			if ((deep[u] - deep[p->y]) % 2 == 0) {
				odd++;
				mark[p->y]--;
				mark[u]++;
				where = p->id;
			} else {
				mark_E[p->y]++;
				mark_E[u]--;
			}
		}
	}
}

int stack[MAXN], top = 0, sum[MAXN], fail = false;

void Cal(int u) {
	if (fail) return;
	sum[u] = mark[u]; vis[u] = true; even[u] = mark_E[u];
	for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y]) {
		Cal(p->y);
		sum[u] += sum[p->y];
		even[u] += even[p->y];
		if (sum[p->y] == odd && even[p->y] == 0) {
			stack[++top] = p->id;
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	if (m == 0) {puts("0"); return 0;}
	int self = 0;
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		if (x == y) {self = i; continue;}
		a[x] = new Edge(y, i, a[x]);
		a[y] = new Edge(x, i, a[y]);
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) {
	Dfs(i); }memset(vis, 0, sizeof vis);
	if (self) {
		if (odd) puts("0"); else {
			printf("1\n%d\n", self);
		}
		return 0;
	}
	if (odd == 0) {
		printf("%d\n", m);
		for (int i = 1; i <= m; i++) printf("%d ", i); puts("");
		return 0;
	}
	for (int i = 1; i <= n; i++) if (!vis[i]) {
	Cal(i); }if (odd == 1) stack[++top] = where;
	if (fail) top = 0;
	sort(stack + 1, stack + top + 1);
	printf("%d\n", top);
	for (int i = 1; i <= top; i ++) printf("%d ", stack[i]); puts("");
	return 0;
}


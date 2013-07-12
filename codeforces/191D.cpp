#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100010;

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

int n, m, Ans = 0;
int top[MAXN], low[MAXN], dnf[MAXN], tim = 0;;

vector<int> stack;
vector<int> circle;

inline void Dfs(int u, int father) {
	low[u] = dnf[u] = ++tim;
	stack.push_back(u);
	for (Edge *p = a[u]; p; p = p->next) if (p->y != father) {
		if (dnf[p->y] == 0) {
			Dfs(p->y, u);
			low[u] = min(low[u], low[p->y]);
		} else {
			low[u] = min(low[u], dnf[p->y]);
		}
		if (low[p->y] > dnf[u]) top[u]++;
	}
	if (low[u] == dnf[u]) {
		circle.clear();
		int j;
		do {
			circle.push_back(j = stack.back());
			stack.pop_back();
		} while (j != u);
		reverse(circle.begin(), circle.end()); circle.push_back(u);
		bool go = true; int tmp = 0, tmpu = 0, none = !top[u]; int firsttop = -1;
		for (int i = 0; i < (int)circle.size(); i++) {
			int now = circle[i]; if (firsttop == -1 && top[now] > 0) firsttop = top[now];
			tmp += !!top[now];
			if (now != u) tmpu |= top[now];
			if (i && top[now]) {
				top[now]--, Ans++;
				if (i == (int)circle.size() - 1) go = false;
			}
			if (i != (int)circle.size() - 1 && top[now]) top[now]--;
		}
		if (!tmp && (int)circle.size() > 2) {
			Ans++;
			top[u] = 0;
			return;
		}
		if (!tmpu && (int)circle.size() > 2) Ans++;
		circle.pop_back();
		for (int i = 1; i < (int)circle.size(); i++) {
			Ans += (top[circle[i]] + 1) / 2;
		}
		Ans += (top[u] + go) / 2; if (go) top[u] = 1; else top[u] &= 1;
		if (none && tmp >= 2) {
			top[u] = false;
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	if (m == 0) {puts("0 0"); return 0;}
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
	}
	for (int i = 1; i <= n; i++) if (!dnf[i]) {
		Dfs(i, 0);
		Ans += top[i];
	}
	printf("%d %d\n", Ans, m);
	return 0;
}


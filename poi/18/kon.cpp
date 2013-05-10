#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

namespace Solve {
	const int MAXN = 10003;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) ;
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN], *e[MAXN];

	int n; bool vis[MAXN];
	vector<int> E[MAXN]; int inp[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) {
			int t = ScanInt(); memset(vis, 0, sizeof vis); vis[i] = true;
			for (int j = 1; j <= t; j++) {
				int x = ScanInt(); E[i].push_back(x);
				a[i * 2] = new Edge(x * 2 - 1, a[i * 2]);
				vis[x] = true;
				//printf("%d -> %d;\n", i * 2, x * 2 - 1);
			}
			for (int j = 1; j <= n; j++) if (!vis[j]) a[i * 2 - 1] = new Edge(j * 2, a[i * 2 - 1]);//, printf("%d -> %d;\n", i * 2 - 1, j * 2);
		}
	}


	int stack[MAXN], tim[MAXN], time, belong[MAXN], low[MAXN], top, sum; bool instack[MAXN];
	vector<int> List[MAXN];

	inline void Dfs(int u) {
		tim[u] = low[u] = ++time;
		instack[stack[++top] = u] = true;
		for (Edge *p = a[u]; p; p = p->next) {
			if (!tim[p->y]) {
				Dfs(p->y);
				low[u] = std::min(low[u], low[p->y]);
			} else if (instack[p->y]) low[u] = std::min(low[u], tim[p->y]);
		}
		if (low[u] == tim[u]) {
			int j; ++sum;
			do {
				j = stack[top--];
				belong[j] = sum;
				instack[j] = false;
				List[sum].push_back(j);
			} while (j != u);
		}
	}

	int d[MAXN], head = 1, tail = 0, cnt = 0, linka[MAXN], linkb[MAXN];
	bool choose[MAXN], del[MAXN];
	set<int> clique, backup;

	inline void solve(void) {
		Input();
		for (int i = 1; i <= n * 2; i++) 
			if (!tim[i]) 
				Dfs(i);
		for (int i = 1; i <= n; i++) if (belong[i * 2] == belong[i * 2 - 1]) {puts("0"); return;}
		for (int i = 1; i <= n * 2; i++)
			for (Edge *p = a[i]; p; p = p->next) if (belong[i] != belong[p->y])
				e[belong[p->y]] = new Edge(belong[i], e[belong[p->y]]), inp[belong[i]]++;
		for (int i = 1; i <= sum; i++) if (inp[i] == 0) d[++tail] = i;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = e[now]; p; p = p->next) if (!--inp[p->y]) d[++tail] = p->y;
			if (del[now]) for (Edge *p = e[now]; p; p = p->next) del[p->y] = true; else{
				for (int i = 0; i < (int)List[now].size(); i++) {
					if (List[now][i] % 2 != 0) cnt++, clique.insert((List[now][i] + 1) / 2);
					choose[List[now][i]] = true, del[belong[(1 ^ (List[now][i] - 1)) + 1]] = true;
				}
			}
		}
		backup = clique;
		int Ans = 0, l1 = 0, l2 = 0;
		for (int i = 1; i <= n; i++) {
			clique = backup;
			if (choose[i * 2]) {
				for (int j = 0; j < (int)E[i].size(); ++j) if (choose[E[i][j] * 2 - 1]) clique.erase(E[i][j]);
				if (clique.size() == 0) linka[i] = -1, Ans += (n - cnt > 1), l1++;
				else if (clique.size() == 1) linka[i] = *clique.begin();
			}
			if (choose[i * 2 - 1]) {
				int d = 1, pos;
				for (int j = 0; j < (int)E[i].size(); ++j) if (choose[E[i][j] * 2]) d--, pos = E[i][j];
				if (d == 1) {
					Ans += (cnt > 1); linkb[i] = -1; l2++;
				} else if (d == 0) linkb[i] = pos;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (choose[i * 2]) {
				if (linka[i] > 0 && (linkb[linka[i]] == i || linkb[linka[i]] == -1)) Ans++;
			}
			if (choose[i * 2 - 1]) {
				if (linkb[i] > 0 && (linka[linkb[i]] == -1)) Ans++;
			}
		}
		printf("%d\n", Ans + l1 * l2 + (cnt >= 1 && cnt < n));
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}


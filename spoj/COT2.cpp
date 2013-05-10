#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstring>
#include <map>
#include <set>

using namespace std;

namespace Solve {
	const int MAXN = 200010;
	int A = 100;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	class BIT {public:
		int a[MAXN], n;
		inline void clear(void) {memset(a, 0, sizeof a);}
		inline void insert(int h, int c) {
			for (;h <= n; h += h & -h) a[h] += c;
		}
		inline int Cal(int h) {
			int ret = 0;
			for (;h; h -= h & - h) ret += a[h];
			return ret;
		}
		inline void Add(int l, int r, int c) {
			insert(l, c); insert(r + 1, -c);
		}
	}T;

	struct Edge {
		int y, z; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN], *e[MAXN];

	int n, m, c[MAXN]; set<int> S; map<int, int> M; int L;
	inline void Input(void) {
		n = ScanInt(), m = ScanInt(); T.n = n;
		for (int i = 1; i <= n; i++) c[i] = ScanInt(), S.insert(c[i]);
		for (set<int>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++L;
		for (int i = 1; i <= n; i++) c[i] = M[c[i]];
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
	}

	struct Node {
		Node *ch[2]; int l, r, size;
	}*seg[MAXN];
	
	inline Node* Build(int l, int r) {
		Node *ret = new Node();
		ret->l = l, ret->r = r, ret->size = 0;
		if (l == r) return ret;
		int mid = (l + r) >> 1;
		ret->ch[0] = Build(l, mid);
		ret->ch[1] = Build(mid + 1, r);
		return ret;
	}

	inline Node* Insert(Node *now, int h) {
		Node *ret = new Node(); *ret = *now; ret->size++;
		if (now->l == now->r) {
			return ret;
		}
		int mid = (now->l + now->r) >> 1;
		int d = (h > mid);
		ret->ch[!d] = now->ch[!d];
		ret->ch[d] = Insert(now->ch[d], h);
		return ret;
	}

	inline int Cal(Node *x, Node *y, Node *A, int h) {
		if (x->l == x->r) {
			return x->size + y->size - 2 * A->size;
		}
		int mid = (x->l + x->r) >> 1;
		int d = (h > mid);
		return Cal(x->ch[d], y->ch[d], A->ch[d], h);
	}

	int father[MAXN], deep[MAXN], d[MAXN], maxDeep[MAXN], sum[MAXN], son[MAXN], belong[MAXN];

	inline void Bfs(void) {
		int head = 1, tail = 1; d[1] = 1; deep[1] = 1;
		seg[0] = Build(1, n);
		while (head <= tail) {
			int now = d[head++];
			seg[now] = Insert(seg[father[now]], c[now]);
			for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
				d[++tail] = p->y;
				father[p->y] = now;
				maxDeep[p->y] = deep[p->y] = deep[now] + 1;
			}
		}
		for (int i = tail; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]], maxDeep[father[d[i]]] = max(maxDeep[father[d[i]]], maxDeep[d[i]]);
		belong[1] = 1;
		for (int i = 1; i <= tail; i++) {
			int now = d[i], best = -1; if (!belong[now]) belong[now] = now;
			for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now] && sum[p->y] > best)
				best = sum[p->y], son[now] = p->y;
			belong[son[now]] = belong[now];
		}
	}

	inline int LCA(int x, int y) {
		while (true) {
			if (deep[x] > deep[y]) swap(x, y);
			if (belong[x] == belong[y]) return x;
			if (deep[belong[x]] > deep[belong[y]]) swap(x, y);
			y = father[belong[y]];
		}
	}

	bool inTree[MAXN], end[MAXN];
	int vis[MAXN];
	
	inline int Process(int x, int y, int a[], int d) {
		int ret = 0;
		while (deep[x] > deep[y]) {
			if (!a[c[x]]) ret++;
			a[c[x]] += d;
			x = father[x];
		}
		return ret;
	}

	inline int Gao(int x, int y) {
		int A = LCA(x, y);
		int l1 = Process(x, father[A], vis, 1);
		int l2 = Process(y, A, vis, 1);
		Process(x, father[A], vis, -1);
		Process(y, A, vis, -1);
		return l1 + l2;
	}

	inline void Force(void) {
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			printf("%d\n", Gao(x, y));
		}
	}

	int root[MAXN];

	struct Query {
		int x, y;
	}q[MAXN];

	int Ans[MAXN], tmpDeep[MAXN], last[MAXN], lca[MAXN], cur;

	inline void Dfs(int u, int f) {
		T.Add(tmpDeep[last[c[u]]] + 1, tmpDeep[u], 1); int backup = vis[u];
		vis[u] = cur; int w = last[c[u]];
		last[c[u]] = u;
		for (Edge *p = e[u]; p; p = p->next) if ( vis[p->y] == cur) {
			int ret = T.Cal(tmpDeep[p->y]);
			Ans[p->z] = ret;
		}
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f && inTree[p->y]) {
			tmpDeep[p->y] = tmpDeep[u] + 1;
			Dfs(p->y, u);
		}
		last[c[u]] = w;
		vis[u] = backup;
		T.Add(tmpDeep[last[c[u]]] + 1, tmpDeep[u], -1);
	}

	int list[MAXN], top, cnt = 0;
	pair<int, int> other[MAXN];

	inline void Addition(void) {
		int i = 1;
		while (i <= cnt) {
			top = 0, cur++; int w = other[i].second;
			while (i <= cnt && other[i].second == w) {
				int t = other[i].first;
				while (!inTree[t]) list[++top] = t, t = father[t];
				i++;
			}
			int X = q[w].x, Y = q[w].y, A = lca[w];
			for (int j = 1; j <= top; j++) {
				if (vis[c[list[j]]] != cur) {
					int tmp = (c[A] == c[list[j]] || Cal(seg[X], seg[Y], seg[A], c[list[j]]));
					if (tmp == 0) Ans[w]++;
					vis[c[list[j]]] = cur;
				}
			}
		}
	}

	inline void Work(void) {
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt();
			assert(x <= n && y <= n);
			if (root[x] == root[y] && !inTree[x]) {
				Ans[i] = Gao(x, y);
				continue;
			}
			if (x != root[x]) other[++cnt].first = x, other[cnt].second = i;
			if (y != root[y]) other[++cnt].first = y, other[cnt].second = i;
			x = root[x], y = root[y];
			q[i].x = x, q[i].y = y;
			lca[i] = LCA(x, y);
		}
		for (int i = 1; i <= m; i++) if (q[i].x) {
			e[q[i].x] = new Edge(q[i].y, e[q[i].x]);
			e[q[i].x]->z = i;
			e[q[i].y] = new Edge(q[i].x, e[q[i].y]);
			e[q[i].y]->z = i;
		}
		for (int i = 1; i <= n; i++) if (end[i]) {
			cur++;
			memset(tmpDeep, 0, sizeof tmpDeep); T.clear();
			memset(last, 0, sizeof last); 
			tmpDeep[i] = 1;
			Dfs(i, 0); 
		}
	}

	inline void solve(void) {
		Input();
		Bfs();
		int tmp = 0;
		for (int i = 1; i <= n; i++) {
			if (maxDeep[i] - deep[i] == A) end[i] = true, tmp++;
			if (maxDeep[i] - deep[i] >= A) inTree[i] = true;
		}
		for (int i = 1; i <= n; i++) {
			if (inTree[d[i]]) root[d[i]] = d[i];
			for (Edge *p = a[d[i]]; p; p = p->next) if (p->y != father[d[i]] && !inTree[p->y])
				root[p->y] = root[d[i]];
		}
		if (!tmp || tmp >= 50) {
			Force();
		} else {
			Work();
			Addition();
			for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
		}
	}
}

int main(void) {
	Solve::solve();
	return 0;
}


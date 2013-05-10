#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cctype>

#define Max(a,b) ((a)>(b)?(a):(b))
#define Min(a,b) ((b)>(a)?(a):(b))

using namespace std;

namespace Solve {
	const int MAXN = 100010;
	const int inf = ~0U>>2;

	struct Edge {
		int y, c; Edge *next, *opt; bool flag;
		Edge(int y, int c, Edge *next):y(y), c(c), next(next){flag = true;}
	}*a[MAXN];

	pair<int, int> E[MAXN]; int n;

	inline void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i < n; i++) {
			int &x = E[i].first, &y = E[i].second, z; scanf("%d%d%d", &x, &y, &z);
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
		}
	}

	struct Node {
		int l, r; Node *ch[2]; int same, d, s;
		Node(int _l = 0, int _r = 0){l = _l, r = _r, same = -inf, d = -inf, s = -inf, ch[0] = NULL, ch[1] = NULL;}
		inline void Same(int u) {
			same = u, d = -inf, s = u;
		}
		inline void Add(int u) {
			if (d == -inf) d = u; else d += u; s += u;
		}
		inline void Down(void) {
			if (ch[0] == NULL) return;
			if (same > -inf) {
				ch[0]->Same(same);
				ch[1]->Same(same);
				same = -inf;
			}
			if (d > -inf) {
				ch[0]->Add(d);
				ch[1]->Add(d);
				d = -inf;
			}
		}
		inline void Update(void) {if (ch[0] != NULL) s = Max(ch[0]->s, ch[1]->s);}
		inline void Add(int L, int R, int u) {
			if (L > R) return;
			if (L <= l && r <= R) {
				Add(u);
				return;
			}
			Down();
			int mid = (l + r) >> 1;
			ch[0]->Add(L, min(R, mid), u);
			ch[1]->Add(max(mid + 1, L), R, u);
			Update();
		}
		inline void Same(int L, int R, int u) {
			if (L > R) return;
			if (L <= l && r <= R) {
				Same(u);
				return;
			}
			Down();
			int mid = (l + r) >> 1;
			ch[0]->Same(L, min(R, mid), u);
			ch[1]->Same(max(mid + 1, L), R, u);
			Update();
		}
		inline int Cal(int L, int R) {
			if (L > R) return -inf;
			if (L <= l && r <= R) return s;
			int mid = (l + r) >> 1;
			Down();
			Update();
			return max(ch[0]->Cal(L, min(R, mid)), ch[1]->Cal(max(L, mid + 1), R));
		}
		inline void Build(int L, int R, int a[]) {
			l = L, r = R;
			if (l == r) {s = a[l]; return;}
			int mid = (l + r) >> 1;
			(ch[0] = new Node())->Build(l, mid, a);
			(ch[1] = new Node())->Build(mid + 1, r, a);
			Update();
		}
	}root[MAXN];

	int d[MAXN], son[MAXN], belong[MAXN], deep[MAXN], father[MAXN], sum[MAXN], list[MAXN], top, cost[MAXN], fim[MAXN], seg_n = 0, pos[MAXN];

	inline void Cut(void) {
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p;p = p->next) if (p->flag) {
				p->opt->flag = false;
				d[++tail] = p->y;
				father[p->y] = now;
				deep[p->y] = deep[now] + 1;
				cost[p->y] = p->c;
			}
		}
		for (int i = n; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]];
		for (int i = 1; i <= n; i++) {
			int best = 0, now = d[i];
			if (belong[now] == 0) belong[now] = now;
			for (Edge *p = a[now]; p; p = p->next) if (p->flag && sum[p->y] > best) best = sum[p->y], son[now] = p->y;
			if (son[now]) belong[son[now]] = belong[now];
			if (best == 0) {
				top = 0; int now = d[i]; seg_n++;
				while (belong[now] == belong[d[i]]) {
					list[++top] = cost[now];
					fim[now] = seg_n;
					pos[now] = top;
					now = father[now];
				}
				root[seg_n].Build(1, top, list);
			}
		}
	}

	inline int LCA(int x, int y) {
		while (true) {
			if (deep[x] > deep[y]) swap(x, y);
			if (belong[x] == belong[y]) return x;
			if (deep[belong[x]] > deep[belong[y]]) x = father[belong[x]]; else y = father[belong[y]];
		}
	}

	//0: query 1: add 2: same
	inline int Gao(int x, int A, int c, int type) {
		int ret = -inf;
		while (true) {
			if (deep[x] <= deep[A]) return ret;
			int y = belong[x]; if (deep[y] <= deep[A]) y = son[A];
			int L = pos[x], R = pos[y]; Node &r = root[fim[x]];
			if (type == 0) ret = max(ret, r.Cal(L, R));
			if (type == 1) r.Add(L, R, c);
			if (type == 2) r.Same(L, R, c);
			x = father[y];
		}
	}

	char ch[10];
	inline void Work(void) {
		for (int i = 1; i < n; i++) if (deep[E[i].first] > deep[E[i].second]) swap(E[i].first, E[i].second);
		while (true) {
			int x, y; scanf("%s %d %d", ch, &x, &y);
			if (ch[0] == 'M') {
				int A = LCA(x, y);
				int L = Gao(x, A, 0, 0);
				int R = Gao(y, A, 0, 0);
				printf("%d\n", Max(L, R));
			}
			if (ch[0] == 'A') {
				int A = LCA(x, y);
				int c; scanf("%d", &c);
				Gao(x, A, c, 1);
				Gao(y, A, c, 1);
			}
			if (ch[0] == 'C') {
				if (ch[1] == 'o') {
					int A = LCA(x, y), c; scanf("%d", &c);
					Gao(x, A, c, 2);
					Gao(y, A, c, 2);
				}
				if (ch[1] == 'h') {
					Gao(E[x].second, E[x].first, y, 2);
				}
			}
			if (ch[0] == 'S') break;
		}
	}

	inline void solve(void) {
		Input();
		Cut();
		Work();
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

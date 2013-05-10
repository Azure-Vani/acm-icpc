#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

namespace Solve {
	const int MAXN = 100010;
	const int MM = 3000000;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int n, color[MAXN];

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) color[i] = ScanInt();
		for (int i = 1; i <  n; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
	}

	inline int clz(int x) {
		return !x ? - 1 : 31 - __builtin_clz(x);
	}

	struct Node {
		Node *l, *r; int size, cover, low, high;char i;
	}*root[MAXN], POOL[MM], *stack[MM], Tnull, *null = &Tnull; int top;

	inline Node* getnew(int x, int s = 1) {
		Node *ret = stack[top--];
		ret->l = ret->r = null; ret->size = s; ret->cover = 0, ret->low = ret->high = x, ret->i = -1;
		return ret;
	}
	inline Node* getnew(Node *L, Node *R) {
		Node *ret = stack[top--];
		ret->l = L, ret->r = R; ret->size = L->size + R->size; ret->cover = 0; ret->low = L->low ^ L->cover, ret->high = R->high ^ R->cover; ret->i = clz(ret->low ^ ret->high);
		return ret;
	}
	inline void Delete(Node *x) {
		stack[++top] = x;
	}

	inline void Down(Node *x) {
		if (x == null) return;
		x->low ^= x->cover;
		x->high ^= x->cover;
		x->l->cover ^= x->cover;
		x->r->cover ^= x->cover;
		if (x->cover & (1 << x->i)) {
			swap(x->l, x->r);
			swap(x->low, x->high);
		}
		x->cover = 0;
	}

	inline Node* Merge(Node *L, Node *R) {
		if (L == null) return R;
		if (R == null) return L;
		Down(L); Down(R);
		int v = clz(min(L->low, R->low) ^ max(L->high, R->high));
		if (v != L->i && v != R->i) return L->low < R->low ? getnew(L, R) : getnew(R, L);
		if (L->i == R->i) {
			Node *ll = L->l, *lr = L->r, *rl = R->l, *rr = R->r;
			if (L->i == -1) {
				Node *ret = getnew(L->low);
				Delete(L); Delete(R);
				return ret;
			}
			Delete(L); Delete(R);
			return getnew(Merge(ll, rl), Merge(lr, rr));
		}
		if (R->i > L->i) swap(L, R);
		Node *l = L->l, *r = L->r; int t = L->i;
		Delete(L);
		if (R->low & (1 << t)) return getnew(l, Merge(r, R));
		else return getnew(Merge(l, R), r);
	}

	inline int mex(Node *x, int v, int k = 0) {
		if (x == null) return 0;
		Down(x);
		if (x->i == -1) return x->low == k ? k + 1 : k;
		if ((((1 << v) - 1) - ((1 << x->i) - 1)) & x->low) return k;
		if (x->l->size < (1 << x->i)) return mex(x->l, x->i, k);
		else return mex(x->r, x->i, (x->low|((1<<x->i) - 1)) + 1);
	}

	int sg[MAXN];

	inline void Dfs(int u, int f) {
		int g = 0;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f)
			Dfs(p->y, u), g ^= sg[p->y];
		root[u] = (color[u] == 1) ? null : getnew(g);
		null->cover = 0;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
			root[p->y]->cover ^= g ^ sg[p->y];
			root[u] = Merge(root[u], root[p->y]);
		}
		sg[u] = mex(root[u], clz(root[u]->high) + 1);
	}

	vector<int> Ans;

	inline void Dfs(int u, int sum, int f) {
		int g = 0;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) g ^= sg[p->y];
		int tmp = sum ^ sg[u] ^ g;
		if (!color[u] && !tmp) Ans.push_back(u);
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) Dfs(p->y, tmp, u);
	}

	inline void solve(void) {
		Input();
		for (int i = 1; i < MM; i++) stack[i] = POOL + i; top = MM - 1;
		Dfs(1, 0);
		if (sg[1] == 0) puts("-1"); else {
			Dfs(1, sg[1], 0);
			sort(Ans.begin(), Ans.end());
			for (int i = 0; i < (int)Ans.size(); i++) printf("%d\n", Ans[i]);
		}
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}


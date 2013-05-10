#include <cstdio>
#include <cctype>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

namespace Solve {
	const int MAXN = 200010;
	
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	int n, c[MAXN], m, L = 0; set<int> S; map<int, int> M, fim;
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) c[i] = ScanInt(), S.insert(c[i]);
		for (set<int>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++L, fim[L] = *it;
		for (int i = 1; i <= n; i++) c[i] = M[c[i]];
		for (int i = 1; i <  n; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
	}

	struct Node {
		Node* ch[2]; int l, r, size;
	}*root[MAXN];

	inline Node* Build(int l, int r) {
		Node *ret = new Node();
		int mid = (l + r) >> 1;
		ret->l = l, ret->r = r, ret->size = 0;
		if (l == r) return ret;
		ret->ch[0] = Build(l, mid);
		ret->ch[1] = Build(mid + 1, r);
		return ret;
	}

	inline Node* Insert(Node *now, int h) {
		Node *ret = new Node(); *ret = *now;
		if (now->l == now->r) {
			ret->size++;
			return ret;
		}
		int mid = (now->l + now->r) >> 1, d = (h > mid);
		ret->ch[d] = Insert(now->ch[d], h);
		ret->ch[!d] = now->ch[!d];
		ret->size = ret->ch[0]->size + ret->ch[1]->size;
		return ret;
	}

	inline int Cal(Node *x, Node *y, Node *A, int t, int k) {
		if (x->l == x->r) return x->l;
		int mid = (x->l + x->r) >> 1;
		int s = x->ch[0]->size + y->ch[0]->size - 2 * A->ch[0]->size + (t >= x->l && t <= mid);
		int ret = 0;
		if (k <= s) ret = Cal(x->ch[0], y->ch[0], A->ch[0], t, k);
		else ret = Cal(x->ch[1], y->ch[1], A->ch[1], t, k - s);
		return ret;
	}

	int father[MAXN], sum[MAXN], son[MAXN], belong[MAXN], deep[MAXN], d[MAXN];

	inline void Pre(void) {
		int head = 1, tail = 1; d[1] = 1;
		root[0] = Build(1, L);
		while (head <= tail) {
			int now = d[head++];
			root[now] = Insert(root[father[now]], c[now]);
			for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now]) {
				father[p->y] = now;
				deep[p->y] = deep[now] + 1;
				d[++tail] = p->y;
			}
		}
		for (int i = tail; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]];
		belong[1] = 1;
		for (int i = 1; i <= tail; i++) {
			int best = -1, now = d[i];
			if (belong[now] == 0) belong[now] = now;
			for (Edge *p = a[now]; p; p = p->next) if (p->y != father[now] && sum[p->y] > best)
				best = sum[p->y], son[now] = p->y;
			belong[son[now]] = belong[now];
		}
	}

	inline int LCA(int a, int b) {
		while (true) {
			if (deep[a] > deep[b]) swap(a, b);
			if (belong[a] == belong[b]) return a;
			if (deep[belong[a]] > deep[belong[b]]) swap(a, b);
			b = father[belong[b]];
		}
	}

	inline void Process(void) {
		int Ans = 0;
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(), k = ScanInt();
			int A = LCA(x, y); 
			Ans = Cal(root[x], root[y], root[A], c[A], k);
			printf("%d\n", fim[Ans]);
		}
	}

	inline void solve(void) {
		Input();
		Pre();
		Process();
	}
}

int main(void) {
	Solve::solve();
	return 0;
}


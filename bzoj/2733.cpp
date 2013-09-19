#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 100010;

struct Node {
	Node *ch[2], *p; int val, index, size;
	inline bool dir(void) {return this == p->ch[1];}
	inline void SetC(Node *x, bool d) {ch[d] = x;x->p = this;}
	inline void Update(void) {size = ch[0]->size + ch[1]->size + 1;}
}Tnull, *null = &Tnull, *fim[MAXN], *d[MAXN];

inline void rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	p->p->SetC(x, p->dir());
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
	p->Update();
}

inline void splay(Node *x) {
	while (x->p != null) {
		if (x->p->p == null) rotate(x); else {
			if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);} else {rotate(x); rotate(x);}
		}
	}
	x->Update();
}

inline void insert(Node *&now, Node *p, Node *u) {
	if (now == null) {
		now = u; now->ch[0] = now->ch[1] = null; p->SetC(now, now->val > p->val); now->size = 1;
		splay(now);
		return;
	}
	now->size++;
	if (u->val <= now->val) insert(now->ch[0], now, u);
	else insert(now->ch[1], now, u);
}

inline Node* Select(Node *now, int k) {
	if (k > now->size) return null;
	while (true) {
		if (now->ch[0]->size + 1 == k) {splay(now); return now;}
		if (now->ch[0]->size + 1 < k) k -= now->ch[0]->size + 1, now = now->ch[1];
		else now = now->ch[0];
	}
}

int n, m, f[MAXN];

inline int get(int x) {return x == f[x] ? x : f[x] = get(f[x]);}

inline void link(int x, int y) {
	x = get(x); y = get(y);
	if (x != y) {
		f[x] = y;
		splay(fim[x]); splay(fim[y]);
		if (fim[x]->size > fim[y]->size) swap(x, y);
		int head = 1, tail = 1; d[1] = fim[x]; Node *last = fim[y];
		while (head <= tail) {
			Node *now = d[head++];
			if (now->ch[0] != null) d[++tail] = now->ch[0];
			if (now->ch[1] != null) d[++tail] = now->ch[1];
			insert(last, null, now); last = now;
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m); null->index = -1;
	for (int i = 1; i <= n; i++) {
		int x; scanf("%d", &x);
		fim[i] = new Node(); fim[i]->ch[0] = fim[i]->ch[1] = fim[i]->p = null; fim[i]->index = i; fim[i]->val = x; fim[i]->size = 1;
		f[i] = i;
	}
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		link(x, y);
	}
	int q; scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		char ch[3]; scanf("%s", ch);
		if (ch[0] == 'B') {
			int x, y; scanf("%d%d", &x, &y);
			link(x, y);
		} else {
			int x, k; scanf("%d%d", &x, &k);
			splay(fim[x]);
			printf("%d\n", Select(fim[x], k)->index);
		}
	}
	return 0;
}

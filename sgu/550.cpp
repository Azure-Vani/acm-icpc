#include <cstdio>
#include <cctype>
#include <algorithm>

using namespace std;

const int MAXN = 200010, mod = 99990001, inf = ~0U>>1;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Edge {
	int y, c, flag; Edge *next, *opt; 
	Edge(int y, int c, Edge *next):y(y), c(c), next(next){flag = true;}
}*a[MAXN], *E[MAXN];

int n;

struct Node {
	Node *ch[2], *p; int d;
	Node();
	inline bool dir(void) {return this == p->ch[1];}
	inline void SetC(Node *x, int d) {ch[d] = x, x->p = this;}
}Tnull, *null = &Tnull, *fim[MAXN];

Node::Node(){ch[0] = ch[1] = p = null;d = 0;}

inline bool isRoot(Node *x) {return x->p == null || (x->p->ch[0] != x && x->p->ch[1] != x);}

inline void Rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	if (!isRoot(x->p)) p->p->SetC(x, p->dir()); else x->p = p->p;
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
}

inline void Splay(Node *x) {
	while (!isRoot(x)) {
		if (isRoot(x->p)) {Rotate(x); break;}
		if (x->dir() == x->p->dir()) {Rotate(x->p); Rotate(x);} else {Rotate(x); Rotate(x);}
	}
}

inline void Access(Node *x) {
	Node *t = x, *q = null;
	for (; x != null; x = x->p) {
		Splay(x); x->ch[1] = q, q = x;
	}
	Splay(t);
}

inline Node *getRoot(Node *x) {
	Access(x); 
	while (x->ch[0] != null) x = x->ch[0]; return x;
}

int father[MAXN], d[2][MAXN], hash[MAXN];

inline void Bfs(int u, int add = 0, int multi = 0, bool change = 0) {
	int head = 1, tail = 1; d[0][1] = u; static int cur = 0; ++cur; hash[u] = cur;
	while (head <= tail) {
		int now = d[0][head++];
		for (Edge *p = a[now]; p; p = p->next) if (p->flag && hash[p->y] != cur) {
			if (!change) {
				father[p->y] = now; 
				fim[p->y]->p = fim[now];
			}else {
				p->c = (p->c + add) % mod;
				p->c = (long long) p->c * multi % mod;
				p->opt->c = p->c;
			}
			hash[d[0][++tail] = p->y] = cur;
		}
	}
}

int vis[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	n = ScanInt();
	for (int i = 1; i <= n; i++) fim[i] = new Node();
	for (int i = 1; i < n; i++) {
		int x = ScanInt(), y = ScanInt(), w = ScanInt();
		a[x] = new Edge(y, w, a[x]);
		a[y] = new Edge(x, w, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
		E[i] = a[x];
	}
	Bfs(1);
	for (int k = 1; k < n; k++) {
		int t = ScanInt(), x = E[t]->y, y = E[t]->opt->y; E[t]->flag = E[t]->opt->flag = false;
		if (father[y] != x) swap(x, y); father[y] = 0;
		int head[2] = {1,1}, tail[2] = {1,1}, cnt[2] = {1, 1}, Min[2];
		d[0][1] = x, d[1][1] = y; Edge *p[2] = {0, 0}; Min[0] = x, Min[1] = y; vis[x] = vis[y] = k;
		while (head[0] <= tail[0] && head[1] <= tail[1]) {
			for (int i = 0; i < 2; i++) {
				while (head[i] <= tail[i]) {
					while (!p[i] && head[i] <= tail[i]) p[i] = a[d[i][head[i]++]];
					while (p[i] && (!p[i]->flag || vis[p[i]->y] == k)) p[i] = p[i]->next;
					if (p[i]) {
						vis[d[i][++tail[i]] = p[i]->y] = k, p[i] = p[i]->next; 
						cnt[i]++; Min[i] = min(Min[i], d[i][tail[i]]);
						break;
					}
				}
			}
		}
		Node *r = getRoot(fim[x]);
		int now = (r->d + E[t]->c) % mod;
		printf("%d\n", now); fflush(stdout);
		if (cnt[0] < cnt[1] || (cnt[0] == cnt[1] && Min[0] < Min[1])) {
			Bfs(x, r->d, now, 1);
			fim[y]->d = (fim[y]->d + now + r->d) % mod;
			r->d = 0;
		} else {
			Bfs(y, r->d, now, 1);
			r->d = (r->d + now) % mod;
		}
		Access(fim[x]); Splay(fim[y]);
		fim[y]->p = null;
	}
	return 0;
}


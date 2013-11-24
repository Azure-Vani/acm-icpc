#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 100010, mod = 51061;

struct Node {
	Node *ch[2], *p; int size, value;
	bool rev; int sum, add, mul;
	Node(int t = 0);
	inline bool dir(void) {return p->ch[1] == this;}
	inline void SetC(Node *x, bool d) {
		ch[d] = x; x->p = this;
	}
	inline void Rev(void) {
		swap(ch[0], ch[1]); rev ^= 1;
	}
	inline void Add(int c) {
		add += c; sum += c * size; sum %= mod; add %= mod;
		value += c; value %= mod;
	}
	inline void Multi(int c) {
		add = (long long) add * c % mod;
		mul = (long long) mul * c % mod;
		sum = (long long) sum * c % mod;
		value = (long long) value * c % mod;
	}
	inline void Push(void) { 
		if (rev) {
			ch[0]->Rev();
			ch[1]->Rev();
			rev = 0;
		}
		ch[0]->Multi(mul); ch[1]->Multi(mul); mul = 1;
		ch[0]->Add(add); ch[1]->Add(add); add = 0;
	}
	inline void Update(void) { 
		size = ch[0]->size + ch[1]->size + 1;
		sum = (ch[0]->sum + ch[1]->sum + value) % mod;
	}
}Tnull, *null = &Tnull, *fim[MAXN];

Node::Node(int _value){ch[0] = ch[1] = p = null; sum = value = _value, rev = 0, add = 0, size = mul = 1;}

inline bool isRoot(Node *x) {return x->p == null || (x != x->p->ch[0] && x != x->p->ch[1]);}

inline void rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	p->Push(); x->Push();
	if (!isRoot(p)) p->p->SetC(x, p->dir()); else x->p = p->p;
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
	p->Update();
}

inline void splay(Node *x) {
	x->Push();
	while (!isRoot(x)) {
		if (isRoot(x->p)) rotate(x);
		else {
			if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);} 
			else {rotate(x); rotate(x);}
		}
	}
	x->Update();
}

inline Node* Access(Node *x) {
	Node *t = x, *q = null;
	for (; x != null; x = x->p) {
		splay(x); x->ch[1] = q; q = x;
	}
	splay(t); //info will be updated in the splay;
	return q;
}

inline void Evert(Node *x) {
	Access(x); x->Rev();
}

inline void link(Node *x, Node *y) {
	Evert(x); x->p = y;
}

inline Node* getRoot(Node *x) {
	Node *tmp = x;
	Access(x);
	while (tmp->ch[0] != null) tmp = tmp->ch[0];
	splay(tmp);
	return tmp;
}

inline void cut(Node *x, Node *y) {
	Access(x); splay(y);
	if (y->p != x) swap(x, y);
	Access(x); splay(y);
	y->p = null;
}

inline Node* getPath(Node *x, Node *y) {
	Evert(x); Access(y);
	return y;
}

int n, q;

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &q); null->size = 0; null->sum = 0;
	for (int i = 1; i <= n; i++) fim[i] = new Node(1);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		link(fim[x], fim[y]);
	}
	char ch[3];
	for (int i = 1, x, y; i <= q; i++) {
		scanf("%s %d %d", ch, &x, &y);
		if (strcmp(ch, "+") == 0) {
			int c; scanf("%d", &c);
			getPath(fim[x], fim[y])->Add(c);
		}
		if (strcmp(ch, "-") == 0) {
			int x2, y2; scanf("%d%d", &x2, &y2);
			cut(fim[x], fim[y]); link(fim[x2], fim[y2]);
		}
		if (strcmp(ch, "*") == 0) {
			int c; scanf("%d", &c);
			getPath(fim[x], fim[y])->Multi(c);
		}
		if (strcmp(ch, "/") == 0) printf("%d\n", getPath(fim[x], fim[y])->sum);
	}
	return 0;
}


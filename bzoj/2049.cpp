#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

const int MAXN = 100010;
int n, m; char ch[10];

inline int ScanInt(void) {
	int r = 0, c;
	while (!isdigit(c = getchar())) ;
	r = c - '0';
	while ( isdigit(c = getchar())) r = r * 10 + c - 48;
	return r;
}

struct Node {
	Node *ch[2], *p; bool rev; Node(); int v;
	inline bool dir(void) {return this == p->ch[1];}
	inline void Push(void) {if (rev) {ch[0]->Rev(), ch[1]->Rev(); rev = 0;}}
	inline void Rev(void) {swap(ch[0], ch[1]); rev ^= 1;}
	inline void SetC(Node *x, bool d) {ch[d] = x; x->p = this;}
}Tnull, *null = &Tnull, *fim[MAXN];

Node::Node():rev(false){p = ch[0] = ch[1] = null;}

inline bool IsRoot(Node *x) {return x->p == null || (x->p->ch[0] != x && x->p->ch[1] != x);}

inline void Rotate(Node *x) {
	Node *p = x->p; bool d = x->dir();
	p->Push();x->Push();
	if (!IsRoot(p)) p->p->SetC(x, p->dir()); else x->p = p->p;
	p->SetC(x->ch[!d], d);
	x->SetC(p, !d);
}

inline void Splay(Node *x) {
	x->Push();
	while (!IsRoot(x)) {
		if (IsRoot(x->p)) {Rotate(x); break;}
		if (x->dir() == x->p->dir()) {Rotate(x->p); Rotate(x);} else {Rotate(x); Rotate(x);}
	}
}

inline Node* Access(Node *x) {
	Node *t = x;
	for (Node *q = null; x != null; x = x->p) {
		Splay(x), x->ch[1] = q, q = x;
	}
	Splay(t);
	return t;
}

inline Node* Getroot(Node *x) {
	Access(x);
	while (x->Push(), x->ch[0] != null) x = x->ch[0]; 
	return x;
}

inline void Evert(Node *x) {
	Access(x);
	x->Rev();
}

int main(void) {
	n = ScanInt(), m = ScanInt();
	REP(i, 1, n) fim[i] = new Node(), fim[i]->v = i;
	REP(_,1,m) {
		scanf("%s", ch); int x = ScanInt(), y = ScanInt();
		if (strcmp(ch, "Query") == 0) {
			Node *X = Getroot(fim[x]);
			Node *Y = Getroot(fim[y]);
			puts(X==Y?"Yes":"No");
		}
		if (strcmp(ch, "Destroy") == 0) {
			Evert(fim[x]);
			Access(fim[y]);
			fim[y]->ch[0] = null; fim[x]->p = null;
		}
		if (strcmp(ch, "Connect") == 0) {
			Evert(fim[x]);
			Evert(fim[y]);
			fim[y]->p = fim[x];
		}
	}
	return 0;
}


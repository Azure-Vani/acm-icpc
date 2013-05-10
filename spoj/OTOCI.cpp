//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	
	const int MAXN = 30010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline int ScanStr(char *s) {
		int t, l = 0;
		while (!isalpha(t = getchar()));
		s[l++] = t;
		while ( isalpha(t = getchar())) s[l++] = t; s[l] = '\0';
		return t;
	}

	struct Node {
		Node *ch[2], *p; int sum, v, rev, id;
		Node(){} Node(int);
		inline bool dir(void) {return p->ch[1] == this;} 
		inline void SetC(Node *x, int d) {ch[d] = x; x->p = this;}
		inline void Rev(void) {rev ^= 1; swap(ch[0], ch[1]);}
		inline void Update(void) {sum = ch[0]->sum + ch[1]->sum + v;}
		inline void Push(void) {if (rev) ch[0]->Rev(), ch[1]->Rev(); rev = 0;}
	}Tnull, *null = &Tnull, *fim[MAXN];

	Node::Node(int _v){p = ch[0] = ch[1] = null, sum = v = _v, rev = 0;}

	inline bool isRoot(Node *x) {return x->p == null || (x->p->ch[0] != x && x->p->ch[1] != x);}

	inline void Rotate(Node *x) {
		Node *p = x->p; bool d = x->dir();
		p->Push(), x->Push();
		if (!isRoot(x->p)) p->p->SetC(x, p->dir()); else x->p = p->p;
		p->SetC(x->ch[!d], d);
		x->SetC(p, !d);
		p->Update();
	}

	inline void Splay(Node *x) {
		while (!isRoot(x)) {
			if (isRoot(x->p)) {Rotate(x); return;}
			if (x->dir() == x->p->dir()) {Rotate(x->p); Rotate(x);} else {Rotate(x); Rotate(x);}
		}
		x->Update();
	}

	inline void Access(Node *x) {
		Node *t = x;
		for (Node *q = null; x != null; x = x->p) {
			Splay(x); x->Push(); x->ch[1] = q, q = x;
		}
		Splay(t);
	}
	inline void Evert(Node *x) {
		Access(x);
		x->Rev();
	}
	inline Node* getRoot(Node *x) {
		Access(x);
		while (x->Push(), x->ch[0] != null) x = x->ch[0];
		return x;
	}

	inline void solve(void) {
		int n = ScanInt();
		rep(i,n) fim[i] = new Node(ScanInt());
		rep(i,n) fim[i]->id = i;
		int q = ScanInt();
		rep(i,q) {
			char ch[20]; ScanStr(ch);
			if (strcmp(ch, "excursion") == 0) {
				int x = ScanInt(), y = ScanInt();
				Evert(fim[x]);
				Access(fim[y]);
				if (getRoot(fim[y]) != fim[x]) puts("impossible"); else
				printf("%d\n", fim[y]->sum);
			} else
			if (strcmp(ch, "bridge") == 0) {
				int x = ScanInt(), y = ScanInt();
				Evert(fim[x]);
				Access(fim[y]);
				if (getRoot(fim[y]) == fim[x]) puts("no"); else {
					puts("yes");
					fim[x]->p = fim[y];
				}
			} else 
			if (strcmp(ch, "penguins") == 0) {
				int x = ScanInt(), u = ScanInt();
				Access(fim[x]); fim[x]->sum += u - fim[x]->v;
				fim[x]->v = u;
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}


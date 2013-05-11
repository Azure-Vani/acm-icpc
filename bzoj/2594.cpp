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
#define cl(a) memset(a,0,sizeof a);
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define OK(a) cerr<<"OK at "<<a<<"!"<<endl;

using namespace std;

namespace Solve {
	const int MAXN = 200020;
	const int MAXM = 2000020;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	
	pair<int, pair<int, int> > E[MAXM], Q[MAXN];
	set<pair<int, int> > res;
	map<pair<int, int>, int> V;

	int n, m, q, f[MAXN];

	inline int get(int x) {return f[x] == x?x:(f[x] = get(f[x]));}

	struct Node {
		Node *ch[2], *p, *w; int v; bool rev;
		Node();
		inline bool dir(void) {return p->ch[1] == this;}
		inline void SetC(Node *x, bool d) {ch[d] = x; x->p = this;}
		inline void Rev(void) {rev ^= 1; swap(ch[0], ch[1]);}
		inline void Push(void) {if (rev) ch[0]->Rev(), ch[1]->Rev(); rev = 0;}
		inline void Update(void) {w = this; if (ch[0]->w->v > w->v) w = ch[0]->w; if (ch[1]->w->v > w->v) w = ch[1]->w;}
	}Tnull, *null = &Tnull, *fim[MAXN];
	Node::Node() {ch[0] = ch[1] = p = w = null; v = 0; rev = 0;}
	
	inline bool isRoot(Node *x) {return x->p == null || (x != x->p->ch[1] && x != x->p->ch[0]);}

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
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);} else {rotate(x); rotate(x);}
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

	inline Node* ask(Node *x, Node *y) {
		Evert(x); Access(y);
		return y->w;
	}

	vector<int> Ans;

	inline void solve(void) {
		n = ScanInt(), m = ScanInt(), q = ScanInt();
		rep(i,n*2) fim[i] = new Node();
		rep(i,n) f[i] = i;
		rep(i,m) {
			int x, y;
			x = E[i].second.first = ScanInt(), y = E[i].second.second = ScanInt(), E[i].first = ScanInt(), V[mp(min(x, y), max(x, y))] = E[i].first;
		}
		rep(i,q) {
			int x, y;
			Q[i].first = ScanInt(), x = Q[i].second.first = ScanInt(), y = Q[i].second.second = ScanInt();
			if (Q[i].first == 2) res.insert(mp(min(x,y), max(x,y)));
		}
		sort(E + 1, E + 1 + m);
		int cnt = n;
		for (int i = 1; i <= m; i++) {
			int x = E[i].second.first, y = E[i].second.second; if (x > y) swap(x, y);
			if (get(x) == get(y) || res.find(mp(x,y)) != res.end()) continue;
			f[get(x)] = y; ++cnt;
			fim[cnt]->v = E[i].first;
			fim[cnt]->w = fim[cnt];
			link(fim[x], fim[cnt]); link(fim[y], fim[cnt]);
		}
		for (int i = q; i >= 1; i--) {
			int type = Q[i].first, x = Q[i].second.first, y = Q[i].second.second; if (x > y) swap(x, y);
			int tmp = V[mp(x, y)];
			if (type == 1) {
				Ans.pb(ask(fim[x], fim[y])->v);
			} else
			if (type == 2) {
				if (get(x) != get(y)) {
					f[get(x)] = get(y);++cnt;
					fim[cnt]->v = tmp;
					fim[cnt]->w = fim[cnt];
					link(fim[x], fim[cnt]); link(fim[y], fim[cnt]);
					continue;
				}
				Node *t = ask(fim[x], fim[y]);
				if (t->v <= tmp) continue;
				splay(t);
				t->ch[0]->p = t->ch[1]->p = null;
				t->ch[0] = t->ch[1] = null;
				Evert(fim[x]); Evert(fim[y]);
				t->w = t; t->v = tmp;
				fim[x]->p = t; fim[y]->p = t;
			}
		}
		std::reverse(Ans.begin(), Ans.end()); foreach(it, Ans) printf("%d\n", *it);
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

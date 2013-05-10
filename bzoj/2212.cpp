//#define Debug
#include <cassert>
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>
namespace DATA {
	const int MAXN = 5000050;
	struct Node {
		Node *ch[2], *p; int c, size;
		inline bool dir(void) {return this == p->ch[1];}
		inline void SetC(Node *t, bool d) {
			t->p = this;
			ch[d] = t;
		}
		inline void Updata(void) {
			size = ch[0]->size + ch[1]->size + 1;
		}
	}Tnull, *null = &Tnull;

	Node POOL[MAXN], *sid = POOL;
	class Splay {public:
		Node *root;
		Splay():root(null){}
		inline void rotate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Updata();
		}
		inline void splay(Node *x, Node *G) {
			if (G == null) root = x;
			while (x->p != G)
				if (x->p->p == G) rotate(x);
				else if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
					else {rotate(x); rotate(x);}
			x->Updata();
		}
		inline int Rank(int x) {
			int ret = 0; Node *t = root, *p;
			while (t != null)
				if (x > t->c)
					ret += t->ch[0]->size + 1, p = t, t = t->ch[1];
				else
					p = t, t = t->ch[0];
			splay(p, null);
			return ret;
		}
		inline Node* Renew(int x) {
			Node *ret = sid++;
			ret->c = x;
			ret->ch[0] = ret->ch[1] = ret->p = null;
			ret->size = 1;
			return ret;
		}
		inline void Insert(Node* p, Node*& Now, int x) {
			if (Now == null) {
				Now = Renew(x);
				Now->p = p;
				splay(Now, null);
				return;
			}
			Now->size++;
			if (x < Now->c)
				Insert(Now, Now->ch[0], x);
			else
				Insert(Now, Now->ch[1], x);
		}
	};
}
namespace Solve {
	typedef long long Int64;
	typedef DATA::Splay II;
	typedef std::vector<int> VII;
	const int MAXN = 400050;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	Int64 Ans = 0;
	II P[MAXN >> 1], *dd = P;
	VII PP[MAXN >> 1], *sdd = PP;

	struct Node {
		Node *l, *r; int c;long long size;
		II *T; VII *Q;
		Node(){l = r = NULL; c = size = 0;}
		int Input(void) {
			 if (c = ScanInt()) return size = 1; else return size = (l = new Node)->Input() + (r = new Node)->Input();
		}
		void solve() {
			if (l == NULL) {
				T = dd++;
				T->Insert(DATA::null, T->root, c);
				Q = sdd++;
				Q->push_back(c);
				return;
			} else l->solve(), r->solve();
			if (l->size < r->size )std::swap(l, r);
			Int64 tmp = 0;
			for (VII::reverse_iterator it = r->Q->rbegin(); it != r->Q->rend(); it++) {
				tmp += l->T->Rank(*it);
			}
			for (VII::reverse_iterator it = r->Q->rbegin(); it != r->Q->rend(); it++) {
				l->T->Insert(DATA::null, l->T->root, *it);
				l->Q->push_back(*it);
			}
			Ans += std::min(tmp, (l->size * r->size - tmp));
			T = l->T;
			Q = l->Q;
		}
	}*root;

	int n;
	void solve(void) {
		n = ScanInt();
		(root = new Node)->Input();
		root->solve();
		std::cout <<Ans<<std::endl;
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("rot.in", "r", stdin);
		freopen("rot.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

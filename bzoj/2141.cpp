#include <map>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef std::map<int, int> MII;
	const int MAXN = 20010;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c));
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Node {
		Node* ch[2], *p; int v, size;
		inline bool dir(){return this == p->ch[1];}
		inline bool Set(Node* x, bool d) {ch[d] = x, x->p = this;}
		inline void Update(void) {size = ch[0]->size + ch[1]->size + 1;}
	}Tnull, *null = &Tnull;

	class TREE {public:
		Node *root;
		TREE(){root = null;}
		inline void rotate(Node* x) {
			Node* p = x->p; bool d = x->dir();
			p->p->Set(x, p->dir());
			p->Set(x->ch[!d], d);
			x->Set(p, !d);
			p->Update();
		}
		inline void Splay(Node* x, Node* G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) rotate(x); else {
					if (x->dir() == x->p->dir()) {
						rotate(x->p); rotate(x);
					}else {
						rotate(x); rotate(x);
					}
				}
			}
			x->Update();
		}
		inline Node* Renew(int v) {
			Node* t = new Node;
			t->ch[0] = t->ch[1] = t->p = null;
			t->size = 1, t->v = v;
			return t;
		}
		inline Node* Select(Node* now, int t) {
			if (now == null) return null;
			if (t <= now->v) return Select(now->ch[0], t);
			else {
				Node* ret = Select(now->ch[1], t);
				if (ret == null) return now; else return ret;
			}
		}
		inline Node* SelectMax(Node* now, int t) {
			if (now == null) return null;
			if (t >= now->v) return SelectMax(now->ch[1], t);
			else {
				Node* ret = SelectMax(now->ch[0], t);
				if (ret == null) return now; else return ret;
			}
		}
		inline int CalMax(int v) {
			Node* t = SelectMax(root, v);
			if (t == null) return 0; else {
				Splay(t, null);
				return t->ch[1]->size + 1;
			}
		}
		inline int Rank(int v) {
			Node* t = Select(root, v);
			if (t == null) return 0; else {
				Splay(t, null);
				return t->ch[0]->size + 1;
			}
		}
		inline void Insert(Node* p, Node*& now, int v) {
			if (now == null) {
				now = Renew(v);
				now->p = p;
				Splay(now, null);
				return;
			}
			now->size++;
			bool d = (v > now->v);
			Insert(now, now->ch[d], v);
		}

		inline Node* GetMin(Node* t) {if (t == null) return t;while (t->ch[0] != null) t = t->ch[0]; return t;}
		inline Node* GetMax(Node* t) {if (t == null) return t;while (t->ch[1] != null) t = t->ch[1]; return t;}
		inline Node* Succ(Node* t) {if (t == null) return null;Splay(t, null); return GetMin(t->ch[1]);}
		inline Node* Prev(Node* t) {if (t == null) return null;Splay(t, null); return GetMax(t->ch[0]);}

		inline void Delete(int v) {
			Node* t = Select(root, v);
			if (t == null) {
				t = GetMin(root);
				Splay(t, null);
				t->ch[1]->p = null; root = t->ch[1];
				return;
			}
			Node* now = Succ(t);
			Node* L = Prev(now), *R = Succ(now);
			Splay(now, null);
			if (L == null || R == null) {
				bool d = (R != null);
				root = now->ch[d], root->p = null;
				return;
			}
			Splay(L, root); Splay(R, root);
			L->Set(R, 1);
			L->Update(); L->p = null;
		}
	};

	class BIT {public:
		TREE a[MAXN]; int n;
		inline void Push(int v, int t) {
			for (;v<=n;v+=v&-v) {
				a[v].Insert(null, a[v].root, t);
			}
		}
		inline void Erase(int v, int t) {
			for (;v<=n;v+=v&-v) {
				a[v].Delete(t);
			}
		}
		inline int Cal(int v, int t) {
			int ret = 0;
			for (;v;v-=v&-v) {
				ret += a[v].Rank(t);
			}
			return ret;
		}
		inline int Sum(int l, int r, int t) {
			if (l > r) return 0;
			int L = Cal(l - 1, t);
			int R = Cal(r, t);
			return R - L;
		}
		inline int CalMax(int v, int t) {
			int ret = 0;
			for (;v;v-=v&-v) {
				ret += a[v].CalMax(t);
			}
			return ret;
		}
		inline int SumMax(int l, int r, int t) {
			if (l > r) return 0;
			int L = CalMax(l - 1, t);
			int R = CalMax(r, t);
			return R - L;
		}
	}T;

	int n, a[MAXN], Ans = 0, delta;

	void Input(void) {
		n = ScanInt(); T.n = n;
		for (int i = 1, tmp; i <= n; i++) {
			a[i] = tmp = ScanInt();
			T.Push(i, tmp);
			Ans += T.SumMax(1, i - 1, tmp);
		}
	}

	void Work(void) {
		int Q = ScanInt();
		for (int i = 1; i <= Q; i++) {
			printf("%d\n", Ans);
			int l = ScanInt(), r = ScanInt();
			if (l > r) std::swap(l, r);
			int dr = (T.Sum(l + 1, r - 1, a[r])) - (T.SumMax(l + 1, r - 1, a[r]));
			int dl = (T.SumMax(l + 1, r - 1, a[l]) - (T.Sum(l + 1, r - 1, a[l])));
			Ans += dr + dl;
			if (a[l] > a[r]) Ans--;
			if (a[l] < a[r]) Ans++;
			T.Erase(l, a[l]);
			T.Erase(r, a[r]);
			std::swap(a[l], a[r]);
			T.Push(l, a[l]);
			T.Push(r, a[r]);
		}
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

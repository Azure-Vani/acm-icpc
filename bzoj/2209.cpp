/*#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const int MAXN = 100020;
	
	struct Node {
		int l, r, p; bool rev, opt;
		int size, lc, rc, rlc, rrc;
		inline void reverse(void);
		inline void Opt(void);
	}S[MAXN]; int root, sid = 0;

	#define abs(x) ((x) < 0 ? 0 : (x))
	inline void Node::reverse(void) {
		rev ^= 1;
		std::swap(l, r);
		lc = S[l].lc + abs(S[r].lc - S[l].rc);
		rc = S[r].rc + abs(S[l].rc - S[r].lc);
		rlc = S[l].rlc + abs(S[r].rlc - S[l].rrc);
		rrc = S[r].rrc + abs(S[l].rrc - S[r].rlc);
	}
	inline void Node::Opt(void) {
		opt ^= 1;
		std::swap(lc, rlc);
		std::swap(rc, rrc);
	}
	class Tree {
		public:
		inline void Updata(int x) {
			int L = S[x].l, R = S[x].r;
			S[x].size = S[L].size + S[R].size + 1;
			if (S[L].rev) {
				S[L].reverse();
			}
			if (S[R].rev) {
				S[R].reverse();
			}
			if (S[L].opt) {
				S[L].Opt();
			}
			if (S[R].opt) {
				S[R].Opt();
			}
			S[x].lc = S[L].lc + abs(S[R].lc - S[L].rc);
			S[x].rc = S[R].rc + abs(S[L].rc - S[R].lc);
			S[x].rlc = S[L].rlc + abs(S[R].rlc - S[L].rrc);
			S[x].rrc = S[R].rrc + abs(S[L].rrc - S[R].rlc);
		}

		void LL(int x) {
			int R = S[x].r, F = S[x].p;
			S[x].r = S[R].l, S[S[x].l].p = x;
			S[R].l = x, S[x].p = R;
			S[R].p = F;
			if (x == S[F].l) S[F].l = R; else S[F].r = R;
			Updata(x);
		}
		void RR(int x) {
			int L = S[x].l, F = S[x].p;
			S[x].l = S[L].r, S[S[x].l].p = x;
			S[L].r = x, S[x].p = L;
			S[L].p = F;
			if (x == S[F].l) S[F].l = L; else S[F].r = L;
			Updata(x);
		}
		void Splay(int x, int G) {
			int F, FF;
			while ((F = S[x].p) != G)
				if ((FF = S[F].p) == G)
					if (x == S[F].l)
						RR(F);
					else
						LL(F);
				else
					if (x == S[F].l)
						if (F == S[FF].l)
							RR(FF), RR(F);
						else
							RR(F), LL(FF);
					else
						if (F == S[FF].r)
							LL(FF), LL(F);
						else
							LL(F), RR(FF);
			if (!G) root = x;
			Updata(x);
		}
		int Select(int k) {
			int t = root, L;
			while (S[L = S[t].l].size == k - 1)
				if (S[L].size <= t)
					t = L;
				else
					t = L, k -= S[L].size + 1;
			return t;
		}

		int Build(int l, int r, char* a) {
			if (l > r) return 0;
			if (l == r) {
				int t = ++sid;
				if (a[l] == '(')
					S[t].rc = 1, S[t].rlc = 1;
				if (a[l] == ')')
					S[t].lc = 1, S[r].rrc = 1;
				S[t].size = 1;
				return t;
			}
			int mid = (l + r) >> 1;
			int t = ++sid;
			S[ S[t].l = Build(l, mid, a) ].p = t;
			S[ S[t].r = Build(mid + 1, r, a) ].p = t;
			Updata(t);
			return t;
		}
		inline int Get(int l, int r) {
			Splay(l = Select(l - 1), 0);
			Splay(r = Select(r + 1), l);
			return S[r].l;
		}
		int Ask(int l, int r) {
			int t = Get(l + 1, r + 1);
			int Mid = (S[t].lc + S[t].rc) >> 1;
			printf("%d\n", S[t].size - abs(S[t].lc - Mid) - abs(S[t].rc - Mid));
		}
		void Reverse(int l, int r) {
			int t = Get(l + 1, r + 1);
			S[t].reverse();
		}
		void Opt(int l, int r) {
			int t = Get(l + 1, r + 1);
			S[t].Opt();
		}
	}T;

	int n, Q;
	void Input(void) {
		scanf("%d%d\n", &n, &Q);
		char s[MAXN] = {0};
		scanf("%s", s + 1);
		s[0] = s[n + 1] = '$';
		root = T.Build(1, n + 1, s);
	}
	void solve(void) {
		Input();
		for (int _ = 1; _ <= Q; _++) {
			int type, l, r;
			scanf("%d%d%d", &type, &l, &r);
			if (type == 0) {
				T.Ask(l, r);
			}else
			if (type == 1) {
				T.Reverse(l, r);
			}else
			if (type == 2) {
				T.Opt(l, r);
			}
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
*/
//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define abs(x) ((x) < 0 ? (-(x)) : (x))
namespace DataInfo {
	struct Info {
		int Lmax, Rmax, Lmin, Rmin;
		int sum;

		void Set(int value) {
			sum = value;
			Lmax = Rmax = std::max(0, value);
			Lmin = Rmin = std::min(0, value);
		}

		void Merge(const Info& L, const Info& R) {
			sum = L.sum + R.sum;
			Lmax = std::max(L.Lmax, L.sum + R.Lmax);
			Lmin = std::min(L.Lmin, L.sum + R.Lmin);
			Rmax = std::max(R.Rmax, R.sum + L.Rmax);
			Rmin = std::min(R.Rmin, R.sum + L.Rmin);
		}
		void Renew(int x) {
			Info copy, tmp;
			copy = *this;
			tmp.Set(x);
			Merge(copy, tmp);
		}
		void Renew(Info R) {
			Info copy;
			copy = *this;
			Merge(copy, R);
		}

		void ApplyRev(void) {
			std::swap(Lmax, Rmax);
			std::swap(Lmin, Rmin);
		}
		void ApplyOpt(void) {
			std::swap(Lmin, Lmax);
			Lmin *= -1, Lmax *= -1;
			std::swap(Rmin, Rmax);
			Rmin *= -1, Rmax *= -1;
			sum *= -1;
		}
		int Cost(void) {
			return ((abs(Lmin) + 1) >> 1) + ((Rmax + 1) >> 1);
		}
	};
}
namespace DataPoint {
	struct Node {
		Node* ch[2], *p;
		int size, value;

		DataInfo::Info info;

		bool isRev, isOpt;

		bool dir(void) {
			return this == p->ch[1];
		}
		inline void SetC(Node* now, bool d) {
			ch[d] = now;
			now->p = this;
		}

		void Updata(void) {
			size = ch[1]->size + ch[0]->size + 1;
			info = ch[0]->info;
			info.Renew(value);
			info.Renew(ch[1]->info);
		}

		Node() {
			size = 0;
			info.Set(0);
		}
		Node(int _value);

		void ApplyRev(void) {
			isRev ^= 1;
			info.ApplyRev();
		}
		void ApplyOpt(void) {
			isOpt ^= 1;
			value *= -1;
			info.ApplyOpt();
		}
		
		void Pass(void) {
			if (isRev) {
				std::swap(ch[0], ch[1]);
				ch[0]->ApplyRev();
				ch[1]->ApplyRev();
				isRev = false;
			}
			if (isOpt) {
				ch[0]->ApplyOpt();
				ch[1]->ApplyOpt();
				isOpt = false;
			}
		}
	}Tnull, *null = &Tnull;

	Node::Node(int _value) {
		ch[0] = ch[1] = null;
		isRev = isOpt = false;
		value = _value;
		info.Set(_value);
		size = 1;
	}
}
namespace DataOrg {
	#define Node DataPoint::Node
	#define null DataPoint::null
	struct SpalyTree {
		Node* root;

		inline void rotate(Node* x) {
			Node* p = x->p;
			bool d = x->dir();
			p->Pass();
			x->Pass();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Updata();
			if (p == root) root = x;
		}
		inline void Splay(Node* x , Node* G) {
			while (x->p != G) {
				if (x->p->p == G)
					rotate(x);
				else {
					if (x->dir() == x->p->dir())
						rotate(x->p), rotate(x);
					else
						rotate(x), rotate(x);
				}
			}
			x->Updata();
		}

		Node* Select(int k) {
			for (Node* t = root;;) {
				t->Pass();
				if (k == t->ch[0]->size)
					return t;
				if (k < t->ch[0]->size)
					t = t->ch[0];
				else
					k = k - t->ch[0]->size - 1, t = t->ch[1];
			}
		}

		Node* Get(int l, int r) {
			Node* L = Select(l - 1);
			Node* R = Select(r + 1);
			Splay(L, null);
			Splay(R, L);
			return R->ch[0];
		}

		Node* Build(int l, int r, int a[]) {
			if (l > r) return null;
			int mid = l + r >> 1;
			Node *t = new Node(a[mid]);
			t->SetC(Build(l, mid - 1, a), 0);
			t->SetC(Build(mid + 1, r, a), 1);
			t->Updata();
			return t;
		}
		
		void Init(int a[], int n) {
			root = Build(0, n + 1, a);
			root->p = null;
		}
	};
}
namespace Solve {
	const int MAXN = 100050;
	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	char ch[MAXN];
	int n, Q, seq[MAXN];

	DataOrg::SpalyTree T;

	void Input(void) {
		n = ScanInt(), Q = ScanInt();
		scanf("%s", ch + 1);
		ch[0] = ch[n + 1] = '|';
		for (int i = 1; i <= n; i++)
			seq[i] = ch[i] == '(' ? 1 : -1;
		T.Init(seq, n);
	}

	void Work(void) {
		for (int __ = 1; __ <= Q; __++) {
			int type = ScanInt(), l =ScanInt(), r = ScanInt();
			if (type == 0) {
				int ret = T.Get(l, r)->info.Cost();
				printf("%d\n", ret);
			}else
			if (type == 1) {
				T.Get(l, r)->ApplyOpt();
			}else
			if (type == 2) {
				T.Get(l, r)->ApplyRev();
			}
		}
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

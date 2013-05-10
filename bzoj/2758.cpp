//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#define NDEBUG

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>
#include <set>
#include <cmath>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Define {
	const int inf = ~0U>>1;
	struct Point {
		double x, y;
		Point(){}
		Point(double x, double y):x(x), y(y){}
	};

	typedef vector<Point> VP;

	//type: 0 => circle  1 => polygon
	//To save figures
	struct Figure {
		bool type;
		VP up, down; double x, y, r;
		int v;
		inline pair<double, double> ScanP(void) {
			int n; scanf("%d", &n); VP tmp;
			int xMax, xMin; double Max = -inf, Min = inf;
			for (int i = 1; i <= n; i++) {
				double x, y; scanf("%lf%lf", &x, &y);
				tmp.pb(Point(x, y));
				if (x > Max) {
					Max = x;
					xMax = tmp.size() - 1;
				}
				if (x < Min) {
					Min = x;
					xMin = tmp.size() - 1;
				}
			}
			if (xMax < xMin) {
				for (int it = xMin; it >= xMax; --it)
					down.pb(tmp[it]);
				for (int it = xMin; it != (int)tmp.size(); ++it)
					up.pb(tmp[it]);
				for (int it = 0; it <= xMax; ++it)
					up.pb(tmp[it]);
			} else {
				for (int it = xMin; it <= xMax; ++it)
					up.pb(tmp[it]);
				for (int it = xMin; it >= 0; --it)
					down.pb(tmp[it]);
				for (int it = (int)tmp.size() - 1; it >= xMax; --it)
					down.pb(tmp[it]);
			} /*
			fputs("Poly 1:\n", stderr);
			for (int i = 0; i <= (int)up.size() - 1; i++) fprintf(stderr, "%lf %lf\n", up[i].x, up[i].y);
			fputs("-----------\n", stderr);
			for (int i = 0; i <= (int)down.size() - 1; i++) fprintf(stderr, "%lf %lf\n", down[i].x, down[i].y);
			fputs("\n", stderr);*/
			scanf("%d", &v);
			return mp(Min, Max);
		}
		inline VP::iterator Binary(VP& a, double x_c) {
			int l = 0, r = a.size() - 1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (a[mid].x < x_c)
					l = mid + 1;
				else 
					r = mid - 1;
			}
			return a.begin() + r;
		}
		inline double intersect(const Point& L, const Point& R, double x_c) {
			assert(L.x < R.x);
			if (L.y == R.y) return L.y;
			if (L.y > R.y) {
				return R.y + (R.x - x_c) / (R.x - L.x) * (L.y - R.y);
			} else {
				return L.y + (x_c - L.x) / (R.x - L.x) * (R.y - L.y);
			}
		}
		inline double getInterval(double x_c, bool dir = 0) {
			if (type == 0) {
				if (fabs(x_c - (x - r)) <= 0.001 || fabs(x_c - (x + r)) <= 0.001) {
					return y;
				}
				double t = this->r * this->r - (x - x_c) * (x - x_c);
				double d = sqrt(t);
				if (dir == 0) return y - d; else return y + d;
			}
			if (x_c == up[0].x) {
				VP::iterator l = up.begin(), r = down.begin();
				while (l->x == x_c) l++; l--; assert(l != up.end() - 1);
				while (r->x == x_c) r++; r--; assert(r != down.end() - 1);
				if (dir == 0) return r->y; else return l->y;
			}
			if (x_c == up[up.size() - 1].x) {
				VP::iterator l = up.end() - 1, r = down.end() - 1;
				while (l->x == x_c) l--; l++; assert(l != up.begin());
				while (r->x == x_c) r--; r++; assert(r != down.begin());
				if (dir == 0) return r->y; else return l->y;
			}
			VP::iterator u = Binary(up, x_c);
			VP::iterator d = Binary(down, x_c);
			assert(x_c >= u->x && x_c <= (u + 1)->x);
			assert(x_c >= d->x && x_c <= (d + 1)->x);
			double l = intersect(*u, *(u + 1), x_c);
			double r = intersect(*d, *(d + 1), x_c);
			if (dir == 0) return r; else return l;
		}
	};

	/* splay tree
	 */
	struct Node {
		Node *ch[2], *p; Figure *v;
		inline bool dir(void) {return this == p->ch[1];}
		inline void SetC(Node *t, bool d) {ch[d] = t; t->p = this;}
	}Tnull, *null = &Tnull;
/*
	class SplayTree {public:
		Node *root; double x_c, y;
		SplayTree(){root = null;}
		inline void rotate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
		}
		inline void splay(Node *x, Node *G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) rotate(x); else {
					if (x->p->dir() == x->dir()) {rotate(x->p); rotate(x);}
					else {rotate(x); rotate(x);}
				}
			}
		}
		inline Node* Renew(Figure *x) {
			Node *ret = new Node; ret->p = ret->ch[0] = ret->ch[1] = null;
			ret->v = x;
			return ret;
		}
		inline void insert(Figure *x, Node *&now, Node *last) {
			if (now == null) {
				now = Renew(x); now->p = last;
				splay(now, null);
				return;
			}
			pair<double, double> tmp = now->v->getInterval(x_c);
			assert(tmp.first<tmp.second);
			if (y < tmp.first) {
				insert(x, now->ch[0], now);
			} else {
				insert(x, now->ch[1], now);
			}
		}
		inline void del(Node *x) {
			assert(x != NULL);
			if (x == null) return;
			splay(x, null);
			if (x->ch[0] == null || x->ch[1] == null) {
				int d = (x->ch[1] != null);
				root = x->ch[d]; root->p = null;
				return;
			}
			Node *L = x->ch[0], *R = x->ch[1];
			while (L->ch[1] != null) L = L->ch[1]; while (R->ch[0] != null) R = R->ch[0];
			splay(L, root); 
			splay(R, root);
			root = L; root->SetC(R, 1); root->p = null;
		}
		inline pair<Node*, Node*> Insert(Figure *x, double X, double Y) {
			x_c = X; y = Y;
			insert(x, root, null); Node* ret = root;
			if (root->ch[0] == null) return mp(ret, (Node*)NULL);
			Node *t = root->ch[0];
			while (t->ch[1] != null) t = t->ch[1];
			splay(t, null);
			pair<double, double> tmp = t->v->getInterval(x_c);
			assert(tmp.first<tmp.second);
			if (tmp.second > y) return mp(ret, t); else return mp(ret, (Node*)NULL);
		}
		inline Node* Find(Node *now) {
			if (now == null) return NULL;
			pair<double, double> tmp = now->v->getInterval(x_c);
			assert(tmp.first<tmp.second);
			//printf("%x %lf %lf %lf %lf\n", now, x_c, y, tmp.first, tmp.second);
			if (y > tmp.first) {
				Node *ret = Find(now->ch[1]);
				if (ret == NULL && tmp.second > y) return now; else return ret;
			} else {
				return Find(now->ch[0]);
			}
		}
		inline Node* Ask(double x, double y_c) {
			x_c = x, y = y_c;
			Node* ret = Find(root);
			if (ret) splay(ret, null);
			return ret;
		}
		inline void Put(Node *now) {
			if (now == null) return;
			fprintf(stderr, "now: %x  left: %x  right: %x  p: %x  %d\n", now, now->ch[0], now->ch[1], now->p, now->v->type);
			assert(now->ch[0]->p == now || now->ch[0] == null);
			assert(now->ch[1]->p == now || now->ch[1] == null);
			Put(now->ch[0]);
			Put(now->ch[1]);
		}
	};
*/
	//the points when sweep
	//contain the most left point and the most right point of a figure and the ask point
	struct SweepPoint {
		double x; int num, dir; //dir: 0 => left, 1 => right, 2 => ask point
	};
	
	//queries
	struct _ {
		int type, l, r; //type: 0 => modify, 1 => ask
	};
}

namespace Solve {
	const int MAXN = 600020;
	const double eps = 1e-6;


	Define::Figure G[MAXN];

	Define::SweepPoint Q[MAXN]; int cnt = 0;

	inline bool cmp(const Define::SweepPoint& a, const Define::SweepPoint& b) {
		if (fabs(a.x - b.x) <= eps) return a.dir < b.dir;
		return a.x < b.x;
	}

	Define::_ Query[MAXN];
	Define::Point P[MAXN]; int len = 0;

	int n, m, c[MAXN];
	bool Del[MAXN];

	inline void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++) {
			int c; while (!isalpha(c = getchar()));
			if (c == 'C') {
				G[i].type = 0;
				scanf("%lf%lf%lf%d", &G[i].x, &G[i].y, &G[i].r, &G[i].v);
				if (G[i].r <= 0) {Del[i] = true;continue;}
				G[i].up.pb(Define::Point(G[i].x - G[i].r, G[i].y));
				++cnt; Q[cnt].x = G[i].x - G[i].r; Q[cnt].num = i; Q[cnt].dir = 0;
				++cnt; Q[cnt].x = G[i].x + G[i].r; Q[cnt].num = i; Q[cnt].dir = 1;
			} else {
				G[i].type = 1;
				pair<double, double> tmp = G[i].ScanP();
				if (fabs(tmp.first - tmp.second) <= eps) {Del[i] = true;continue;}
			//	fprintf(stderr, "%lf %lf\n", tmp.first, tmp.second);
				++cnt; Q[cnt].x = tmp.first; Q[cnt].num = i; Q[cnt].dir = 0;
				++cnt; Q[cnt].x = tmp.second; Q[cnt].num = i; Q[cnt].dir = 1;
			}
		}
		for (int i = 1; i <= m; i++) {
			int c; while (!isalpha(c = getchar()));
			if (c == 'Q') {
				++len; scanf("%lf%lf", &P[len].x, &P[len].y);
				++len; scanf("%lf%lf", &P[len].x, &P[len].y);
				Query[i].type = 1; Query[i].l = len - 1, Query[i].r = len;
				++cnt; Q[cnt].x = P[len - 1].x; Q[cnt].num = len - 1; Q[cnt].dir = 2;
				++cnt; Q[cnt].x = P[len].x; Q[cnt].num = len; Q[cnt].dir = 2;
			} else {
				Query[i].type = 0;
				scanf("%d%d", &Query[i].l, &Query[i].r);
			}
		}
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*e[MAXN];
	inline void AddEdge(int x, int y) {
		e[x] = new Edge(y, e[x]);
	}
	int N;

	double x_c;

	struct Pair {
		int num, dir, belong;
		Pair(int num, int dir, int belong):num(num), dir(dir), belong(belong){}
		inline friend bool operator <(const Pair& a, const Pair& b) {
			if (a.num == b.num && a.dir != 2 && b.dir != 2) return a.dir < b.dir;
			double x = (a.dir == 2) ? (P[a.num].y) : G[a.num].getInterval(x_c, a.dir); 
			double y = (b.dir == 2) ? (P[b.num].y) : G[b.num].getInterval(x_c, b.dir); 
			return x < y;
		}
	};

/*	Define::SplayTree T;
	Define::Node* fim_fig[MAXN] = {0};
	*/

	set<Pair> T;
	set<Pair>::iterator L[MAXN], R[MAXN];

	inline void Sweep(void) {
		sort(Q + 1, Q + cnt + 1, cmp);
		N = n + len + 1;
		for (int i = 1; i <= cnt; i++) {
		//    fputs("----------------------\n", stderr);
		//	fprintf(stderr, "%lf %d %d\n", Q[i].x, Q[i].num, Q[i].dir);
		/*	if (Q[i].dir == 0) {
				pair<Define::Node*, Define::Node*> tmp = T.Insert(G + Q[i].num, Q[i].x, G[Q[i].num].up[0].y);
				fim_fig[Q[i].num] = tmp.first;
				if (tmp.second != NULL) {
					int t = tmp.second->v - G;
					AddEdge(t, Q[i].num);
				} else {
					AddEdge(N, Q[i].num);
				}
			}
			if (Q[i].dir == 1) {
				//cout <<Q[i].num<<endl;
				//fprintf(stderr, "%x\n", fim_fig[Q[i].num]);
				T.del(fim_fig[Q[i].num]);
			}
			if (Q[i].dir == 2) {
				double x = P[Q[i].num].x, y = P[Q[i].num].y;
				Define::Node* tmp = T.Ask(x, y);
				if (tmp != NULL) {
					int t = tmp->v - G;
					AddEdge(t, Q[i].num + n);
				} else {
					AddEdge(N, Q[i].num + n);
				}
			}
			//T.Put(T.root);*/
//			fprintf(stderr, "%d ", i); OK
			x_c = Q[i].x;
			if (Q[i].dir != 2 && Del[Q[i].num]) continue;
			if (Q[i].dir == 0) {
				pair<set<Pair>::iterator,bool> rr = T.insert(Pair(Q[i].num, 1, Q[i].num));
				assert(rr.second);
				set<Pair>::iterator r = rr.first; 
				R[Q[i].num] = r;
				r++;
				int t = (r == T.end()) ? N : r->belong;
				pair<set<Pair>::iterator,bool> ll = T.insert(Pair(Q[i].num, 0, t));
				assert(ll.second);
				set<Pair>::iterator l = ll.first;
				
				L[Q[i].num] = l;
				if (r == T.end()) {
					AddEdge(N, Q[i].num);
				} else {
					AddEdge(r->belong, Q[i].num);
				}
			}
			if (Q[i].dir == 1) {
				T.erase(L[Q[i].num]);
				T.erase(R[Q[i].num]);
			}
			if (Q[i].dir == 2) {
				Pair tmp = Pair(Q[i].num, 2, 0);
				set<Pair>::iterator it = T.lower_bound(tmp);
				if (it == T.end()) {
					AddEdge(N, Q[i].num + n);
				} else {
					AddEdge(it->belong, Q[i].num + n);
				}
			}
		}
	}

	int d[MAXN], belong[MAXN], deep[MAXN], sum[MAXN], father[MAXN];
	inline void Cut(void) {
		int head = 1, tail = 1; d[1] = N;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = e[now]; p; p = p->next) {
				deep[p->y] = deep[now] + 1;
				d[++tail] = p->y;
				father[p->y] = now;
			}
		}
		for (int i = N; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]];
		for (int t = 1; t <= N; t++) {
			int i = d[t];
			if (belong[i] == 0) belong[i] = i;
			int Max = 0, son = 0;
			for (Edge *p = e[i]; p; p = p->next) if (sum[p->y] > Max) {
				Max = sum[p->y];
				son = p->y;
			}
			belong[son] = belong[i];
		}
	}

	inline int LCA(int x, int y) {
		while (true) {
			if (deep[x] > deep[y]) swap(x, y);
			if (belong[x] == belong[y]) return x;
			if (deep[belong[x]] > deep[belong[y]])
				x = father[belong[x]];
			else
				y = father[belong[y]];
		}
	}

	int List[MAXN], Len = 0;
	pair<int, int> I[MAXN];

	inline int Dfs(int u) {
		int ret = 1;
		List[++Len] = u; I[u].first = Len;
		for (Edge *p = e[u]; p; p = p->next) {
			ret += Dfs(p->y);
		}
		List[++Len] = u; I[u].second = Len;
		return ret;
	}

	int C[MAXN], h[MAXN];

	inline void Add(int t, int x) {
		assert(t != 0);
		for (;t <= Len; t += t&-t) C[t] ^= x;
	}
	inline int Cal(int t) {
		int ret = 0;
		for (;t;t -= t&-t) ret ^= C[t];
		return ret;
	}

	inline void Work(void) {
		for (int i = 1; i <= n; i++) if (!Del[i]) {
			h[i] = G[i].v;
			Add(I[i].first, h[i]);
			Add(I[i].second, h[i]);
		}
		int last = 0, count = 0;
		for (int i = 1; i <= m; i++) {
//			fprintf(stderr, "%d %d\n", i, Query[i].type);
			if (Query[i].type == 0) {
				int t = Query[i].l, w = Query[i].r;
				if (Del[t]) continue;
				int d = h[t] ^ w; h[t] = w;
				Add(I[t].first, d);
				Add(I[t].second, d);
			} else {
				++count;
				int x = Query[i].l + n, y = Query[i].r + n;
				//int tmp = 0; for (int i = 1; i <= 21; i++) tmp ^= h[i]; fprintf(stderr, "%d\n", tmp);
				int L = Cal(I[x].first), R = Cal(I[y].first);
				int Ans = L ^ R;
				printf("%d\n", Ans ^ last);
				last ^= Ans;
			}
		}
	}

	inline void solve(void) {
		Input();
//		fputs("Input Done!!\n", stderr);
		Sweep();
//		fputs("Sweep Done!!\n", stderr);
		Dfs(N);
		//for (int i = 1; i <= L; i++) fprintf(stderr, "%d ", List[i]); fputs("", stderr);
//		fputs("Dfs Done!!\n", stderr);
		Cut();
		//for (int i = 1; i <= L; i++) fprintf(stderr, "%d ", belong[i]); fputs("", stderr);
//		fputs("Cut Done!!\n", stderr);
		Work();
//		fputs("Work Done!!\n", stderr);
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
//		freopen("log", "w", stderr);
	#endif
	Solve::solve();
	return 0;
}

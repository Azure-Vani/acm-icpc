//#define Debug
#include <cctype>
#include <algorithm>
#include <cstring>
#include <cstdio>
namespace Solve {
	const long MAXN = 100050;
	const long inf = 0x6eeeeeee;
	struct Node {
		long l, r, p;double x, y;
	}S[MAXN]; long root = 0, sid = 0;
	inline double Delta(double x1, double y1, double x2, double y2) {
		return x1 * y2 - x2 * y1;
	}
	inline double Cross(long x, long l1, long l2) {
		return Delta(S[l1].x - S[x].x, S[l1].y - S[x].y, S[l2].x - S[x].x, S[l2].y - S[x].y);
	}
	inline double Slope(long l1, long l2) {
		return (S[l1].y - S[l2].y) / (S[l1].x - S[l2].x);
	}
	inline void RR(long x) {
		long L = S[x].l, F = S[x].p;
		S[x].l = S[L].r, S[ S[x].l ].p = x;
		S[L].r = x, S[x].p = L;
		S[L].p = F;
		if (x == S[F].l) S[F].l = L; else S[F].r = L;
	}
	inline void LL(long x) {
		long R = S[x].r, F = S[x].p;
		S[x].r = S[R].l, S[ S[x].r ].p = x;
		S[R].l = x, S[x].p = R;
		S[R].p = F;
		if (x == S[F].l) S[F].l = R; else S[F].r = R;
	}
	inline void Splay(long x, long G) {
		long F, FF;
		while ((F = S[x].p) != G) 
			if ((FF = S[F].p) == G)
				if (x == S[F].l)
					RR(F);
				else
					LL(F);
			else
				if (F == S[FF].l)
					if (x == S[F].l)
						RR(FF), RR(F);
					else
						LL(F), RR(FF);
				else
					if (x == S[F].l)
						RR(F), LL(FF);
					else
						LL(FF), LL(F);
		if (!G) root = x;
	}
	inline long Succ(long t, long x) {
		if (S[x].r) {
			t = S[x].r;
			while (S[t].l) t = S[t].l;
			return t;
		}else {
			while (true) {
				if (S[x].p) {
					if (x == S[ S[x].p ].l)
						return S[x].p;
					x = S[x].p;
				}else return inf;
			}
		}
	}
	inline long Prev(long t, long x) {
		if (S[x].l) {
			t = S[x].l;
			while (true) {
				if (!S[t].r)
					return t;
				t = S[t].r;
			}
		}else {
			while (true) {
				if (S[x].p) {
					if (x == S[ S[x].p ].r)
						return S[x].p;
					x = S[x].p;
				}else
					return inf;
			}
		}
	}
	inline double Ask(double ai, double bi) {
		double k = -ai/bi;
		long t = root;
		while (true) {
			long l1 = Prev(root, t), l2 = Succ(root, t);
			double k1 = inf, k2 = -inf;
			if (l1 != inf) k1 = Slope(l1, t);
			if (l2 != inf) k2 = Slope(l2, t);
			if (k <= k1 && k >= k2) break;
			if (k2 > k) t = S[t].r;
				else if (k1 < k) t = S[t].l;
			}
			return ai * S[t].x + bi * S[t].y;
	}
	inline void Insert(long p, long t, double xi, double yi) {
		while (true) {
		if (!t) {
			t = ++sid;
			S[ sid ].x = xi, S[ sid ].y = yi, S[sid].p = p;
			if (xi < S[p].x) S[p].l = t; else S[p].r = t;
			Splay(t, 0);
			break;
		}
		if (xi < S[t].x)
			p = t, t = S[t].l;
		else
		if (xi > S[t].x)
			p = t, t = S[t].r;
		if (xi == S[t].x) {
			if (yi > S[t].y)
				S[t].y = yi;
			Splay(t, 0);
			break;
		}
		}
	}
	inline void Delete(long t) {
		long l1 = Prev(root, t), l2 = Succ(root, t);
		if (l1 != inf && l2 != inf) {
			Splay(l1, 0);
			Splay(l2, l1);
			S[l2].l = 0;
		}else
		if (l1 == inf && l2 != inf) {
			Splay(l2, 0);
			S[root].l = 0;
		}else
		if (l1 != inf && l2 == inf) {
			Splay(l1, 0);
			S[root].r = 0;
		}else
		root = 0;
	}
	inline void Adjust(long t) {
		long l1 = Succ(root, t);
		while (true) {
			if (l1 == inf) break;
			long l2 = Succ(root, l1);
			if (l2 == inf) break;
			if (Cross(t, l1, l2) >= 0)
				Delete(l1);
			else break;
			l1 = l2;
		}
		
		l1 = Prev(root, t);
		while (true) {
			if (l1 == inf) break;
			long l2 = Prev(root, l1);
			if (l2 == inf) {
				if (S[t].y > S[l1].y) {
					Delete(l1);
				}
				break;
			}
			if (Cross(l2, l1, t) >= 0 || S[t].y > S[l1].y)
				Delete(l1);
			else break;
			l1 = l2;
		}
	}
	inline void Add(double xi, double yi) {
		Insert(0, root, xi, yi);
		long temp = root;
		long l1 = Prev(root, temp), l2 = Succ(root, temp);
		if ( (l2 != inf) && ( ((l1 != inf) && Cross(l1, temp, l2) >= 0) || S[l2].y > S[temp].y)) {
			Delete(temp);
			return;
		}
		Adjust(temp);
	}
	double a[MAXN] = {0}, b[MAXN] = {0}, k[MAXN] = {0}, f[MAXN] = {0};
	double X[MAXN] = {0}, Y[MAXN] = {0};
	long n, s;
	#define Cal(i) (f[i] / (a[i] * k[i] + b[i]))
	inline double Read(void) {
		double r = 0;int c;
		while (c = getchar(), !isdigit(c)){}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		if (c == '.') {
			double l = 0.1;
			while (c = getchar(), isdigit(c)) r = r + l * (c - '0'), l /= 10.0;
		}
		return r;
	}
	void Work(void) {
		scanf("%ld %ld", &n, &s);
		for (long i = 1; i <= n; i++)
			a[i] = Read(), b[i] = Read(), k[i] = Read();
		f[1] = s;
		Y[1] = Cal(1);
		X[1] = Y[1] * k[1];
		Add(X[1], Y[1]);
		for (long i = 2; i <= n; i++) {
			double v = Ask(a[i], b[i]);
			f[i] = std::max(f[i - 1], v);

			Y[i] = Cal(i);
			X[i] = Y[i] * k[i];
			Add(X[i], Y[i]);
		}
		printf("%.3lf\n", f[n]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
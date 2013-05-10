#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Solve {
	const long MAXN = 500050;
	const long MAXNTREE = MAXN * 4;

	inline long Read(void) {
		long r = 0;int c;
		while (c = getchar(), !isdigit(c)){}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline char ReadChar(void) {
		char c;
		while(c = getchar(), !isalpha(c)){}
		if (c == 'C' && getchar() == 'S') c = 'L';
		return c;
	}


	struct Node {
		long l, r; long lc, rc, s, cover;
		long lx, rx;
		inline void Cover(long u) {
			cover = lc = rc = u;
			s = 1;
		}
	}S[MAXNTREE]; long sid = 0, root = 1;
	#define max(a,b) ((a)>(b)?(a):(b))
	#define min(a,b) ((a)<(b)?(a):(b))
	class SegmentTree {
		public:
			long Build(long l, long r, long* c) {
				if (l > r) return 0;
				long t = ++sid, mid = (l + r) >> 1;
				if (l == r) {
					S[t].lc = S[t].rc = c[l];
					S[t].s = 1;
					S[t].lx = S[t].rx = 0;
					S[t].l = S[t].r = l;
					return t;
				}
				S[t].lc = S[ S[t].lx = Build(l, mid, c) ].lc;
				S[t].rc = S[ S[t].rx = Build(mid + 1, r, c) ].rc;
				S[t].s = S[ S[t].lx ].s + S[ S[t].rx ].s - (S[ S[t].lx ].rc == S[ S[t].rx ].lc);
				S[t].l = l, S[t].r = r;
				return t;
			}
			inline void Updata(long x) {
				long L = S[x].lx, R = S[x].rx;
				S[x].lc = S[L].lc, S[x].rc = S[R].rc;
				S[x].s = S[L].s + S[R].s - (S[L].rc == S[R].lc);
			}
			inline void Pass(long x) {
				long u;
				if (u = S[x].cover) {
					S[ S[x].lx ].Cover(u);
					S[ S[x].rx ].Cover(u);
					S[x].cover = 0;
				}
			}
			void Cover(long t, long l, long r, long color) {
				if (l > r) return;
				Pass(t);
				if (l <= S[t].l && r >= S[t].r) {
					S[t].Cover(color);
					return;
				}
				long mid = (S[t].l + S[t].r) >> 1;
				Cover(S[t].lx, l, min(mid, r), color);
				Cover(S[t].rx, max(mid + 1, l), r, color);
				Updata(t);
			}
			void Make(long t, long k, long color) {
				Pass(t);
				if (S[t].l == S[t].r) {
					S[t].lc = S[t].rc = color;
					return;
				}
				long mid = (S[t].l + S[t].r) >> 1;
				if (k <= mid)
					Make(S[t].lx, k, color);
				else
					Make(S[t].rx, k, color);
				Updata(t);
			}
			long Find(long t, long k) {
				Pass(t);
				if (S[t].l == S[t].r)
					return S[t].lc;
				long mid = (S[t].l + S[t].r) >> 1;
				if (k <= mid)
					return Find(S[t].lx, k);
				else
					return Find(S[t].rx, k);
			}
			long Count(long t, long l, long r) {
				if (l > r) return 0;
				Pass(t);
				if (l <= S[t].l && S[t].r <= r) {
					return S[t].s;
				}
				long mid = (S[t].l + S[t].r) >> 1;
				long l1 = Count(S[t].lx, l, min(r, mid));
				long l2 = Count(S[t].rx, max(l, mid + 1), r);
				long res = l1 + l2;
				if (l1 && l2)
					res -= (S[ S[t].lx ].rc == S[ S[t].rx ].lc);
				return res;
			}
	}T;

	long C[MAXN] = {0}, n, c, delta = 0;
	bool reverse = false;
	inline void Adjust(long& l) {
		if (reverse)
			l = n - l + 2;
		l -= delta;
		if (l <= 0) l += n;
		else if (l > n) l -= n;
	}
	void Work(void) {
		n = Read(), c = Read();
		for (long i = 1; i <= n; i++)
			C[i] = Read();

		root = T.Build( 1, n, C);
		long Q = Read();
		for (long oo = 1; oo <= Q; oo++) {
			char flag = ReadChar();long l1, l2;
			if (flag == 'R') {
				l1 = Read();l1 %= n;
				if (!reverse)delta += l1;
				else delta -= l1;
				if (delta >= n) delta -= n;
				else if (delta < 0) delta +=n;
			}else
			if (flag == 'F') {
				reverse ^= 1;
			}else
			if (flag == 'S') {
				l1 = Read(), l2 = Read();
				Adjust(l1), Adjust(l2);
				if (reverse) 
					std::swap(l1, l2);
				long c1 = T.Find(root, l1), c2 = T.Find(root, l2);
				T.Make(root, l1, c2);
				T.Make(root, l2, c1);
			}else
			if (flag == 'P') {
				l1 = Read(), l2 = Read(); long color = Read();
				Adjust(l1); Adjust(l2);
				if (reverse)
					std::swap(l1, l2);
				if (l1 <= l2) {
					T.Cover(root, l1, l2, color);
				}else {
					T.Cover(root, l1, n, color);
					T.Cover(root, 1, l2, color);
				}
			}else
			if (flag == 'L') {
				l1 = Read(), l2 = Read();
				Adjust(l1); Adjust(l2);
				if (reverse)
					std::swap(l1, l2);
				if (l1 <= l2) {
					long A;
					A = T.Count(root, l1, l2);
					printf("%ld\n", A);
				}else {
					long A1, A2;
					A1 = T.Count(root, l1, n);
					A2 = T.Count(root, 1, l2);
					if (S[root].lc == S[root].rc) A1--;
					printf("%ld\n", A1 + A2);
				}
			}else
			if (flag == 'C') {
				long A;
				A = T.Count(root, 1, n);
				if (S[root].lc == S[root].rc && A != 1)
					A--;
				printf("%ld\n", A);
			}
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}

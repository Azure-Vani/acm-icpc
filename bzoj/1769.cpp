//#define Debug
#define XX
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cmath>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100020;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Point{
		Int64 x, y;
		inline Point operator -(const Point& oth) const {
			Point ret;
			ret.x = x - oth.x;
			ret.y = y - oth.y;
			return ret;
		}
		inline Point operator +(const Point& oth) const {
			Point ret;
			ret.x = x + oth.x;
			ret.y = y + oth.y;
			return ret;
		}
		inline Int64 operator *(const Point& oth) const {
			return x * oth.y - oth.x * y;
		}
	}a[MAXN];
	
	#define sqr(x) ((x)*(x))
	#define dis(a, b) (sqrt(sqr(a) + sqr(b)))
	inline bool cmp(const Point& a, const Point& b) {
		Int64 t = a * b;
		if (t != 0) return t > 0; else return dis(a.x, a.y) <= dis(b.x, b.y);
	}

	int n, m;
	void Input(void) {
		n = ScanInt(), m =ScanInt();
		for (int i = 1; i <= n; i++) {
			a[i].x = ScanInt(), a[i].y = ScanInt();
		}
	}

	typedef std::vector<Point> VII;
	#define max(a, b) ((a)>(b)?(a):(b))
	#define min(a, b) ((a)<(b)?(a):(b))
	Point A, B;

	struct Node {
		Node *ch[2]; int l, r;
		VII S;
/*
		inline void Cal(const Point& a, double& x, double& y) {
			double k;
			if (a.x != 0)
				k = (double) a.y / (double) a.x;
			else {
				y = (double) (A.y - B.y) / (double) (A.x - B.x) * A.x + A.y;
				x = 0;
				return;
			}
			x = (double) ((A.x - B.x) * A.y - (A.y - B.y) * A.x) / (double) (k * (A.x - B.x) - (A.y - B.y));
			y = k * x;
		}
		double Slope(const Point& a, const Point& b) {
			if (a.x == b.x) return -0x7fffffff;
			double t = (double) (a.y - b.y) / (double) (a.x - b.x);
			return t;
		}
*/
		inline double Cal(Point now) {
			Int64 t = (A - now) * (B - now);
			double d = sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
			return t / d;
		}

		inline bool Check(void) {
			double k = (double)(A.y - B.y) / (double)(A.x - B.x), tmp;
			int n = S.size() - 1;
			tmp = Cal(S[0]);
			if (tmp >= 0) return true;
			tmp = Cal(S[n]);
			if (tmp >= 0) return true;
			if (n <= 1) return false;
#ifdef XX
		/*	int L = 0, R = n;
			while (L <= R) {
				int mid = (L + R) >> 1; 
				double t1 = Slope(S[mid], S[mid - 1]), t2 = Slope(S[mid], S[mid + 1]);
				bool c1 = (t1 >= k), c2 = (t2 <= k || t2 >= 0);
				if (!c1&&c2) R = mid - 1;
				else if (c1&&!c2) L = mid + 1;
				else {
					Cal(S[mid], x, y);
					return dis(x, y) >= dis(S[mid].x, S[mid].y);
				}
			}*/
			int L = 0, R = n;
			while (L + 2 < R) {
				int delta = (R - L) / 3;
				int tmp1 = L + delta, tmp2 = R - delta;
				//double x1, y1, x2, y2;
				//Cal(S[tmp1], x1, y1); Cal(S[tmp2], x2, y2);
				//double t1 = dis(x1, y1) - dis(S[tmp1].x, S[tmp1].y), t2 = dis(x2, y2) - dis(S[tmp2].x, S[tmp2].y);
				double t1 = Cal(S[tmp1]), t2 = Cal(S[tmp2]);
				if (t1 >= 0 || t2 >= 0) return true;
				if (t1 > t2) R = tmp2; else L = tmp1;
			}
			for (int i = L; i <= R; i++) {
				double tmp = Cal(S[i]);
				if (tmp >= 0) return true;
			}
			return false;

#else
			double mx = -0x7fffffff, last = -0x7fffffff; int where;
			bool o = false;
			for (int i = 0; i <= n; i++) {
				if (i == 178) {
					i--, i++;
				}
				double tmp = Cal(S[i]);
				if (mx < tmp) mx = tmp, where = i;
				if (tmp > last) {
					i--, i++;
				}
				last = tmp;
			}
			return mx >= 0;
#endif
		}
		bool Ask(int L, int R) {
			if (L > R) return false;
			if (L <= l && r <= R) {
				return Check();
			}
			int mid = (l + r) >> 1;
			bool t1 = ch[0]->Ask(L, min(R, mid));
			if (t1) return true;
			bool t2 = ch[1]->Ask(max(L, mid + 1), R);
			return (t1 || t2);
		}
		inline void Make(int l, int r) {
			#define top S.size()
			for (int i = l; i <= r; i++) {
				while (top >= 2 && (a[i] - S[top - 1]) * (S[top - 2] - S[top - 1]) >= 0)
					S.pop_back();
				S.push_back(a[i]);
			}
			#undef top
		}
		void Build(int L, int R) {
			l = L, r = R;
			Make(L, R);
			if (l == r) return;
			int mid = (l + r) >> 1;
			(ch[0] = new Node)->Build(l, mid);
			(ch[1] = new Node)->Build(mid + 1, r);
		}
	}*root;
	
	inline int Binary(const Point& now, bool flag) {
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (cmp(a[mid], now))
				l = mid + 1;
			else
				r = mid - 1;
		}
		return flag ? r : l;
	}

	inline bool comp(const Point& a, const Point& b) {
		return a.x < b.x;
	}

	void Work(void) {
		std::sort(a + 1, a + n + 1, cmp);
		(root = new Node)->Build(1, n);
		for (int i = 1; i <= m; i++) {
			A.x = ScanInt(), A.y = ScanInt(), B.x = ScanInt(), B.y = ScanInt();
			if (cmp(B, A)) std::swap(A, B);
			int l = Binary(A, false);
			int r = Binary(B, true);
			bool ret = root->Ask(l, r);
			puts(ret?"Y":"N");
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
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

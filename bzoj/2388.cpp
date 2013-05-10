#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXQ = 333;
	const int MAXN = 100010 + MAXQ;
	const Int64 inf = 100000000000000ll;

	inline Int64 max(Int64 a, Int64 b) {return a > b ? a : b;}
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	
	int n, m;Int64 s[MAXN];
	inline void Input(void) {
		n = ScanInt();
		int nn = n;
		for (int i = 1; i <= n; i++) s[i] = s[i - 1] + ScanInt();
		if (n % MAXQ) nn = (n / MAXQ + 1) * MAXQ;
		for (int i = n + 1; i <= nn; i++) s[i] += s[i - 1];
		n = nn;
	}

	struct Point {
		Int64 x, y;
		inline bool operator <(const Point& oth) const {
			if (y != oth.y) return y < oth.y; else return x < oth.x;
		}
		inline bool operator ==(const Point& oth) const {
			return oth.x == x && oth.y == y;
		}
		inline Point operator -(const Point& oth) const {
			Point ret;
			ret.x = x - oth.x, ret.y = y - oth.y;
			return ret;
		}
		inline Int64 operator *(const Point& oth) const {
			return x * oth.y - y * oth.x;
		}
	}Base, stack[MAXN];
	
	int belong[MAXN], cnt;

	class Piece {public:
		Point a[MAXQ + 5]; int n, L; Int64 Answer, k, c[MAXQ + 3];
		inline void Add(Int64 d) {
			Answer = inf;
			k += d;
		}
		inline void Set(int l, int r) {
			Answer = inf; L = l, n = 0; int t = 1;
			for (int i = l; i <= r; i++, t++) {
				while (n >= 2 && (s[i] - a[n].y) * (a[n].x - a[n - 1].x) >= 
						(i - l + 1 - a[n].x) * (a[n].y - a[n - 1].y)) n--;
				a[++n].x = i - l + 1, a[n].y = s[i];
				c[t] = s[i];
			}
			a[0] = a[1], a[n + 1] = a[n];
			a[0].y = a[n + 1].y = -inf;
		}
		inline Int64 Ask(void) {
			if (Answer != inf) return Answer;
			k = -k;
			int l = 1, r = n;
			while (l <= r) {
				int mid = (l + r) >> 1;
				bool slopeL = (((Int64) (a[mid].y - a[mid - 1].y)) >= (Int64) k * (a[mid].x - a[mid - 1].x));
				bool slopeR = (((Int64) (a[mid + 1].y - a[mid].y)) <= (Int64) k * (a[mid + 1].x - a[mid].x));
				assert(slopeL || slopeR);
				if (slopeL && slopeR) {l = mid; break;}
				else if (!slopeR) l = mid + 1;
				else if (!slopeL) r = mid - 1;
			}
			k = -k;
			return a[l].y + a[l].x * k;
		}
		inline Int64 GetSum(int t = -1) {
			int l = t - L + 1; if (t == -1) l = MAXQ;
			return (Int64) l * k + c[l];
		}
	}a[MAXN / MAXQ + 5];

	inline void Prepare(void) {
		cnt = 1;
		int last = 1, lastsum = 0;
		for (int i = 1; i <= n; i++) {
			belong[i] = cnt;
			s[i] -= lastsum;
			if (i % MAXQ == 0) {
				a[cnt++].Set(last, i);
				last = i + 1;
				lastsum += s[i];
			}
		}
	}
	
	inline Int64 Cal(int l, int r) {
		Int64 Ans = -inf;
		if (belong[l] == belong[r]) {
			Int64 PreSum = 0;
			for (int i = 1; i < belong[l]; i++) 
				PreSum += a[i].GetSum();
			for (int i = l; i <= r; i++) 
				Ans = std::max(Ans, a[belong[l]].GetSum(i));
			return Ans + PreSum;
		}
		Int64 PreSum = 0;
		for (int i = 1; i < belong[l]; i++) PreSum += a[i].GetSum();
		if (belong[l] == belong[l - 1]) {
			int j;
			for (j = l; belong[j] == belong[l]; j++)
				Ans = std::max(Ans, PreSum + a[belong[l]].GetSum(j));
			PreSum += a[belong[l]].GetSum();
			l = j;
		}
		for (int i = belong[l]; i * MAXQ <= r; i++)
			Ans = std::max(Ans, a[i].Ask() + PreSum), PreSum += a[i].GetSum();
		if (belong[r] == belong[r + 1]) {
			int t = (belong[r] - 1) * MAXQ + 1;
			for (int j = t; j <= r; j++)
				Ans = std::max(Ans, a[belong[r]].GetSum(j) + PreSum);
		}
		return Ans;
	}

	#define Make(l) a[belong[l]].Set((belong[l] - 1) * MAXQ + 1, belong[l] * MAXQ)
	inline void Query(int l, int r, Int64 delta) {
		if (belong[l] == belong[r]) {
			for (int i = l; i <= r; i++)
				s[i] += (Int64) (i - l + 1) * delta;
			for (int i = r + 1; i <= belong[l] * MAXQ; i++)
				s[i] += (Int64) (r - l + 1) * delta;
			Make(l);
			return;
		}
		int i;
		if (belong[l] == belong[l - 1]) {
			for (i = l; belong[i] == belong[l]; i++)
				s[i] += (Int64) delta * (i - l + 1);
			Make(l);
			l = i;
		}
		if (belong[r] == belong[r + 1]) {
			int t = belong[r] * MAXQ - MAXQ + 1;
			for (i = t; i <= r; i++)
				s[i] += (Int64) delta * (i - t + 1);
			for (i = r + 1; i <= belong[r] * MAXQ; i++)
				s[i] += (Int64) delta * (r - t + 1);
			Make(r);
			r = t - 1;
		}
		for (int i = belong[l]; i <= belong[r]; i++) 
			a[i].Add(delta);
	}

	void Work(void) {
		int Q = ScanInt();
		for (int _ = 1; _ <= Q; _++) {
			int type = ScanInt();
			if (type == 0) {
				int l = ScanInt(), r = ScanInt(), delta = ScanInt();
				Query(l, r, delta);
			}else {
				int l = ScanInt(), r = ScanInt();
				printf("%lld\n", Cal(l, r));
			}
		}
	}

	void solve(void) {
		Input();
		Prepare();
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}

//#define Debug
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cctype>
namespace Solve {
	const int MAXN = 100005;
	const double eps = 1e-7;
	const double inf = 0x6eeeeeee;

	struct Circle {
		int x, y, r;
	}a[MAXN];

	inline int ScanInt(void) {
		int c, r = 0, d;
		while (d = getchar(), d != '-' && !isdigit(d)) {}
		if (d != '-') r = d - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return d == '-' ? -r : r;
	}

	int n;double l = inf, r = 0;
	void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) {
			a[i].x = ScanInt(), a[i].y = ScanInt(), a[i].r = ScanInt();
			l = std::min(l, double(a[i].x - a[i].r));
			r = std::max(r, double(a[i].x + a[i].r));
		}
	}

	struct pair {double l, r;int index;};
	pair c[MAXN]; int cnt;
	bool cmp(const pair& a, const pair& b) {return a.l < b.l;}

	#define pow(x) ((x)*(x))
	int Check(double now) {
		cnt = 0;
		bool L = 0, R = 0, OK = true;
		for (int i = 1; i <= n; i++) {
			if (a[i].x + a[i].r <= now) {L = true;if (R) break;continue;}
			if (a[i].x - a[i].r >= now) {R = true;if (L) break;continue;}
			double lc, rc;
			double Temp = sqrt(pow(a[i].r) - pow(now - a[i].x));
			lc = Temp + a[i].y;
			rc = a[i].y - Temp;
			if (lc > rc) std::swap(lc, rc);
			c[cnt].index = i, c[cnt].l = lc, c[cnt++].r = rc;
		}
		if (L && R) return 0;
		std::sort(c, c + cnt, cmp);

		double last = inf, l = c[0].l, r = c[0].r;
		for (int i = 1; i < cnt; i++) {
			if (c[i].l >= r) {OK = false; if (a[c[i].index].x >= now) R = true; else L = true; break;}
			l = std::max(l, c[i].l);
			r = std::min(r, c[i].r);
		}
		if (L && R) return 0;
		return L ? -1 : R ? 1 : OK ? 2 : 0;
	}

	void solve(void) {
		Input();
		while (l <= r) {
			double mid = (l + r) / 2.0;
			int flag = Check(mid);
			if (!flag) {puts("NO"); return;}
			if (flag == 2) {puts("YES"); return;}
			if (flag == -1)
				r = mid;
			else
				l = mid;
			if (r - l <= eps) break;
		}
		puts("NO");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;
#define mp make_pair
namespace Solve {
	const int MAXN = 100010;

	typedef pair<int, int> PII;

	inline int Round(double s) {
		if (s >= 0) {
			if (fabs(0.5 - (s - (int)s)) <= 1e-5) return (int)s;
			else return (int)(s + 0.5);
		}else return -Round(0.0 - s);
	}

	struct Point {
		int x, y;
	}a[3], b[3], c[3], d[3];
	vector<pair<PII, PII> > T;

	inline Point Rot (const Point& a, double _sin, double _cos) {
		Point ret;
		ret.x = Round(a.x * _cos - a.y * _sin);
		ret.y = Round(a.x * _sin + a.y * _cos);
		return ret;
	}

	bool multi = false;

	inline bool Make(int a, int b, int& ax, bool X = true) {
		int La, Lb; 
		if (X) La = c[a].x - c[b].x, Lb = d[a].x - d[b].x; else La = c[a].y - c[b].y, Lb = d[a].y - d[b].y;
		if (La != 0 && Lb != 0) {
			if (abs(Lb) % abs(La) != 0) return false;
			if (ax == 0) {
				ax = Lb / La;
			} else {
				if (ax != Lb / La) return false;
			}
			return true;
		} else {
			if (La != 0 || Lb != 0) return false; else return true;
		}
		assert(false);
	}

	inline void Cal(int p1, int p2, int p3, int Rx, int Ry) {
		double _sin = (double)Ry / sqrt(Rx * Rx + Ry * Ry);
		double _cos = (double)Rx / sqrt(Rx * Rx + Ry * Ry);
		
		for (int i = 0; i < 3; i++) c[i] = Rot(a[i], _sin, _cos);
		d[0] = b[p1], d[1] = b[p2], d[2] = b[p3];
		int ax = 0, ay = 0;
		if (!Make(0, 1, ax)) return;
		if (!Make(1, 2, ax)) return;
		if (!Make(2, 0, ax)) return;
		if (!Make(0, 1, ay, false)) return;
		if (!Make(1, 2, ay, false)) return;
		if (!Make(2, 0, ay, false)) return;

		if (ax == 0 || ay == 0) multi = true;
		T.push_back(mp(mp(ax, ay), mp(Rx, Ry)));
	}

	inline void Gao(int p1, int p2, int p3) {
		for (int x = -9; x <= 9; x++) {
			Cal(p1, p2, p3, x, -10);
			Cal(p1, p2, p3, x, 10);
		}
		for (int y = -10; y <= 10; y++) {
			Cal(p1, p2, p3, -10, y);
			Cal(p1, p2, p3, 10, y);
		}
	}

	inline bool Fuck(PII a, PII b) {
		return a.first + b.first == 0 && a.second + b.second == 0;
	}

	bool used[MAXN];

	inline void solve(void) {
		int Tcase = 0;
		while (true) {
			T.clear(); multi = false; memset(used, 0, sizeof used);
			bool end = true;
			for (int i = 0; i < 3; i++) scanf("%d%d", &a[i].x, &a[i].y), end &= (a[i].x == 0 && a[i].y == 0);
			if (end) break;
			for (int i = 0; i < 3; i++) scanf("%d%d", &b[i].x, &b[i].y);
			printf("Case %d: ", ++Tcase);
			Gao(0, 1, 2);
			Gao(0, 2, 1);
			Gao(1, 0, 2);
			Gao(1, 2, 0);
			Gao(2, 1, 0);
			Gao(2, 0, 1);
			if (T.size() == 0) {puts("no solution"); continue;}
			int Ans = 0;
			for (int i = 0; i < (int)T.size(); ++i) if (!used[i]) {
				Ans++;
				for (int j = i + 1; j < (int)T.size(); ++j) {
					assert(T[i] != T[j]);
					if (Fuck(T[i].first, T[j].first) && Fuck(T[i].second, T[j].second)) used[j] = true;
				}			
			}
			if (Ans == 1 && !multi) puts("equivalent solutions"); else puts("inconsistent solutions");
		}
	}
}
int main(void) {
	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

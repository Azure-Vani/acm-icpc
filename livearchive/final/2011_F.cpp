#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <set>
using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 100010;

	int N, C, D;

	struct _{
		Int64 D, P, R, G;
	}a[MAXN];
	inline bool cmp(const _& a, const _& b) {
		return a.D < b.D;
	}

	struct Point {
		Int64 x, y;
		inline friend bool operator <(const Point& a, const Point& b) {
			if (a.x == b.x) return a.y > b.y; else return a.x < b.x;
		}
		Point(Int64 x, Int64 y):x(x), y(y){}
	};

	template <class T> T Next(T a) {return ++a;}
	template <class T> T Prev(T a) {return --a;}
	set<Point> S;
	Int64 f[MAXN];

	inline void solve(void) {
		int Tcase = 0;
		while (scanf("%d%d%d", &N, &C, &D) && !(N == 0 && C == 0 && D == 0)) {
			Tcase++; S.clear(); memset(a, 0, sizeof a);
			memset(f, 0, sizeof f);
			for (int i = 1; i <= N; i++) scanf(LL LL LL LL, &a[i].D, &a[i].P, &a[i].R, &a[i].G);
			sort(a + 1, a + N + 1, cmp); a[0].R = C; a[N + 1].D = D + 1;
			S.insert(Point(0, C));
			for (int i = 1; i <= N + 1; i++) {
				/* force 
				for (int j = 0; j < i; j++) if (f[j] >= a[j].P) {
					f[i] = max(f[i], f[j] - a[j].P + (a[i].D - a[j].D - 1) * a[j].G + a[j].R);
				}
				*/
				Int64 k = -a[i].D;
				set<Point>::iterator it = S.begin();
				while (S.size() >= 2) {
					set<Point>::iterator next = Next(it);
					if ((next->y - it->y) >= k * (next->x - it->x)) {
						S.erase(it);
						it = S.begin();
					} else break;
				}
				f[i] = S.begin()->x * -k + S.begin()->y; if (i == N + 1) break;
				if (f[i] < a[i].P) continue;
				Int64 x = a[i].G, y = -a[i].D * a[i].G - a[i].G + f[i] - a[i].P + a[i].R;
				pair<set<Point>::iterator, bool> t = S.insert(Point(x, y)); it = t.first;
				if (S.size() >= 3 && Next(it) != S.end() && it != S.begin()) {
					set<Point>::iterator prev = Prev(it), next = Next(it);
					if ((next->x - it->x) * (prev->y - it->y) - (next->y - it->y) * (prev->x - it->x) >= 0) {
						S.erase(it);
						continue;
					}
				}
				while (it != S.begin() && Prev(it) != S.begin()) {
					set<Point>::iterator p = Prev(it), pp = Prev(p);
					if ((it->x - p->x) * (pp->y - p->y) - (it->y - p->y) * (pp->x - p->x) >= 0) {
						S.erase(p);
					} else break;
				}
				while (Next(it) != S.end() && Next(Next(it)) != S.end()) {
					set<Point>::iterator p = Next(it), pp = Next(p);
					if ((it->x - p->x) * (pp->y - p->y) - (it->y - p->y) * (pp->x - p->x) <= 0) {
						S.erase(p);
					} else break;
				}
			}
			printf("Case %d: "LL "\n", Tcase, f[N + 1]);
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

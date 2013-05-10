//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1010;
	const double eps = 1e-7;

	struct Point {
		int x, y, z;
		inline void Trans(void) {std::swap(x, y); std::swap(z, y);}
	}a[MAXN]; int n;

	inline void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
	}

	struct Double {
		double a;
		Double(double x = 0):a(x){}
		bool operator ==(const Double& oth) const {
			return fabs(a - oth.a) < eps;
		}
		bool operator <(const Double& oth) const {
			return a - oth.a < -eps;
		}
	};

	struct Line {
		int flag1;
		pair<Double, Double> p1; Double kx, ky;
		Point a, b;
		bool operator <(const Line& oth) const {
			if (flag1 != oth.flag1) return flag1 < oth.flag1;
				if (p1 != oth.p1)
					return p1 < oth.p1;
				else
					return mp(kx,ky) < mp(oth.kx, oth.ky);
		}
		Line(Point aa, Point bb) {
			this->a = aa, this->b = bb;
			double x = aa.x - bb.x, y = aa.y - bb.y, z = aa.z - bb.z;
			if (z == 0) {
				flag1 = 0;
				p1.first = Double(aa.z);
				if (x == 0) {
					p1.second = Double(1000000000);
					kx = Double(aa.x);
				} else {
					p1.second = Double(y / x);
					double k = (double)bb.x / (-x);
					kx = Double(bb.y + k * y);
				}
				ky = 0;
			} else {
				flag1 = 1;
				double k = (double) bb.z / (-z); 
				p1 = mp(Double(bb.x + k * x), Double(bb.y + k * y));
				kx = Double(x / z), ky = Double(y / z);
			}
		}
	};

	map<Line, int> H;

	inline void Work(void) {
		for (int i = 1; i <= n; i++) 
			for (int j = i + 1; j <= n; j++) {
				Line now(a[i], a[j]);
				H[now]++;
			}
		int ret = 0;
		foreach(it, H) if (it->second > 1)
			ret++;
		printf("%d\n", ret);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
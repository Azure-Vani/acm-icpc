#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <map>
#include <string>
#include <iostream>
#include <cctype>
#include <cstring>
#include <set>
#include <queue>
#include <deque>
#include <list>

#define PI 3.1415926

using namespace std;

typedef vector<int> VII;
typedef long long Int64;
typedef map<double, int> MII;
typedef set<double> SII;

	const int MAXN = 55;

	struct Point {
		double x, y;
		inline void Set(int x, int y){this->x = (double)x, this->y = (double)y;}
		inline friend double operator ^(const Point& a, const Point& b) {
			if (a.x == b.x) return a.x;
			return a.x - a.y * (b.x - a.x) / (b.y - a.y);
		}
	}a[MAXN];

	int n = 0;
	vector<double> S_tmp;
	
	inline int MainWork(double X) {
		double Angle = 0;
		for (int i = 1; i < n; i++) {if (a[i + 1]. y == a[i].y && a[i].y == 0 && X >= min(a[i + 1].x, a[i].x) && X <= std::max(a[i + 1].x, a[i].x)) return 0;
			double tmp = atan2(a[i + 1].y, a[i + 1].x - X) - atan2(a[i].y, a[i].x - X);
			if (tmp > PI) tmp -= 2 * PI;
			if (tmp < -PI) tmp += 2 * PI;
			Angle += tmp;
		}
		printf("%.4lf\n", Angle);
		return (int)(Angle / 2.0 / PI + 0.5);
	}

	class AllWoundUp { public:
		int maxWind(VII x, VII y) {
			for (VII::iterator it_x = x.begin(), it_y = y.begin(); it_x != x.end(); it_x++, it_y++)
				a[++n].Set(*it_x, *it_y);
			a[n + 1] = a[1];
			for (int i = 1; i <= n; i++) if (a[i].y * a[i + 1].y <= 0 && (a[i].x != a[i + 1].x || a[i].y != a[i + 1].y)) {
				if (a[i].y || a[i + 1].y)
					S_tmp.push_back(a[i] ^ a[i + 1]);
				else S_tmp.push_back(a[i].x), S_tmp.push_back(a[i + 1].x);
			}
			sort(S_tmp.begin(), S_tmp.end());
			int Ans = 0, N = S_tmp.size();
			for (int i = 0; i < N - 1; i++) {
				if (fabs(S_tmp[i] - S_tmp[i + 1]) > 1e-5)
					Ans = max(Ans, MainWork((S_tmp[i] + S_tmp[i + 1]) / 2.0));
			}
			return Ans;
		}
	};

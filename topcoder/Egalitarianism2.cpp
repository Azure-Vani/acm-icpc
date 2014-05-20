#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <cmath>

using namespace std;

const int MAXN = 10000;

struct Edge {
	int x, y; double z, back;
}c[MAXN], CC[MAXN]; int top;

inline double dis(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

inline bool cmp(const Edge& x, const Edge& y) {
	return x.z < y.z;
}

int f[MAXN], n; vector<double> res;

inline int find(int x) {return x == f[x] ? x : (f[x] = find(f[x]));}

class Egalitarianism2 {
	public:
	double get(const vector<double>& a) {
		double tmp = 0;
		for (int i = 0; i < a.size(); i++) {
			tmp += a[i];
		}
		tmp /= a.size();
		double ret = 0;
		for (int i = 0; i < a.size(); i++) {
			ret += (a[i] - tmp) * (a[i] - tmp);
		}
		return sqrt(ret / a.size());
	}

	inline double Make(double tmp) {
		for (int i = 1; i <= top; i++) c[i].z = (CC[i].z - tmp) * (CC[i].z - tmp), c[i].back = CC[i].z;
		sort(c + 1, c + top + 1, cmp);
		for (int j = 0; j < n; j++) f[j] = j;
		res.clear();
		for (int j = 1; j <= top; j++) {
			if (find(c[j].x) != find(c[j].y)) {
				res.push_back(c[j].back);
				f[find(c[j].x)] = c[j].y;
			}
		}
		return get(res);
	}

	double Cal(long double l, long double r) {
		for (int i = 1; i <= 50; i++) {
			long double L = l + (r - l) / 3.0, R = l + (r - l) / 3.0 * 2;
			double t1 = Make(L);
			double t2 = Make(R);
			if (t1 < t2) r = R; else l = L;
		}
		return Make(l);
	}

	double minStdev(vector <int> x, vector <int> y) {
		n = x.size();
		for (int i = 0; i < x.size(); i++)
			for (int j = i + 1; j < x.size(); j++) {
				c[++top].z = dis(x[i], y[i], x[j], y[j]);
				c[top].x = i;
				c[top].y = j;
				CC[top] = c[top];
			}
		sort(CC + 1, CC + top + 1, cmp);
		double Ans = 100000000000.0;
		for (int i = 1; i < top; i++) {
			double tmp = Cal(CC[i].z, CC[i + 1].z);
			printf("%lf %lf %lf\n", CC[i].z, CC[i + 1].z, tmp);
			Ans = min(Ans, tmp);
		}
		return Ans;
	}
};

vector<int> X, Y;

int main(void) {
	Egalitarianism2 now;
	X.push_back(12);
	X.push_back(46);
	X.push_back(81);
	X.push_back(56);
	Y.push_back(0);
	Y.push_back(45);
	Y.push_back(2);
	Y.push_back(67);
	double tmp = now.minStdev(X, Y);
	printf("%lf\n", tmp);
	return 0;
}

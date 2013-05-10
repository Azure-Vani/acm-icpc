// BEGIN CUT HERE

// END CUT HERE

#define OJ

#include <vector> 
#include <list> 
#include <map> 
#include <set> 
#include <deque> 
#include <queue> 
#include <stack> 
#include <bitset> 
#include <algorithm> 
#include <functional> 
#include <numeric> 
#include <utility> 
#include <sstream> 
#include <iostream> 
#include <iomanip> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <cctype> 
#include <string> 
#include <cstring> 
#include <cstdio> 
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)
#define dis(a, b) (sqrt(sqr(a.x - b.x) + sqr(a.y - b.y)))

typedef long long Int64;

using namespace std; 

const int MAXN = 53;
const double inf = 10000000000000.0;

int n;
double P[MAXN][MAXN], f[MAXN];
bool vis[MAXN];

struct Point {
	double x, y;
	Point(){}
	Point(double x, double y):x(x), y(y){}
	Point operator -(const Point& oth) const {
		return Point(x - oth.x, y - oth.y);
	}
	Point operator +(const Point& oth) const {
		return Point(x + oth.x, y + oth.y);
	}
	double operator *(const Point& oth) const {
		return x * oth.x + y * oth.y;
	}
}a[MAXN], b[MAXN], Goal;

int d[30000];
class BasketballStrategy { public:
	double ML(const Point& a, const Point& b, const Point& c) {
		if ((c - a) * (b - a) < 0 || (c - b) * (a - b) < 0) return inf;
		double A = dis(b, c), B = dis(a, c), C = dis(a, b), p = (A + B + C) / 2.0;
		double ret = sqrt(p * (p - A) * (p - B) * (p - C));
		return ret * 2 / C;
	}
	double Get(const Point& L, const Point& R) {
		double ret = inf;
		for (int i = 0; i < n; i++) {
			ret = std::min(ret, ML(L, R, b[i]));
		}
		return ret;
	}
	double scoreProbability(vector <string> team, vector <string> rivals, double Cp, double Cs) {
		n = team.size(), Goal = Point(50, 0);
		for (int i = 0; i <= n - 1; i++) {
			stringstream sin(team[i]);
			sin >>a[i].x>>a[i].y;
		}
		for (int i = 0; i <= n - 1; i++) {
			stringstream sin(rivals[i]);
			sin >>b[i].x>>b[i].y;
		}
		for (int i = 0; i <= n - 1; i++) {
			for (int j = i + 1; j <= n - 1; j++) {
				double dr = Get(a[i], a[j]), ls = dis(a[i], a[j]);
				P[i][j] = P[j][i] = Cp * (1 - sqr(ls / 150)) * dr / (dr + 1);
			}
			double dr = Get(a[i], Goal), ls = dis(a[i], Goal);
			P[n][i] = pow((Cs * dr / (dr + 1)), log(ls));
		}
		rep(i, 0, n) f[i] = -1; f[n] = 1;
		int head = 1, tail = 1; d[1] = n; vis[n] = true;
		while (head <= tail) {
			int now = d[head++];
			for (int i = 0; i < n; i++) {
				if (f[i] < f[now] * P[now][i]) {
					f[i] = f[now] * P[now][i];
					if (!vis[i]) {
						d[++tail] = i;
						vis[i] = false;
					}
				}
			}
			vis[now] = false;
		}
		return f[0];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"50 50","35 60","70 15"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"75 5","72 25","45 17"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1; double Arg3 = 1; double Arg4 = 0.6100612919616956; verify_case(0, Arg4, scoreProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"50 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"50 5"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.99; double Arg3 = 0.5; double Arg4 = 0.3825461314703953; verify_case(1, Arg4, scoreProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"50 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"50 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.5; double Arg3 = 0.5; double Arg4 = 0.0; verify_case(2, Arg4, scoreProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"50 50","40 50","40 40","40 30","50 20"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"50 41","44 29","48 27","45 41","48 64"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.999999; double Arg3 = 0.8; double Arg4 = 0.25546407305110735; verify_case(3, Arg4, scoreProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { string Arr0[] = {"50 50","50 25"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"40 40","60 20"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1; double Arg3 = 0.7; double Arg4 = 0.20631213370921644; verify_case(4, Arg4, scoreProbability(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	BasketballStrategy ___test;  
 	___test.run_test(4); 
	return 0;
}
// END CUT HERE

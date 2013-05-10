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

#define mk make_pair
#define pb push_back
#define rep(i,r) for(int i = 0; i < r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define eps 0.000001

template <class T> T Dec(T a, T b) {return (a - b) < 0 ? (b - a) : (a - b);}

const int inf = 2047483647;

typedef long long Int64;

using namespace std; 

int V = 0, E = 0;

struct Point {
double x, y;
	Point(double x, double y):x(x),y(y){}
	inline bool friend operator <(const Point& a, const Point& b) {
		if (Dec(a.x ,b.x) <= eps) return a.y < b.y;else 
		return a.x < b.x;
	}
};
vector<Point> C;
struct Line {
	int x1, y1, x2, y2;
	inline double Slope(void) const {
		if (x1 == x2) return inf;
		else return (double) (y2 - y1) / (double) (x2 - x1);
	}
}a[60];

class PlaneDivision { public:
	int n; vector<double> Vol[60];
	inline double Get(Line a, Line b, bool flag) {
		double a1 = a.y2 - a.y1, b1 = a.x2 - a.x1, c1 = a1 * a.x1 - b1 * a.y1;
		double a2 = b.y2 - b.y1, b2 = b.x2 - b.x1, c2 = a2 * b.x1 - b2 * b.y1;
		double y = (c1 * a2 - c2 * a1) / (b2 * a1 - b1 * a2), x = a1 ? (c1 + b1 * y) / a1 : (c2 + b2 * y) / a2;
		C.pb(Point(x, y));
		return flag ? y : x;
	}

	int howManyFiniteParts(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) {
		n = x1.size();
		V = 0, E = 0;
		if (n <= 2) return 0;
		rep(i, n) a[i].x1 = x1[i], a[i].y1 = y1[i], a[i].x2 = x2[i], a[i].y2 = y2[i];
		rep(i, n) {
			rep(j, n) if (i != j) {
				double k1 = a[i].Slope(), k2 = a[j].Slope();
				if (Dec(k1, k2) <= eps) continue;
				Vol[i].pb(Get(a[i], a[j], k1 == inf));
			}
			std::sort(Vol[i].begin(), Vol[i].end());
			int Len = Vol[i].size(), tmp = 1;
			rep(j,Len - 1) if (Dec(Vol[i][j], Vol[i][j + 1]) > eps) tmp++;
			E += tmp - 1;
		}
		std::sort(C.begin(), C.end());
		V = 1;
		rep(i, (int)C.size() - 1) if (!(Dec(C[i].x, C[i + 1].x) <= eps && Dec(C[i].y, C[i + 1].y) <= eps)) V++;
		return E - V + 1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(0, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, -1, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {-10000, -9999, 10000, -9999, 0, 500, -500}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-9999, 10000, 9999, -10000, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {-10000, 9999, 10000, 9999, 0, 500, -500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {9999, 10000, -9999, -10000, 1, -1, -2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 4; verify_case(2, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(3, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {-1, -1, -1, -1, 1, 3, -3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, -2, 0, 0, 10000, 1, -5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1, 1, -1, 1, -3, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 0, 2, -10000, 0, -2, 4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 7; verify_case(4, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {-100, -100, -100, -100, -100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100, -99, -98, -97, -96}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100, 100, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {99, 100, 101, 102, 103}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(5, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = {-100, -100, -100, -100, -100, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100, -99, -98, -97, -96, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100, 100, 100, -2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {99, 100, 101, 102, 103, 2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(6, Arg4, howManyFiniteParts(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	PlaneDivision ___test;  
 	___test.run_test(6); 
	return 0;
}
// END CUT HERE

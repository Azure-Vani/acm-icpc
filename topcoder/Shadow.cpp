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
#include <iterator>
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

typedef long long Int64;

using namespace std; 

typedef pair<double, double> pt;
vector<pt> V;

class Shadow {
	public:
	double X(const pt& a, const pt& c, const pt& b) {
		return (a.first - c.first) * (b.second - c.second) - (a.second - c.second) * (b.first - c.first);
	}
	double Hull(vector<pt> a) {
		int n = a.size(); if (n <= 2) return 0.0;
		vector<pt> up, down;
		std::sort(a.begin(), a.end());
		pt p1 = a[0], p2 = a.back(); up.pb(a[0]); down.pb(a[0]);
		for (int i = 1; i <= n - 1; i++) {
			if (i == n - 1 || X(p1, a[i], p2) > 0) {
				while (up.size() >= 2 && X(up[up.size() - 2], up[up.size() - 1], a[i]) <= 0)
					up.pop_back();
				up.pb(a[i]);
			}
			if (i == n - 1 || X(p1, a[i], p2) < 0) {
				while (down.size() >= 2 && X(down[down.size() - 2], down[down.size() - 1], a[i]) >= 0)
					down.pop_back();
				down.pb(a[i]);
			}
		}
		a.clear();
		foreach(it, up) a.pb(*it);
		for (int i = down.size() - 2; i > 0; --i) a.pb(down[i]); if (a.size() <= 2) return 0.0; a.pb(a[0]);
		double ret = 0;
		for (int i = 0; i < (int)a.size() - 1; i++) ret += X(a[i], mp(0.0, 0.0), a[i + 1]);
		return fabs(ret) * 0.5;
	}
	double area(vector <int> tree, vector <int> light) {
		if (light[1] <= std::min(tree[1], tree[4])) return 0.0;
		if (light[1] <= std::max(tree[1], tree[4])) {
			if ((tree[0] == tree[3] && tree[2] == tree[5]) ||
			    (tree[0] == tree[3] && light[0] == tree[0]) ||
			    (tree[2] == tree[5] && light[2] == tree[2])) return 0.0;
			return -1.0;
		}
		double lx = light[0], ly = light[1], lz = light[2];
		for (int s = 0; s <= 7; s++) {
			double x = (s&1)?tree[0]:tree[3];
			double y = (s&2)?tree[1]:tree[4];
			double z = (s&4)?tree[2]:tree[5];
			double rx = (ly / (ly - y)) * (x - lx) + lx;
			double rz = (ly / (ly - y)) * (z - lz) + lz;
			V.pb(mp(rx, rz));
		}
		return Hull(V);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,1,1, 10,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,5,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(0, Arg2, area(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,3,1, 10,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = -1.0; verify_case(1, Arg2, area(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {5, 5, 5, 5, 7, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 6, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(2, Arg2, area(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] =  {1,1,1, 3,3,3} ; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = -1.0; verify_case(3, Arg2, area(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	Shadow ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

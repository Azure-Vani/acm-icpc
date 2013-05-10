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

typedef long long Int64;

using namespace std; 

const int inf = 1000000000;

struct Point {
	int x, y;
}a[250010];

class Manhattan {
	public:
	int dis(Point a, Point b) {
		return abs(a.x - b.x) + abs(a.y - b.y);
	}
	vector <int> furthestPair(int n, int c, int b, int m) {
		c %= m, b %= m;
		a[1].x = 0, a[1].y = b;
		for (int i = 2; i <= n; i++) {
			a[i].x = ((Int64) a[i - 1].y * c % m + b) % m;
			a[i].y = ((Int64) a[i].x * c % m + b) % m;
		}
		int min1 = inf, max1 = -inf, pos_min1 = 0, pos_max1 = 0, min2 = min1, max2 = max1, pos_min2 = 0, pos_max2 = 0;
		for (int i = 1; i <= n; i++) {
			if (min1 > a[i].x + a[i].y) {
				min1 = a[i].x + a[i].y;
				pos_min1 = i;
			}
			if (max1 < a[i].x + a[i].y) {
				max1 = a[i].x + a[i].y;
				pos_max1 = i;
			}
			if (min2 > a[i].x - a[i].y) {
				min2 = a[i].x - a[i].y;
				pos_min2 = i;
			}
			if (max2 < a[i].x - a[i].y) {
				max2 = a[i].x - a[i].y;
				pos_max2 = i;
			}
		}
		if (pos_min1 > pos_max1) swap(pos_min1, pos_max1);
		if (pos_min2 > pos_max2) swap(pos_min2, pos_max2);
		vector<int> ret1, ret2; ret1.pb(pos_min1 - 1); ret1.pb(pos_max1 - 1); ret2.pb(pos_min2 - 1); ret2.pb(pos_max2 - 1);
		if (ret1[0] == ret1[1]) ret1[1] = 1;
		if (ret2[0] == ret2[1]) ret2[1] = 1;
		int t1 = dis(a[pos_min1], a[pos_max1]), t2 = dis(a[pos_min2], a[pos_max2]);
		if (t1 > t2 || (t1 == t2 && ret1 < ret2)) return ret1; else return ret2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 250000; int Arg1 = 999999998; int Arg2 = 999999997; int Arg3 = 999999999; int Arr4[] = {0, 1 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(0, Arg4, furthestPair(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 17; int Arg2 = 17; int Arg3 = 17; int Arr4[] = {0, 1 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(1, Arg4, furthestPair(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 912; int Arg2 = 1023; int Arg3 = 103871; int Arr4[] = {0, 54 }; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); verify_case(2, Arg4, furthestPair(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	Manhattan ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

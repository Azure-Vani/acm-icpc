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

const int MAXN = 55;

struct rect {
	Int64 x1, y1, x2, y2;
} a[MAXN];
Int64 S, X[MAXN], Y[MAXN], W, H, Tmp = 0; int n;

class StrawberryFieldsOnFire {
	public:
	void Init(Int64 L) {
		Tmp = 0;
		for (int i = 1; i <= n; i++) {
			a[i].x1 = std::max(1ll, X[i] - L);
			a[i].y1 = std::max(1ll, Y[i] - L);
			a[i].x2 = std::min(W, X[i] + L);
			a[i].y2 = std::min(H, Y[i] + L);
		}
	}

	void Cal(int k, Int64 x1, Int64 y1, Int64 x2, Int64 y2) {
		if (x1 > x2 || y1 > y2) return;
		while (k <= n && (a[k].x1 > x2 || a[k].x2 < x1 || a[k].y1 > y2 || a[k].y2 < y1)) ++k;
		if (k > n) {
			Tmp += (x2 - x1 + 1ll) * (y2 - y1 + 1ll);
			return;
		}
		if (a[k].x1 >= x1) {
			Cal(k + 1, x1, y1, a[k].x1 - 1, y2);
			x1 = a[k].x1;
		}
		if (a[k].x2 <= x2) {
			Cal(k + 1, a[k].x2 + 1, y1, x2, y2);
			x2 = a[k].x2;
		}
		if (a[k].y1 >= y1) {
			Cal(k + 1, x1, y1, x2, a[k].y1 - 1);
			y1 = a[k].y1;
		}
		if (a[k].y2 <= y2) {
			Cal(k + 1, x1, a[k].y2 + 1, x2, y2);
			y2 = a[k].y2;
		}
	}

	int timeLimit(int w, int h, string need, vector <string> fire) {
		W = w, H = h;
		n = fire.size(); stringstream sin(need); sin >>S; S = (Int64) ((Int64) W * (Int64) H) - S;
		for (int i = 0; i <= n - 1; i++) {
			sin.clear(); sin.str(fire[i]);
			sin >>X[i + 1]>>Y[i + 1];
		}
		Int64 l = 0, r = 1000000000;
		while (l <= r) {
			Int64 mid = (l + r) >> 1;
			Init(mid);
			for (int i = 1; i <= n; i++) 
				Cal(i + 1, a[i].x1, a[i].y1, a[i].x2, a[i].y2);
			if (Tmp > S) {
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		return r;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 998098080; int Arg1 = 999998083; string Arg2 = "8066849"; string Arr3[] = {"99980980 1243", "141 524521", "555555 555555", "998098080 235234", "21 999998083"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 998098053; verify_case(0, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 5; string Arg2 = "1"; string Arr3[] = {"1 4","2 2"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 2; verify_case(1, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 5; string Arg2 = "13"; string Arr3[] = {"1 4","2 2"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000000000; int Arg1 = 1; string Arg2 = "1"; string Arr3[] = {"1 1"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 999999998; verify_case(3, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 101; int Arg1 = 101; string Arg2 = "400"; string Arr3[] = {"51 51"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 49; verify_case(4, Arg4, timeLimit(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	StrawberryFieldsOnFire ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

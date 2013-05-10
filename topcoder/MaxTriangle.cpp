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
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)
#define round(x) ((int) (x) + 0.5)

typedef long long Int64;

using namespace std; 

class MaxTriangle {
	public:
	
	bool issqr(int x) {
		int t = round(sqrt(x));
		return t * t == x;
	}

	double calculateArea(int A, int B) {
		int a = -1, b = -1;
		for (int i = 0; i <= A; i++) {
			if (issqr(i) && issqr(A - i)) {
				a = i;
				break;
			}
		}
		for (int i = 0; i <= B; i++) {
			if (issqr(i) && issqr(B - i)) {
				b = i;
				break;
			}
		}
		if (a == -1 || b == -1) return -1;
		double x1 = sqrt(A - a), y1 = sqrt(a), x2 = sqrt(b), y2 = sqrt(B - b);
		double A1 = fabs(x1 * y2 - x2 * y1) / 2.0;
		x2 = -x2;
		double A2 = fabs(x1 * y2 - x2 * y1) / 2.0;
		x2 = -x2, y1 = -y1;
		double A3 = fabs(x1 * y2 - x2 * y1) / 2.0;
		return max(A1, max(A2, A3));
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; double Arg2 = 0.5; verify_case(0, Arg2, calculateArea(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 7; double Arg2 = -1.0; verify_case(1, Arg2, calculateArea(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 41; int Arg1 = 85; double Arg2 = 29.5; verify_case(2, Arg2, calculateArea(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	MaxTriangle ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

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

typedef long long Int64;

using namespace std; 

class AlternateColors2 {
	public:
	long long rest(int n) {
		long long ret = 0;
		for (int i = 0; i <= n; i++)
			ret += n - i + 1;
		return ret;
	}
	long long countWays(int n, int k) {
		long long ret = 0;
		/*if (k == 1) {
			return rest(n - 1);
		}*/
		if ((k - 1) % 3 == 0) {
			ret += rest(n - k);
		}
		if (k != n) for (int i = 0; i * 3 + 2 < k; i++) if ((k - i * 3) & 1) {
			long long now = 0;
			now += n - k;
			now *= 2;
			ret += now;
		}
		for (int i = 0; i * 3 < k - 1; i++) {
			int l2 = k - i * 3 - 1;
			long long now = l2 / 2 + 1;
			ret += (now - 1) * 2 + 1;
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; long long Arg2 = 1LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 3LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 4; long long Arg2 = 9LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; long long Arg2 = 21LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000; int Arg1 = 3; long long Arg2 = 1LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 99999; int Arg1 = 2009; long long Arg2 = 1666700000LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	AlternateColors2 ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

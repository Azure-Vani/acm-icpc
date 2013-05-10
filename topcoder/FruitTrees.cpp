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
#define rep(i,r) for(int i = 1; i <= r; i++)
#define REP(i,l,r) for(inti = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

class FruitTrees {
	public:
	inline int gcd(int a, int b) {return !b?a:gcd(b, a % b);}
	
	inline int get(int a, int b, int d) {
		if (d < 0) d = -d;
		int t = gcd(a, b);
		int u = d / t;
		return min(abs(t * u - d), abs((u + 1) * t - d));
	}

	int maxDist(int apple, int kiwi, int grape) {
		int n = max(apple, max(kiwi, grape));
		int Ans = 0;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++) {
				int t1 = get(apple, kiwi, i);
				int t2 = get(apple, grape, j);
				int t3 = get(kiwi, grape, i - j);
				Ans = max(Ans, min(t1, min(t2, t3)));
			}
		return Ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 5; int Arg2 = 8; int Arg3 = 0; verify_case(0, Arg3, maxDist(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 6; int Arg3 = 1; verify_case(1, Arg3, maxDist(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 40; int Arg1 = 30; int Arg2 = 20; int Arg3 = 5; verify_case(2, Arg3, maxDist(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 899; int Arg1 = 1073; int Arg2 = 1147; int Arg3 = 14; verify_case(3, Arg3, maxDist(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1500; int Arg1 = 2000; int Arg2 = 2000; int Arg3 = 666; verify_case(4, Arg3, maxDist(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	FruitTrees ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

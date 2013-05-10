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

map<pair<Int64, int>, Int64> f;
long long n;

class NewMoneySystem {
	public:
	Int64 Cal(Int64 n, int k) {
		pair<int, int> now = mp(n, k);
		if (f.count(now)) return f[now];
		Int64 &ret = f[now]; ret = 1ll << 62;
		if (k == 1) return ret = n;
		for (int i = 2; i <= 5; i++) {
			ret = std::min(ret, n % i + Cal(n / i, k - 1));
		}
		return ret;
	}

	long long chooseBanknotes(string N, int K) {
		f.clear();
		stringstream sin(N); sin >>n;
		return Cal(n, K);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "1025"; int Arg1 = 6; long long Arg2 = 2LL; verify_case(0, Arg2, chooseBanknotes(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "1005"; int Arg1 = 5; long long Arg2 = 3LL; verify_case(1, Arg2, chooseBanknotes(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "12000"; int Arg1 = 14; long long Arg2 = 1LL; verify_case(2, Arg2, chooseBanknotes(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "924323565426323626"; int Arg1 = 1; long long Arg2 = 924323565426323626LL; verify_case(3, Arg2, chooseBanknotes(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "924323565426323626"; int Arg1 = 50; long long Arg2 = 10LL; verify_case(4, Arg2, chooseBanknotes(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	NewMoneySystem ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

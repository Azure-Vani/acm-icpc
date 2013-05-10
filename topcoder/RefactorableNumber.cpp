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

const int MAXN = 2000010;

bool tag[MAXN];
int prime[MAXN], cnt = 0, fac[MAXN];

class RefactorableNumber {
	public:
	void Product(int n) {
		for (int i = 2; i <= n; i++) {
			if (!tag[i]) prime[++cnt] = i, fac[i] = i;
			for (int j = 1; j <= cnt && prime[j] * i <= n; j++) {
				tag[prime[j] * i] = true;
				fac[prime[j] * i] = prime[j];
				if (i % prime[j] == 0) break;
			}
		}
	}

	inline int Cal(int u) {
		int ret = 1;
		while (u > 1) {
			register int t = 1, p = fac[u];
			while (u % p == 0) u /= p, t++;
			ret *= t;
		}
		return ret;
	}

	int count(int low, int high) {
		Product(high);
		int ret = 0;
		for (int i = low; i <= high; i++) {
			if (i % Cal(i) == 0) ret++;
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 10; int Arg2 = 4; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 100; int Arg2 = 12; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 25; int Arg1 = 35; int Arg2 = 0; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123; int Arg1 = 4567; int Arg2 = 315; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RefactorableNumber ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

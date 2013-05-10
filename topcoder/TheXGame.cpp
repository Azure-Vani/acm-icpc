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
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899

typedef long long Int64;

using namespace std; 

class TheXGame {
	public:

	vector<int> a;

	int firstMove(string board) {
		a.clear();
		board += 'X';
		for (int i = 0, last = 0; i <= (int)board.length(); i++) {
			if (board[i] == 'X') {
				if (last) {
					a.pb(last);
					last = 0;
				}
			} else last++;
		}
		int n = a.size(), limit = 0, sg = 0, sum = 0;
		for (int i = 0; i <= n - 1; i++) {
			limit = std::max(limit, a[i]);
			sg ^= a[i];
			sum += a[i];
		}
		if (sum <= 2) return -1;
		for (int t = 1; t <= limit; t++) {
			for (int i = 0; i <= n - 1; i++) if (a[i] >= t) {
				for (int j = 0; j <= a[i] - t; j++)  {
					if (!(sg ^ a[i] ^ j ^ (a[i] - t - j)))
						return t;
				}
			}
		}
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "X---X-X-"; int Arg1 = 1; verify_case(0, Arg1, firstMove(Arg0)); }
	void test_case_1() { string Arg0 = "----"; int Arg1 = 2; verify_case(1, Arg1, firstMove(Arg0)); }
	void test_case_2() { string Arg0 = "--XXX" ; int Arg1 = -1; verify_case(2, Arg1, firstMove(Arg0)); }
	void test_case_3() { string Arg0 = "--------X-----X----X"; int Arg1 = 3; verify_case(3, Arg1, firstMove(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	TheXGame ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

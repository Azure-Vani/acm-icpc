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

class PalindromeEncoding {
	public:
	int getLength(string s) {
		while (s.length() > 1 && s[0] == s[1]) s.erase(0, 1);
		if (s.length() == 1) return 1;
		int pos = -1;
		for (int i = 0; i + 1 < s.length(); i++) if (s[i] == s[i + 1]) {
			pos = i + 1;
			break;
		}
		return pos == -1?s.length():pos;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "0111001"; int Arg1 = 2; verify_case(0, Arg1, getLength(Arg0)); }
	void test_case_1() { string Arg0 = "0"; int Arg1 = 1; verify_case(1, Arg1, getLength(Arg0)); }
	void test_case_2() { string Arg0 = "01010111100110101110000001011000101000010111000111"; int Arg1 = 6; verify_case(2, Arg1, getLength(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	PalindromeEncoding ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

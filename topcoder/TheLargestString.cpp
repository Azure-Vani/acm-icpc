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
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

class TheLargestString {
	public:
		string Add(string st, char a, char b) {
			int n =st.length();
			return st.substr(0, n / 2) + a + st.substr(n / 2, n / 2) + b;
		}

	string find(string s, string t) {
		string f[55][55];
		int n = s.length();
		rep(i, n) rep(j, n) {
			REP(k, 0, i - 1) {
				f[i][j] = max(f[i][j], Add(f[k][j - 1], s[i - 1], t[i - 1]));
			}
		}
		string ret;
		rep(i,n) rep(k, n) ret = max(ret, f[i][k]);
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ba"; string Arg1 = "zy"; string Arg2 = "by"; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "abacaba"; string Arg1 = "zzzaaaa"; string Arg2 = "cbaaaa"; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "cbc"; string Arg1 = "cba"; string Arg2 = "xx"; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "abbabbacbabacaaaabbababab"; string Arg1 = "babcbbacbbbababbbbababaab"; string Arg2 = "bbbbbbbbbbbbbbbbbbaaab"; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	TheLargestString ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

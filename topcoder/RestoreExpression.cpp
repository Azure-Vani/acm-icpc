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

class RestoreExpression {
	public:
	string a, b, c;
	string A, B, C;
	int f[100][100];

	bool can(string a, int i, int d) {
		if (i >= (int)a.length() && d) return false;
		if (i == (int)a.length() - 1 && d == 0 && (int)a.size() > 1) return false;
		if (i < (int)a.length() && a[i] != '?' && a[i] != d + '0') return false;
		return true;
	}

	int Cal(int pos, int d) {
		if (pos >= (int)a.length() && pos >= (int)b.length() && pos >= (int)c.length()) {
			if (d == 0) return true; else return false;
		}
		int &ret = f[pos][d];
		if (ret != -1) return ret;
		for (int da = 0; da <= 9; da++) if (can(a, pos, da)) {
			for (int db = 0; db <= 9; db++) if (can(b, pos, db)) {
				int now = (da + db + d) % 10;
				int next = (da + db + d) / 10;
				if (!can(c, pos, now)) continue;
				if (Cal(pos + 1, next)) return ret = 1;
			}
		}
		return ret = 0;
	}

	bool Check(string A, string B, string C) {
		memset(f, -1, sizeof f);
		a = A, b = B, c = C;
		reverse(a.begin(), a.end());
		reverse(b.begin(), b.end());
		reverse(c.begin(), c.end());
		return Cal(0, 0);
	}

	void Gao(string& a) {
		 for (int i = 0; i <= (int)a.length() - 1; i++) if (a[i] == '?') {
			for (int d = 9; d >= 0; d--) {
				a[i] = d + '0';
				if (Check(A, B, C)) break;
			}
		}
	}
	string restore(string expression) {
		for (int i = 0; i <= (int)expression.length() - 1; i++) if (expression[i] == '=' || expression[i] == '+') expression[i] = ' ';
		stringstream sin(expression); sin >>A>>B>>C;
		if (!Check(A, B, C)) return string("no solution");
		Gao(C); Gao(A); Gao(B);
		return A + "+" + B + "=" + C;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "?2345??891234567+1?34??6891234567=2469???78246???4"; string Arg1 = "1234599891234567+1234996891234567=2469596782469134"; verify_case(0, Arg1, restore(Arg0)); }
	void test_case_1() { string Arg0 = "?+?=4"; string Arg1 = "4+0=4"; verify_case(1, Arg1, restore(Arg0)); }
	void test_case_2() { string Arg0 = "?2+?2=4"; string Arg1 = "no solution"; verify_case(2, Arg1, restore(Arg0)); }
	void test_case_3() { string Arg0 = "??+1=1?"; string Arg1 = "18+1=19"; verify_case(3, Arg1, restore(Arg0)); }
	void test_case_4() { string Arg0 = "???+?=???0"; string Arg1 = "999+1=1000"; verify_case(4, Arg1, restore(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RestoreExpression ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

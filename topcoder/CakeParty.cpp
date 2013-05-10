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

vector<int> a;

class CakeParty {
	public:
	string digit(int a) {
		stringstream st;
		st <<a;
		return st.str();
	}
	int Trans(string s) {
		stringstream sin(s);
		int r; sin >>r;
		return r;
	}
	int I(int l, int r) {
		string L = digit(l), R = digit(r);
		if (L.length() == R.length()) return l;
		string ret = "1"; for (int i = 1; i <= (int)L.length(); i++) ret += "0";
		return Trans(std::min(ret, L));
	}
	string R(int a, int b) {
		char ch[100] = {};
		sprintf(ch, "CAKE %d PIECES %d", a, b);
		return string(ch);
	}
	string makeMove(vector <int> pieces) {
		int pos = 99, max1 = 0, sg1 = 0, sg2 = 0, n = pieces.size(), max2 = 0;
		if (n == 1) return R(0, pieces[0]);
		a = pieces; sort(a.begin(), a.end()); max1 = a.back(); a.pop_back(); max2 = a.back();
		for (int i = 0; i <= n - 1; i++) {
			if (pieces[i] == max1) {
				sg1++;
				pos = Trans(std::min(digit(i), digit(pos)));
			}
			if (pieces[i] == max2) sg2++;
		}
		if (!(sg1&1)) return R(pos, 1);
		if (sg1 != 1) return R(pos, 1);
		if (sg2&1) return R(pos, max1 - max2); else return R(pos, I(max1 - max2 + 1, max1));
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 47"; verify_case(0, Arg1, makeMove(Arg0)); }
	void test_case_1() { int Arr0[] = {3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(1, Arg1, makeMove(Arg0)); }
	void test_case_2() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 1 PIECES 2"; verify_case(2, Arg1, makeMove(Arg0)); }
	void test_case_3() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(3, Arg1, makeMove(Arg0)); }
	void test_case_4() { int Arr0[] = {3,3,112}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 2 PIECES 110"; verify_case(4, Arg1, makeMove(Arg0)); }
	void test_case_5() { int Arr0[] = {3,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 0 PIECES 1"; verify_case(5, Arg1, makeMove(Arg0)); }
	void test_case_6() { int Arr0[] = {4,7,4,7,4,7,4,7,47,47,47,47}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CAKE 10 PIECES 1"; verify_case(6, Arg1, makeMove(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	CakeParty ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

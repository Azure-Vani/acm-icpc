// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulCoins.cpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

class ColorfulCoins {
	public:
		long long a[100]; int top;

		inline int check(int t) {
			for (int i = 1; i <= top; i++) {
				long double tmp = pow(a[i] + 1, t);
				if (tmp - 1 < i - 1e-8) return false;
			}
			return true;
		}
	int minQueries(vector<long long> values) {
		top = 0;
		for (int i = 1; i < (int)values.size(); i++) a[++top] = values[i] / values[i - 1] - 1;
		sort(a + 1, a + top + 1);
		int Ans = 1;
		while (!check(Ans)) Ans++;
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {1}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minQueries(Arg0)); }
	void test_case_1() { long Arr0[] = {1, 3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minQueries(Arg0)); }
	void test_case_2() { long Arr0[] = {1, 2, 576460752303423492}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, minQueries(Arg0)); }
	void test_case_3() { long Arr0[] = {1, 2, 4, 8, 16}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minQueries(Arg0)); }
	void test_case_4() { long Arr0[] = {1, 2, 6, 30, 90, 270, 810, 2430, 7290, 29160, 87480, 262440, 787320, 3149280,
  9447840, 28343520, 56687040, 170061120, 510183360, 1530550080, 3061100160,
  9183300480, 27549901440, 82649704320, 247949112960, 1239745564800, 3719236694400,
  14876946777600, 44630840332800, 223154201664000, 669462604992000, 2008387814976000,
  6025163444928000, 12050326889856000, 24100653779712000, 72301961339136000,
  289207845356544000, 867623536069632000}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, minQueries(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE

int main(){
	ColorfulCoins ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

// BEGIN CUT HERE

// END CUT HERE
#line 5 "MyLongCake.cpp"
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

int stack[100000], top;
class MyLongCake {
	public:
	int cut(int n) {
		top = 0; int Ans = 0;
		for (int i = 2; i * i <= n; i++) if (n % i == 0) {
			stack[++top] = i;
			stack[++top] = n / i;
		}
		stack[++top] = n;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= top; j++) if (i % stack[j] == 0) {
				Ans++;
				break;
			}
		}
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; verify_case(0, Arg1, cut(Arg0)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; verify_case(1, Arg1, cut(Arg0)); }
	void test_case_2() { int Arg0 = 16; int Arg1 = 7; verify_case(2, Arg1, cut(Arg0)); }
	void test_case_3() { int Arg0 = 11; int Arg1 = 60000; verify_case(3, Arg1, cut(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	MyLongCake ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

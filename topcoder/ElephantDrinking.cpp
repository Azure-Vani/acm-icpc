// BEGIN CUT HERE
// END CUT HERE
#line 166 "ElephantDrinking.cpp"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>

using namespace std;

class ElephantDrinking {
	public:
	int maxSum(vector <string> field) {
		return 0;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"00000",
 "00110",
 "01000",
 "00100",
 "00000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, maxSum(Arg0)); }
	void test_case_1() { string Arr0[] = {"111",
 "191",
 "111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(1, Arg1, maxSum(Arg0)); }
	void test_case_2() { string Arr0[] = {"1010",
 "0011",
 "1100",
 "1111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, maxSum(Arg0)); }
	void test_case_3() { string Arr0[] = {"0011",
 "1110",
 "0111",
 "0101"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, maxSum(Arg0)); }
	void test_case_4() { string Arr0[] = {"11100",
 "00100",
 "11111",
 "00100",
 "10111"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 13; verify_case(4, Arg1, maxSum(Arg0)); }
	void test_case_5() { string Arr0[] = {"023771",
 "509514",
 "675579",
 "367472",
 "575198",
 "115281"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 112; verify_case(5, Arg1, maxSum(Arg0)); }
	void test_case_6() { string Arr0[] = {"11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111111111111111111111111111111",
 "11111111111011111111111111101111111111",
 "11111111111000111111111100001111111111",
 "11111111111000001111111000011111111111",
 "11111111111100000000000000011111111111",
 "11111111111100000000000000011111111111",
 "11111111111100000000000000111111111111",
 "11111111111110000000000000111111111111",
 "11111111111100000000000000011111111111",
 "11111111111000000000000000001111111111",
 "11111110111000000000000000001110111111",
 "11111110010000000000000000001100111111",
 "11111111000000000000000000001001111111",
 "11111111110000000000000000000011111111",
 "11111111100000110000000011000001111111",
 "11111110000001111000001111000000111111",
 "11111100000000111000001100000000101111",
 "11110000000110111000001101100000000111",
 "11111000000111110000000111111000111111",
 "11111100001111110000000111111111111111",
 "11111111111111100000000011111111111111",
 "11111111111111100000000011111111111111",
 "11111111111111000000000011111111111111",
 "11111111111111000000000011111111111111",
 "11111111111111100000000111111111111111",
 "11111111111111100000000111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 148; verify_case(6, Arg1, maxSum(Arg0)); }

// END CUT HERE

};// BEGIN CUT HERE

int main(){
	ElephantDrinking ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

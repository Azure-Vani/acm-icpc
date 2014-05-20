// BEGIN CUT HERE
// END CUT HERE
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstring>

#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); ++it)

using namespace std;

class SplitStoneGame {
	public:
	int f[100][100], n;

	string winOrLose(vector <int> number) {
		n = number.size();
		if (n <= 2) return "LOSE";
		memset(f, 0, sizeof f);
		for (int i = 3; i <= n; i++) {
			for (int j = 0; j < i; j++) {
				int l1 = j, l2 = i - j;
				if (l2 > 2 && !f[i - 1][j]) f[i][j] = 1;
				if (l2 > 1 && l1 >= 1 && !f[i - 1][j - 1]) f[i][j] = 1;
				if (l1 >= 2 && !f[i - 1][j - 2]) f[i][j] = 1;
			}
		}
		int t = 0; foreach(it, number) t += (*it == 1);
		return f[n][t] ? "WIN" : "LOSE";
	}
	
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(0, Arg1, winOrLose(Arg0)); }
	void test_case_1() { int Arr0[] = {2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(1, Arg1, winOrLose(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "WIN"; verify_case(2, Arg1, winOrLose(Arg0)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 4, 3, 2, 2, 4, 3, 1, 4, 4, 1, 2, 4, 4, 1, 4, 3, 1, 4, 2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "WIN"; verify_case(3, Arg1, winOrLose(Arg0)); }
	void test_case_4() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 9, 1, 3, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LOSE"; verify_case(4, Arg1, winOrLose(Arg0)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
SplitStoneGame ___test;
___test.run_test(-1);
return 0;
}
// END CUT HERE


#include <string>
#include <cstring>
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

long long f[5010], g[5010];
const int mod = 1000000007;

int C[5001][5001];

class LongWordsDiv1 {
	public:
	int count(int n) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		C[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= n; j++)
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}

		f[0] = f[1] = 1; g[0] = 0; g[1] = 1;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= i - 1; j++) {
				g[i] = max(g[i], g[j] + g[i - 1 - j] + 2 + (j != i - 1));
			}
			for (int j = 1; j <= i - 1; j++) if (g[i] == g[j] + g[i - 1 - j] + 2 + (j != i - 1)) {
				f[i] = (f[i] + ((f[j] * f[i - 1 - j] % mod) * C[i - 1][j]) % mod) % mod;
			}
			f[i] = (f[i] * i) % mod;
		}
		return f[n];
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 1080; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 486425238; verify_case(3, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	LongWordsDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

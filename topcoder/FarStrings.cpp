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
#include <cstring>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

class FarStrings {
	public:
	int n;
	
	string S;
	int f[50][50], g[50][50];

	inline pair<int, int> Dp(string T) {
		f[0][0] = g[0][0] = 0;
		for (int i = 1; i <= n; i++) f[0][i] = g[0][i] = f[i][0] = g[i][0] = i;
		for (int i = 1; i <= (int)S.length(); i++)
			for (int j = 1; j <= (int)T.length(); j++) {
				f[i][j] = min(f[i][j - 1], f[i - 1][j]) + 1;
				g[i][j] = min(g[i][j - 1], g[i - 1][j]) + 1;
				if (S[i - 1] == '?' || T[j - 1] == '?') {
					f[i][j] = min(f[i][j], f[i - 1][j - 1]);
					g[i][j] = min(g[i][j], g[i - 1][j - 1] + 1);
				} else {
					f[i][j] = min(f[i][j], f[i - 1][j - 1] + (S[i - 1] != T[j - 1]));
					g[i][j] = min(g[i][j], g[i - 1][j - 1] + (S[i - 1] != T[j - 1]));
				}
			}
		return make_pair(f[n][n], g[n][n]);
	}

	inline string Cal(int len) {
		string st(n, '?');
		for (int i = 0; i < n; i++) {
			for (int c = 'a'; c <= 'z'; c++) {
				st[i] = c;
				pair<int, int> tmp = Dp(st);
				if (tmp.first <= len && len <= tmp.second) break;
			}
		}
		return st;
	}

	vector <string> find(string t) {
		vector<string> Ans; S = t;
		n = t.length();
		for (int i = 1; i <= n; i++) {
			Ans.push_back(Cal(i));
		}
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "atan"; string Arr1[] = {"aaan", "aaaa", "aaba", "babb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, find(Arg0)); }
	void test_case_1() { string Arg0 = "ir"; string Arr1[] = {"ar", "aa" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, find(Arg0)); }
	void test_case_2() { string Arg0 = "aaa"; string Arr1[] = {"aab", "abb", "bbb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, find(Arg0)); }
	void test_case_3() { string Arg0 = "bazinga"; string Arr1[] = {"aazinga", "aaainga", "aaaanga", "aaaaaga", "aaaaaaa", "aaaaaab", "abbaabb" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, find(Arg0)); }
	void test_case_4() { string Arg0 = "bcdab"; string Arr1[] = {"acdab", "aadab", "aaaab", "aaaaa", "aaaca" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, find(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	FarStrings ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

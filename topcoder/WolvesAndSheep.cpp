// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolvesAndSheep.cpp"
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

int zero = 0;
class WolvesAndSheep {
	public:
	int n, m, sheep[20][20], wolf[20][20], divide[20], f[20];
	inline int& getSheep(int x, int y) {
		if (x >= 0 && y >= 0) return sheep[x][y]; else return zero;
	}
	inline int& getWolf(int x, int y) {
		if (x >= 0 && y >= 0) return wolf[x][y]; else return zero;
	}
	inline int sumSheep(int x1, int y1, int x2, int y2) {
		return getSheep(x2, y2) - getSheep(x1 - 1, y2) - getSheep(x2, y1 - 1) + getSheep(x1 - 1, y1 - 1);
	}
	inline int sumWolf(int x1, int y1, int x2, int y2) {
		return getWolf(x2, y2) - getWolf(x1 - 1, y2) - getWolf(x2, y1 - 1) + getWolf(x1 - 1, y1 - 1);
	}
	inline int Vaild(int x1, int y1, int x2, int y2) {
		int nWolf = sumWolf(x1, y1, x2, y2);
		int nSheep = sumSheep(x1, y1, x2, y2);
		if (nWolf > 0 && nSheep > 0) return false; else return true;
	}
	int getmin(vector <string> field) {
		n = field.size(); m = field[0].size();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				getSheep(i, j) = getSheep(i - 1, j) + getSheep(i, j - 1) - getSheep(i - 1, j - 1) + (field[i][j] == 'S');
				getWolf(i, j) = getWolf(i - 1, j) + getWolf(i, j - 1) - getWolf(i - 1, j - 1) + (field[i][j] == 'W');
			}
		if (getSheep(n - 1, m - 1) == 0 || getWolf(n - 1, m - 1) == 0) return 0;
		int Ans = ~0u>>1;
		for (int i = 0; i < (1 << (n - 1)); i++) {
			memset(divide, 0, sizeof divide); int cnt = 0;
			for (int j = 0; j < n - 1; j++) if (i & ( 1 << j)) divide[j] = 1, cnt++; divide[n - 1] = 1;
			int ok = true;
			for (int j = 0; j < m && ok; j++) {
				int last = 0;
				for (int k = 0; k < n && ok; k++) if (divide[k]) {
					ok &= Vaild(last, j, k, j);
					last = k + 1;
				}
			}
			if (!ok) continue;
			f[0] = 1;
			for (int j = 1; j < m; j++) {
				f[j] = ~0u>>1;
				for (int k = j - 1; k >= -1; k--) {
					int ok = 1, last = 0;
					for (int l = 0; l < n && ok; l++) if (divide[l]) {
						ok &= Vaild(last, k + 1, l, j);
						last = l + 1;
					}
					if (!ok) break;
					f[j] = min(f[j], k >= 0 ? f[k] + 1 : 1);
				}
			}
			Ans = min(Ans, f[m - 1] + cnt - 1);
		}
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"W.WSS",
 "WW.S.",
 ".SSS.",
 "SSS.S",
 ".SS.S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arr0[] = {
 "WSWSW",
 "SWSWS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arr0[] = {".SS",
 "...",
 "S..",
 "W.W"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arr0[] = {
 "WWWSWWSSWWW",
 "WWSWW.SSWWW",
 "WS.WSWWWWS."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arr0[] = {".W.S.W.W",
 "W.W.S.W.",
 ".S.S.W.W",
 "S.S.S.W.",
 ".S.W.W.S",
 "S.S.W.W.",
 ".W.W.W.S",
 "W.W.S.S."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arr0[] = {"W.SSWWSSSW.SS",
 ".SSSSW.SSWWWW",
 ".WWWWS.WSSWWS",
 "SS.WSS..W.WWS",
 "WSSS.SSWS.W.S",
 "WSS.WS...WWWS",
 "S.WW.S.SWWWSW",
 "WSSSS.SSW...S",
 "S.WWSW.WWSWSW",
 ".WSSS.WWSWWWS",
 "..SSSS.WWWSSS",
 "SSWSWWS.W.SSW",
 "S.WSWS..WSSS.",
 "WS....W..WSS."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; verify_case(5, Arg1, getmin(Arg0)); }
	void test_case_6() { string Arr0[] = {"WW..SS",
 "WW..SS",
 "......",
 "......",
 "SS..WW",
 "SS..WW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(6, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	WolvesAndSheep ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

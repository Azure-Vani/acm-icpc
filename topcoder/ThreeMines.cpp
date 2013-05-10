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
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define SUM(x1,y1,x2,y2) (sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1])

typedef long long Int64;

using namespace std; 

const int inf = 100000000;
const int MAXN = 33;
int a[MAXN][MAXN], n, m, sum[MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN][4];bool vis[MAXN][MAXN][MAXN][MAXN][4];

class ThreeMines { public:
	void Max(int &a, int b) {
		if (a < b) 
			a = b;
	}
	int Get(char c) {
		if (islower(c)) {
			return c - 'a';
		} else return 'A' - c;
	}
	int Dfs(int x1, int y1, int x2, int y2, int c = 1) {
		if (x1 > x2 || y1 > y2) return -inf;
		bool &tmp = vis[x1][y1][x2][y2][c];
		int &ret = f[x1][y1][x2][y2][c];
		if (tmp) return ret; tmp = true; 
		if (c == 1) {
			ret = SUM(x1, y1, x2, y2);
			Max(ret, Dfs(x1 + 1, y1, x2, y2));
			Max(ret, Dfs(x1, y1 + 1, x2, y2));
			Max(ret, Dfs(x1, y1, x2 - 1, y2));
			Max(ret, Dfs(x1, y1, x2, y2 - 1));
			return ret;
		}
		ret = -inf;
		if (c == 2) {
			for (int i = x1; i <= x2; i++) {
				Max(ret, Dfs(x1, y1, i, y2, 1) + Dfs(i + 1, y1, x2, y2, 1));
			}
			for (int i = y1; i <= y2; i++) {
				Max(ret, Dfs(x1, y1, x2, i, 1) + Dfs(x1, i + 1, x2, y2, 1));
			}
		}
		if (c == 3) {
			for (int i = x1; i <= x2; i++) {
				Max(ret, Dfs(x1, y1, i, y2, 2) + Dfs(i + 1, y1, x2, y2, 1));
				Max(ret, Dfs(x1, y1, i, y2, 1) + Dfs(i + 1, y1, x2, y2, 2));
			}
			for (int i = y1; i <= y2; i++) {
				Max(ret, Dfs(x1, y1, x2, i, 2) + Dfs(x1, i + 1, x2, y2, 1));
				Max(ret, Dfs(x1, y1, x2, i, 1) + Dfs(x1, i + 1, x2, y2, 2));
			}
		}
		return ret;
	}
	int maximumProfit(vector <string> field) {
		n = field.size(), m = field[0].length();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				a[i][j] = Get(field[i - 1][j - 1]);
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + a[i][j];
			}
		}
		return Dfs(1, 1, n, m, 3);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"bbbb",
"bBBB",
"BBbb",
"BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(0, Arg1, maximumProfit(Arg0)); }
	void test_case_1() { string Arr0[] = {"cfCBDCbcdZb"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(1, Arg1, maximumProfit(Arg0)); }
	void test_case_2() { string Arr0[] = {"d", "c", "B", "m", "Z", "h", "g", "B", "z", "G", "H", "b", "Y"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 54; verify_case(2, Arg1, maximumProfit(Arg0)); }
	void test_case_3() { string Arr0[] = {
"hBhh", 
"BBBB",
"BBBB", 
"hBhh", 
"hBhh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 62; verify_case(3, Arg1, maximumProfit(Arg0)); }
	void test_case_4() { string Arr0[] = {
"BB", 
"BB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -3; verify_case(4, Arg1, maximumProfit(Arg0)); }
	void test_case_5() { string Arr0[] = {
"ZcabcaacacabcbbbcababacaccbZaa",
"acaaccccacbccbaaccabaccaacbZbc",
"bcbaacbcbbccbbcbabbbbaZcbcbccb",
"cccacbabccbZbcbabaacbbZcbacbab",
"cacbabbcabbabbcacbcbbcaacaabbc",
"bacZcacaaccbabbcccccabcaacbaca",
"cbcccacabcabacaccacaZbbcbcacbb",
"cZbbbcaacbaacaabZcaccbcZccbbab",
"Zcababaacbbbbccbcbbaccacacbbcc",
"cZcccaaabbcbcbccccbcbaabbbccbb",
"bbcaacacabccababacbccacccbbaba",
"cccbbcaZabccacabbccccabbabbbab",
"bbbacbccbbcaabaaabccbcaabcacaa",
"cbbababbccccbcccbaacacccaabaac",
"aaccaccaccbabbccaaaacbacccacca",
"bbbcabcabZZcabcabbaacZbaaabaZb",
"aaabbabcabaaacbcccccbbcabcccbc",
"bbbaccbacacaccbbaccabacbbbaaac",
"acaaacccbabbccbcbabbcbaaaccabb",
"bcaaaaabcbabaaabccacccbaacbbbc",
"bZcbcbcccaabccaabbccbababbbcca",
"cbbbbcccabcabcbacaaaaabbbbbcac",
"ccbbcbacacbbcacacbaabcbbacbaba",
"cbbbaabaabbbbaccabbcbcaccaaaac",
"abZcabaacbbcacbaaabccbabacacaa",
"aabccacbabaacaccccbbbbcccccaca",
"aabcbaaacbabcaccbaabbbabbabbca",
"ababcabaccaaaacccacbcbcabacbcb",
"bcaaaacabcabbbaccccccacabccacb",
"cbbabbbccaaaaacbccaabcbbccbacc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 671; verify_case(5, Arg1, maximumProfit(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	ThreeMines ___test;  
 	___test.run_test(5); 
	return 0;
}
// END CUT HERE

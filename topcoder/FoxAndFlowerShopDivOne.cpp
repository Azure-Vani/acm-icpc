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
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 35;
const int MAXM = 905;

int sa[MAXN][MAXN], a[MAXN][MAXN], sb[MAXN][MAXN];
int left[MAXN][MAXM], right[MAXN][MAXM], up[MAXN][MAXM], down[MAXN][MAXM];

class FoxAndFlowerShopDivOne {
	public:
	int theMaxFlowers(vector <string> flowers, int maxDiff) {
		int n = flowers.size(), m = flowers[0].length();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				sa[i + 1][j + 1] = sa[i][j + 1] + sa[i + 1][j] - sa[i][j] + (flowers[i][j] == 'L');
				sb[i + 1][j + 1] = sb[i][j + 1] + sb[i + 1][j] - sb[i][j] + (flowers[i][j] == 'P');
			}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
			 	for (int x = 1; x <= i; x++) 
					for (int y = 1; y <= j; y++) {
						int sum_a = sa[i][j] - sa[i][y - 1] - sa[x - 1][j] + sa[x - 1][y - 1];
						int sum_b = sb[i][j] - sb[i][y - 1] - sb[x - 1][j] + sb[x - 1][y - 1];
						int d = sum_a - sum_b;
						for (int l = x; l > 0; l--) {
							left[l].Insert(d, sum_a + sum_b);
						}
						for (int l = i + 1; l <= n; l++) {
							up[l].Insert(d, sum_a + sum_b);
						}
						for (int l = y; l > 0; l--) {
							right[l].Insert(d, sum_a + sum_b);
						}
						for (int l = j + 1; l <= m; l++) {
							left[l].Insert(d, sum_a + sum_b);
						}
					}
			}
		}
		int Ans = -inf;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				for (int x = 1; x <= i; x++) {
					for (int y = 1; y <= j; y++) {
						int sum_a = sa[i][j] - sa[i][y - 1] - sa[x - 1][j] + sa[x - 1][y - 1];
						int sum_b = sb[i][j] - sb[i][y - 1] - sb[x - 1][j] + sb[x - 1][y - 1];
						int d = sum_a - sum_b, l1 = -d, r1 = min(maxDiff - d, 900), l2 = max(-900, -maxDiff - d), r2 = -d;
						int u1 = up[x].Cal(l1, r1);
						int u2 = up[x].Cal(l2, r2);
						int d1 = down[i].Cal(l1, r1);
						int d2 = down[i].Cal(l2, r2);
						int le1 = left[y].Cal(l1, r1);
						int le2 = left[y].Cal(l2, r2);
						int r1 = right[j].Cal(l1, r1);
						int r2 = right[j].Cal(l2, r2);
						Ans = max(Ans, sum_a + sum_b + max(u1, max(u2, max(d1, max(d2, max(le1, max(le2, max(r1, r2))))))));
					}
				}
			}
		}
		if (Ans >= 0) return Ans; else return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; verify_case(0, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 6; verify_case(1, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 0; verify_case(2, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"LLPL.LPP",
 "PLPPPPLL",
 "L.P.PLLL",
 "LPL.PP.L",
 ".LLL.P.L",
 "PPLP..PL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 38; verify_case(3, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = -1; verify_case(4, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"LLLP..LLP.PLL.LL..LP",
 "L.PL.L.LLLL.LPLLPLP.",
 "PLL.LL.LLL..PL...L..",
 ".LPPP.PPPLLLLPLP..PP",
 "LP.P.PPL.L...P.L.LLL",
 "L..LPLPP.PP...PPPL..",
 "PP.PLLL.LL...LP..LP.",
 "PL...P.PPPL..PLP.L..",
 "P.PPPLPLP.LL.L.LLLPL",
 "PLLPLLP.LLL.P..P.LPL",
 "..LLLPLPPPLP.P.LP.LL",
 "..LP..L..LLPPP.LL.LP",
 "LPLL.PLLPPLP...LL..P",
 "LL.....PLL.PLL.P....",
 "LLL...LPPPPL.PL...PP",
 ".PLPLLLLP.LPP...L...",
 "LL...L.LL.LLLPLPPPP.",
 "PLPLLLL..LP.LLPLLLL.",
 "PP.PLL..L..LLLPPL..P",
 ".LLPL.P.PP.P.L.PLPLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; int Arg2 = 208; verify_case(5, Arg2, theMaxFlowers(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	FoxAndFlowerShopDivOne ___test;  
 	___test.run_test(-1); 
	return 0;
}
 // END CUT HERE

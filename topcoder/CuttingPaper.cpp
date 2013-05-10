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
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 55;

vector< pair<int, int> > Edge[MAXN][MAXN];
bool vis[MAXN][MAXN], start[MAXN][MAXN], exist[MAXN][MAXN];
int a[MAXN][MAXN];

class CuttingPaper {
	public:
	void Add(int x1, int y1, int x2, int y2) {
		Edge[x1][y1].pb(mp(x2, y2));
		Edge[x2][y2].pb(mp(x1, y1));
		//printf("%d %d\n%d %d\n----------------\n", x1, y1, x2, y2);
	}
	void Dfs(int x, int y) {
		if (vis[x][y]) return;
		vis[x][y] = true;
		foreach(it, Edge[x][y]) 
			Dfs(it->first, it->second);
	}
	bool Distinct(int a, int b, int c, int d) {
		return !(a == b && a == c && a == d);
	}
	int minCuts(vector <string> paper) {
		memset(vis, 0, sizeof vis); memset(start, 0, sizeof start); memset(exist, 0, sizeof exist);
		memset(a, 0, sizeof a);
		for (int i = 0; i <= MAXN - 1; i++) for (int j = 0; j <= MAXN - 1; j++) Edge[i][j].clear();
		int ret = 0, n = paper.size(), m = 0;
		foreach(it, paper) m = std::max(m, (int)it->length());
		foreach(it, paper) while ((int)it->length() < m) *it += " ";
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) {
				if (paper[i - 1][j - 1] != ' ')
				a[i][j] = paper[i - 1][j - 1] - 'A' + 1;
				else a[i][j] = 0;
			}
		for (int i = 1; i <= n + 1; i++) 
			for (int j = 1; j <= m + 1; j++) {
				start[i][j] = (a[i][j] && a[i - 1][j] && a[i][j - 1] && a[i - 1][j - 1]); start[i][j] ^= 1;
				exist[i][j] = Distinct(a[i][j], a[i - 1][j], a[i][j - 1], a[i - 1][j - 1]);
				if (a[i][j] && a[i - 1][j] && a[i][j] != a[i - 1][j])
					Add(i, j, i, j + 1);
				if (a[i][j] && a[i][j - 1] && a[i][j] != a[i][j - 1])
					Add(i, j, i + 1, j);
			}
		for (int i = 1; i <= n + 1; i++) 
			for (int j = 1; j <= m + 1; j++) if (start[i][j])
				Dfs(i, j);
		for (int i = 1; i <= n + 1; i++) 
			for (int j = 1; j <= m + 1; j++) if (exist[i][j] && !vis[i][j])
				return -1;
		for (int i = 1; i <= n + 1; i++) 
			for (int j = 1; j <= m + 1; j++) if (exist[i][j]) {
				int d = Edge[i][j].size();
				if (start[i][j] || d <= 1) ret += d; else ret += d - 2;
			}
		return ret / 2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"AABB",
 "AABB",
 "BBDD",
 "BBDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minCuts(Arg0)); }
	void test_case_1() { string Arr0[] = {"  X",
 " XXX A Y",
 "XX XX YYY",
 " XXX B Y",
 "  X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minCuts(Arg0)); }
	void test_case_2() { string Arr0[] = {"AAA",
 "ABA",
 "AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, minCuts(Arg0)); }
	void test_case_3() { string Arr0[] = {"ABBBB",
 "AABBB",
 "AAABB",
 "AAAAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, minCuts(Arg0)); }
	void test_case_4() { string Arr0[] = {"AABB",
 "A BB",
 "CCDD",
 "CCDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, minCuts(Arg0)); }
	void test_case_5() { string Arr0[] = {"BAA",
 "ABA",
 "AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(5, Arg1, minCuts(Arg0)); }
	void test_case_6() { string Arr0[] = {"BBB CCCC",
 "BAB CD C",
 "BB  CCCC"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(6, Arg1, minCuts(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	CuttingPaper ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

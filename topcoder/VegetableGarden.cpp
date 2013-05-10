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

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 
const int MAXN = 52, MAXP = 10, MAXM = 1 << MAXP;

struct Node {
	int x, y, s;
	Node(int x, int y, int s):x(x), y(y), s(s){}
};

int a[MAXN][MAXN], n, m;
int lab[MAXN][MAXN], under[MAXN][MAXN], f[MAXN][MAXN][MAXM];
bool vis[MAXN][MAXN][MAXM];
queue<Node> Q;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

class VegetableGarden {
	public:
	vector <int> getMinDistances(vector <string> garden) {
		n = garden.size(), m = garden[0].length();
		int opp = 0, sid = 0, num = 0;
		memset(lab, -1, sizeof lab);
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= m - 1; j++) {
				if (garden[i][j] == 'I') a[i][j] = 1, lab[i][j] = sid++, num++;;
				if (garden[i][j] == 'X') a[i][j] = 2, opp |= 1 << sid, lab[i][j] = sid++;
			}
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= m - 1; j++) {
				for (int k = i; k <= n - 1; k++) if (lab[k][j] != -1)
					under[i][j] |= 1 << lab[k][j];
			}
		memset(f, 60, sizeof f);
		memset(vis, 0, sizeof vis);
		Q.push(Node(0, 0, 0));
		vis[0][0][0] = false;
		f[0][0][0] = 0;
		while (!Q.empty()) {
			int x = Q.front().x, y = Q.front().y, s = Q.front().s; Q.pop();
			for (int dir = 0; dir <= 3; dir++) {
				int lx = x + dx[dir], ly = y + dy[dir], ns = s;
				if (lx < 0 || lx > n || ly < 0 || ly > m) continue;
				if (dir == 0) ns ^= under[x][y];
				if (dir == 2) ns ^= under[lx][ly];
				if (f[lx][ly][ns] > f[x][y][s] + 1) {
					f[lx][ly][ns] = f[x][y][s] + 1;
					if (!vis[lx][ly][ns])
						Q.push(Node(lx, ly, ns));
				}
			}
			vis[x][y][s] = false;
		}
		vector<int> ret(num, 100000000);
		for (unsigned int i = 1; i <= (1u << sid) - 1; i++) {
			unsigned int opi = (~i) & ((1u << sid) - 1);
			if ((opi & opp) != opp) continue;
			unsigned int t = __builtin_popcount(i);
			ret[t - 1] = std::min(ret[t - 1], f[0][0][i]);
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"I"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getMinDistances(Arg0)); }
	void test_case_1() { string Arr0[] = {"XX", 
 "XI"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getMinDistances(Arg0)); }
	void test_case_2() { string Arr0[] = {"III", 
 "IXI",
 "III"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6, 8, 10, 12, 14, 16, 18 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getMinDistances(Arg0)); }
	void test_case_3() { string Arr0[] = {"X.I", 
 ".I.", 
 "I.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 10, 14 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getMinDistances(Arg0)); }
	void test_case_4() { string Arr0[] = {"IIXIIXIXII"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 6, 12, 14, 20, 26, 28 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, getMinDistances(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	VegetableGarden ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

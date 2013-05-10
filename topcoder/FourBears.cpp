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
#define Is(a, i) ((a) & (1 << (i)))
#define In(a, b, c) ((a) >= (b) && (a) <= (c))

typedef long long Int64;

using namespace std; 

const int MAXN = 8;
const int MAXM = 51;

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

class FourBears {
	public:

	int a[MAXN][MAXM];
	int dis[MAXN][MAXM][MAXN][MAXM];

	vector< pair<int, int> > bear[2];

	int Dis(pair<int, int> a, int x, int y) {
		return dis[a.first][a.second][x][y];
	}
	int Delta(int x1, int y1, int x2, int y2) {
		return ((int)a[x1][y1] + (int)a[x2][y2]) << 1;
	}

	int clearPassages(vector <string> field) {
		int n = field.size(), m = field[0].length();
		memset(dis, 50, sizeof dis);
		for (int i = 0; i <= n - 1; i++) for (int j = 0; j <= m - 1; j++) {
			a[i][j] = (field[i][j] == '.');
			if (j == 0 || j == m - 1) a[i][j] = 100000000;
			if (field[i][j] == 'B')
				bear[(bool)j].pb(make_pair(i, j)), a[i][j] = 0;
			dis[i][j][i][j] = a[i][j];
		}

		for (int i = 0; i <= n - 1; i++) for (int j = 0; j <= m - 1; j++) {
			for (int t = 0; t <= 3; t++) {
				int x = i + dx[t], y = j + dy[t];
				if (In(x, 0, n - 1) && In(y, 0, m - 1))
					dis[i][j][x][y] = std::min(dis[i][j][x][y], (int)a[i][j] + (int)a[x][y]);
			}
		}

		for (int k1 = 0; k1 <= n - 1; k1++) for (int k2 = 0; k2 <= m - 1; k2++) {
			int d = a[k1][k2];
			for (int i1 = 0; i1 <= n - 1; i1++)  for (int i2 = 0; i2 <= m - 1; i2++) 
				for (int j1 = 0; j1 <= n - 1; j1++) for (int j2 = 0; j2 <= m - 1; j2++) {
					dis[i1][i2][j1][j2] = std::min(dis[i1][i2][j1][j2], dis[i1][i2][k1][k2] + dis[k1][k2][j1][j2] - d);
				}
		}
		int ret = 10000000;
		for (int i1 = 0; i1 <= n - 1; i1++) for (int i2 = 0; i2 <= m - 1; i2++) {
			for (int j1 = 0; j1 <= n - 1; j1++) for (int j2 = 0; j2 <= m - 1; j2++) {
				int v1 = Dis(bear[0][0], i1, i2) + Dis(bear[0][1], i1, i2) + Dis(bear[1][0], j1, j2) + Dis(bear[1][1], j1, j2) 
					+ dis[i1][i2][j1][j2] - Delta(i1, i2, j1, j2);
				int v2 = Dis(bear[0][0], i1, i2) + Dis(bear[0][1], j1, j2) + Dis(bear[1][0], i1, i2) + Dis(bear[1][1], j1, j2) 
					+ dis[i1][i2][j1][j2] - Delta(i1, i2, j1, j2);
				ret = std::min(ret, std::min(v1, v2));
			}
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
 "B.X...............",
 "..X..XXXXXXXXXX..B",
 "B.X..X........X...",
 ".....X........X...",
 "..XXXX........X..B"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(0, Arg1, clearPassages(Arg0)); }
	void test_case_1() { string Arr0[] = {
 "..................",
 "B..........XXXX..B",
 "..........X.......",
 "....XXXXXX........",
 "..........XX......",
 "B............XX..B",
 ".................."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(1, Arg1, clearPassages(Arg0)); }
	void test_case_2() { string Arr0[] = {
 "B.B",
 "...",
 "B.B"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, clearPassages(Arg0)); }
	void test_case_3() { string Arr0[] = {
 "..B",
 "B.B",
 "B.."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, clearPassages(Arg0)); }
	void test_case_4() { string Arr0[] = {
 "B..................XX.................XX.XXX.....B",
 "...XXXXX.....XXXX......XXXXX.....XXXX..XXX.XXXX...",
 "............XX..................XX................",
 ".......XXX........XX..X....XXX...........XXX......",
 "............XXX......X.XXX......XXX.XXX..X.XXX....",
 "....XXXX......XXX...X...XXXX......XXX.XXXX........",
 "B..XX..............XX............................B"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 28; verify_case(4, Arg1, clearPassages(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	FourBears ___test;  
 	___test.run_test(5); 
	return 0;
}
// END CUT HERE

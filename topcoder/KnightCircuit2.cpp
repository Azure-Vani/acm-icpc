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

int vis[11][45010], sum[45010 * 11], d[45010 * 11][2];
int dx[] = {1, 2, 1, 2, -1, -2, -1, -2};
int dy[] = {2, 1, -2, -1, 2, 1, -2, -1}; int w, h;

class KnightCircuit2 {
	public:
	int Bfs(int x0, int y0, int color) {
		vis[x0][y0] = color;
		int head = 1, tail = 1; d[1][0] = x0, d[1][1] = y0;
		while (head <= tail) {
			int x = d[head][0], y = d[head++][1];
			for (int i = 0; i < 8; i++) {
				int nx = x + dx[i], ny = y + dy[i];
				if (nx > 0 && nx <= w && ny > 0 && ny <= h && !vis[nx][ny]) {
					vis[nx][ny] = color;
					d[++tail][0] = nx, d[tail][1] = ny;
				}
			}
		}
		return tail;
	}

	int maxSize(int w, int h) {
		if (w >= 9 && h >= 9) return w * h; else {
			if (w > h) swap(w, h);
		}
		::w = w, ::h = h;
		int c = 0; memset(vis, 0, sizeof vis); memset(sum, 0, sizeof sum);
		for (int i = 1; i <= w; i++)
			for (int j = 1; j <= h; j++) if (!vis[i][j]) {
				++c;
				sum[c] = Bfs(i, j, c);
			}
		int ret = 0;
		for (int i = 1; i <= c; i++) ret = max(ret, sum[i]);
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 15; int Arg1 = 2; int Arg2 = 8; verify_case(1, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 10000; verify_case(2, Arg2, maxSize(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	KnightCircuit2 ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

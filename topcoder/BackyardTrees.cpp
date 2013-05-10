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
#define R(a) ((int)((a) + 0.5))

typedef long long Int64;

using namespace std; 

const int MAXN = 520;
const int mod = 1000000000;
int C[MAXN][MAXN];

class BackyardTrees {
	public:
	int gcd(int a, int b) {
		return !b ? a : gcd(b, a % b);
	}
	int Cal(int W, int H, int t, int d) {
		int g = gcd(W, H);
		if (t > g) return 0;
		double Len = sqrt(sqr(W) + sqr(H)) / (double)g;
		int skip = 0;
		double tmp = 0;
		while (tmp + 0.00001< d) {
			skip++;
			tmp += Len;
		}
		if (skip * t > g) return 0;
		g -= skip * t;
		int ret = C[g + t - 1][t - 1];
		return ret;
	}
	int countWays(int treeCount, int width, int height, int distance) {
		if (treeCount == 1) {
			return (width + 1) * (height + 1) % mod;
		}
		C[0][0] = 1;
		for (int i = 1; i <= MAXN - 1; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= MAXN - 1; j++) 
				C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
		}
		int ret = 0;
		for (int w = 0; w <= width; w++) 
			for (int h = 0; h <= height; h++) {
				int mul = (w && h) ? 2 : 1;
				Int64 tmp = mul * Cal(w, h, treeCount - 1, distance) % mod;
				tmp = tmp * (Int64) (width - w + 1) * (Int64) (height - h + 1) % mod;
				ret = (ret + tmp) % mod;
			}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 4; int Arg2 = 4; int Arg3 = 1; int Arg4 = 300; verify_case(0, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 13; int Arg1 = 36; int Arg2 = 48; int Arg3 = 5; int Arg4 = 2; verify_case(1, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 5; int Arg2 = 5; int Arg3 = 1; int Arg4 = 88; verify_case(2, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 50; int Arg1 = 49; int Arg2 = 49; int Arg3 = 1; int Arg4 = 102; verify_case(3, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 6; int Arg1 = 5; int Arg2 = 5; int Arg3 = 2; int Arg4 = 0; verify_case(4, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 10; int Arg1 = 55; int Arg2 = 75; int Arg3 = 5; int Arg4 = 490260662; verify_case(5, Arg4, countWays(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	BackyardTrees ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

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

const int MAXN = 521;

long double f[MAXN][MAXN], g[MAXN];
bool vis[MAXN];

class RPSChamps {
	public:
	long double Cal(int N) {
		if (N == 1) return 0;
		if (vis[N]) return g[N]; vis[N] = true;
		long double &ret = g[N], tmp = 0; ret = 0;
		for (int i = 1; i <= N - 1; i++) 
			tmp += f[N][i];
		for (int i = 1; i <= N - 1; i++) {
			ret += (Cal(i) + Cal(N - i)) * f[N][i] / tmp;
		}
		return ret += 1.0 / tmp;
	}
	double numberOfMoves(int N) {
		long double one_three = 1.0 / 3.0;
		f[0][0] = 1;
		for (int i = 1; i <= N; i++) {
			f[i][i] = f[i][0] = f[i - 1][0] * one_three;
			for (int j = 1; j < i; j++) {
				f[i][j] = (f[i - 1][j] + f[i - 1][j - 1]) * one_three;
			}
		}
		memset(vis, 0, sizeof vis);
		return (double)Cal(N) / 3.0;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; double Arg1 = 0.0; verify_case(0, Arg1, numberOfMoves(Arg0)); }
	void test_case_1() { int Arg0 = 2; double Arg1 = 1.5; verify_case(1, Arg1, numberOfMoves(Arg0)); }
	void test_case_2() { int Arg0 = 3; double Arg1 = 3.0; verify_case(2, Arg1, numberOfMoves(Arg0)); }
	void test_case_3() { int Arg0 = 10; double Arg1 = 35.59012622220019; verify_case(3, Arg1, numberOfMoves(Arg0)); }
	void test_case_4() { int Arg0 = 200; double Arg1 = 5.509733035960696E34; verify_case(4, Arg1, numberOfMoves(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RPSChamps ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

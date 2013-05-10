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

Int64 f[82][1 << 9][22];
Int64 C[82][22];

class SeatingPlan {
	public:
	bool Isgood(int n) {
		for (int i = 0; i <= 9; i++) if ((n & (1 << i)) && (n & (1 << (i + 1)))) return false;
		return true;
	}
	Int64 gcd(Int64 a, Int64 b) {
		if (!b) return a; else return gcd(b, a % b);
	}
	string expectedTrial(int m, int n, int k) {
		if (m > n) swap(m, n);
		f[0][0][0] = 1;
		for (int i = 0; i <= n - 1; i++) {
			for (unsigned int S = 0; S <= (unsigned int)(1 << m) - 1; S++) if (Isgood(S)) {
				int cnt = __builtin_popcount(S);
				for (int j = cnt; j <= k; j++) if (f[i][S][j]) {
					for (unsigned int next = 0; next <= (unsigned int)(1 << m) - 1; next++) if (Isgood(next)) {
						int tmp = __builtin_popcount(next);
						if (tmp + j <= k && (S & next) == 0) {
							f[i + 1][next][tmp + j] += f[i][S][j];
						}
					}
				}
			}
		}
		Int64 ret2 = 0;
		for (int i = 0; i <= (1 << m) - 1; i++) ret2 += (Int64)f[n][i][k];
		if (ret2 == 0) return string("Impossible!");
		C[0][0] = 1;
		for (int i = 1; i <= n * m; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= k; j++) {
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
		}
		Int64 ret1 = C[n * m][k];
		Int64 t = gcd(ret1, ret2); ret1 /= t, ret2 /= t;
		stringstream sin;
		sin <<ret1<<"/"<<ret2;
		return sin.str();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 80; int Arg1 = 1; int Arg2 = 10; string Arg3 = "20271005/5684749"; verify_case(0, Arg3, expectedTrial(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 0; string Arg3 = "1/1"; verify_case(1, Arg3, expectedTrial(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 2; string Arg3 = "15/8"; verify_case(2, Arg3, expectedTrial(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 2; string Arg3 = "3/2"; verify_case(3, Arg3, expectedTrial(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 8; int Arg1 = 7; int Arg2 = 18; string Arg3 = "70775996591300/172086661"; verify_case(4, Arg3, expectedTrial(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	SeatingPlan ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

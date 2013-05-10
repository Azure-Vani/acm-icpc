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
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899

typedef long long Int64;

using namespace __gnu_cxx;
using namespace std; 

const int MAXN = 71;

int mod;

inline void Add(int& a, int b) {
	a += b;
	if (a >= mod) a-=mod;
}

struct Matrix {
	int a[MAXN][MAXN];
	int n;
	void operator =(Matrix oth) {
		memcpy(a, oth.a, sizeof a);
	}
	Matrix(int v = 0) {
		memset(a, 0, sizeof a);
		for (int i = 0; i <= n - 1; i++) a[i][i] = v;
	}
	Matrix operator *(Matrix oth) const {
		Matrix ret;
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= n - 1; j++) {
				int tmp = 0;
				for (int k = 0; k <= n - 1; k++) {
					Add(tmp, (Int64) a[i][k] * oth.a[k][j] % mod);
				}
				ret.a[i][j] = tmp;
			}
		return ret;
	}
};

class TourCounting { public:
	
	Matrix ret, c;

	int countTours(vector <string> g, int k, int m) {
		int n = g.size();
		c.n = (n << 1);
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) 
			c.a[i][j] = (g[i][j] == 'Y');
		for (int i = 0; i <= n - 1; i++) {
			c.a[i][i + n] = c.a[i + n][i + n] = 1;
		}
		mod = m;
		ret = __gnu_cxx::power(c, k);
		int r = 0;
		for (int i = 0; i <= n - 1; i++) {
			Add(r, ret.a[i][i + n]);
		}
		r = (r - n) % mod;
		return r < 0 ? r + mod : r;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYNY",
 "NNYN",
 "YNNN",
 "YNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 100; int Arg3 = 12; verify_case(0, Arg3, countTours(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"NYNNNNN",
 "NNYNNNN",
 "NNNYNNN",
 "NNNNYNN",
 "NNNNNYN",
 "NNNNNNY",
 "YNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 40; int Arg2 = 13; int Arg3 = 9; verify_case(1, Arg3, countTours(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"NYNY",
 "NNNN",
 "YYNY",
 "NYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000; int Arg2 = 1000000000; int Arg3 = 0; verify_case(2, Arg3, countTours(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"NY",
 "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1500; int Arg2 = 1; int Arg3 = 0; verify_case(3, Arg3, countTours(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"NYYNYYN",
 "YNYNYNY",
 "NYNYNYN",
 "YYYNYNY",
 "NNYYNNY",
 "NYYYNNY",
 "YYYYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; int Arg2 = 100; int Arg3 = 72; verify_case(4, Arg3, countTours(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"NYYY",
 "YNYY",
 "YYNY",
 "YNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 10000; int Arg3 = 3564; verify_case(5, Arg3, countTours(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	TourCounting ___test;  
 	___test.run_test(1); 
	return 0;
}
// END CUT HERE

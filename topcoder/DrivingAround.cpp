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

const int MAXN = 60, Mod = 1000003;

int c[MAXN][MAXN], n;

inline void Add(int &a, int b, int c) {
	b = (Int64) b * c % Mod;
	a += b;
	if (a >= Mod) a -= Mod;
}

class Matrix {
	public:
	int a[MAXN][MAXN], n;
	Matrix(int k = 0) {this->n = ::n; memset(a, 0, sizeof a);for (int i = 0; i <= n - 1; i++) a[i][i] = k;}
	int& operator ()(int i, int j) {return a[i][j];}
	void operator =(const Matrix& oth) {
		memcpy(a, oth.a, sizeof a);
		n = oth.n;
	}
	Matrix operator *(const Matrix& oth) const {
		Matrix ret;
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= n - 1; j++) {
				int &tmp = ret(i, j); tmp = 0;
				for (int k = 0; k <= n - 1; k++) 
					Add(tmp, a[i][k], oth.a[k][j]);
			}
		return ret;
	}
};

Matrix init, res;

inline Matrix power(Matrix a, int b) {
	Matrix ret(1);
	while (b) {
		if (b & 1) ret = ret * a;
		b >>= 1;
		a = a * a;
	}
	return ret;
}

class DrivingAround {
	public:
	int numberOfWays(vector <string> adj, int start, int finish, int time) {
		n = adj.size();int sid = n;
		for (int i = 0; i <= sid - 1; i++) {
			for (int j = 0; j <= sid - 1; j++) if (adj[i][j] != '.') {
				int t = adj[i][j] - '0';
				if (t == 1) {
					c[i][j] = 1;
					continue;
				}
				for (int k = 1; k <= t - 2; k++) 
					c[n + k - 1][n + k] = 1;
				c[i][n] = 1; c[n + t - 2][j] = 1;
			}
			n += 4;
		}
		init.n = n;
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= n - 1; j++) 
				init(i, j) = c[i][j];
		res = power(init, time);
		return res(start, finish);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
 ".12",
 "2.1",
 "12."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 5; int Arg4 = 8; verify_case(0, Arg4, numberOfWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"....52....",
 "..5.......",
 "..........",
 ".......1..",
 "......42.2",
 "5...4.....",
 ".5...4...1",
 "......5...",
 ".3244.....",
 ".........."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 10; int Arg4 = 0; verify_case(1, Arg4, numberOfWays(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"...14....1",
 "......13..",
 ".2...4....",
 "....52.5..",
 "1.3..4....",
 ".3....35.5",
 "4......1.1",
 "..4.4.1.54",
 "....4.11.5",
 "31144.2.4."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 2; int Arg3 = 100; int Arg4 = 316984; verify_case(2, Arg4, numberOfWays(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	DrivingAround ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

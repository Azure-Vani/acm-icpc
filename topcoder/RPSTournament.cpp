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
const int MAXN = 1 << 17;
int n, c, r; bool vis[MAXN];
int d[MAXN];

class RPSTournament {
	public:
	bool Can(int u, int t) {
		if (u >= t - (int)sqrt(c * t)) return true;
		return false;
	}
	bool Check(int u) {
		memset(vis, 0, sizeof vis);
		vis[ d[1] = u ] = true;
		for (int i = 0; i <= r - 1; i++) {
			int t = 1;
			std::sort(d + 1, d + (1 << i) + 1);
			for (int j = 1; j <= (1 << i); j++) {
				int Now = d[j];
				t = std::max(t, Now - (int)sqrt(c * Now));
				while (t <= (1 << r) && vis[t]) t++;
				if (t > (1 << r)) return false;
				d[j + (1 << i)] = t;
				vis[t] = true;
			}
		}
		return true;
	}
	int greatestSeed(int rounds, int C) {
		n = 1 << rounds, c = C, r = rounds;
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Check(mid)) 
				l = mid + 1;
			else
				r = mid - 1;
		}
		return r;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 0; int Arg2 = 1; verify_case(0, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 1; int Arg2 = 6; verify_case(1, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 9; verify_case(2, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arg1 = 3; int Arg2 = 50; verify_case(3, Arg2, greatestSeed(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 15; int Arg1 = 180; int Arg2 = 9755; verify_case(4, Arg2, greatestSeed(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RPSTournament ___test;  
 	___test.run_test(4); 
	return 0;
}
// END CUT HERE

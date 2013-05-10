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

	Int64 f[500010][2], s[500010];
class PubTrivia {
	public:
	vector<int> gen(vector<int> x, int n, int G) {
		Int64 k = 0; vector<int> ret;
		for (int i = 0; i <= n - 1; i++) {
			ret.pb(x[k]);
			Int64 s = (k + 1) % x.size();
			x[k] = ((x[k] ^ x[s]) + 13) % G;
			k = s;
		}
		return ret;
	}
	vector<int> point, bound;

	long long maximumScore(int N, int tokensNeeded, vector <int> p, vector <int> b) {
		point = gen(p, N, 1001); bound = gen(b, N, 10001); s[0] = point[0];
		for (int i = 1; i <= N - 1; i++) s[i] = s[i - 1] + point[i];
		memset(f, -55, sizeof f);
		f[0][0] = f[0][1] = 0;
		for (int i = 1; i <= N; i++) {
			f[i][0] = max(f[i - 1][0], f[i - 1][1]) + point[i - 1];
			if (i >= tokensNeeded) {
				Int64 ret = f[i - tokensNeeded][1];
				if (i > tokensNeeded)
					ret = max(ret, max(f[i - tokensNeeded - 1][0], f[i - tokensNeeded - 1][1]) - point[i - tokensNeeded - 1]);
				f[i][1] = ret + bound[i - 1] + s[i - 1] - (i > tokensNeeded ? s[i - 1 - tokensNeeded] : 0);
			}
		}
		return max(f[N][0], f[N][1]);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 5; int Arr2[] = {1, 2, 3, 4, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 2, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 20LL; verify_case(0, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 3; int Arr2[] = {1, 2, 3, 4, 5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 0, 2, 5}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 16LL; verify_case(1, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 3; int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {7, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 98LL; verify_case(2, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 4; int Arr2[] = {998, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {9998, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); long long Arg4 = 1056LL; verify_case(3, Arg4, maximumScore(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	PubTrivia ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

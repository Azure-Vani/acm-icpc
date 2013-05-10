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
#define foreach(i, T) for(typeof((T).begin()) i = (T).begin(); i != (T).end(); ++i)

typedef long long Int64;

using namespace std; 

int n1, S1, S2, n2;
int f[2000000];

class SplitAndMergeGame {
	public:
	int minMoves(vector <int> startState, vector <int> finishState) {
		n1 = startState.size(), n2 = finishState.size();
		foreach(it, startState) S1 += *it;
		foreach(it, finishState) S2 += *it;
		if (S1 != S2) return -1;
		for (int i = 1; i < (1 << n1 + n2); i++) {
			int d = 0, v = 1;
			for (int j = 0; j <= n1 - 1; v += v, j++) if (i&v)
				d += startState[j], f[i] = max(f[i], f[i^v]);
			for (int j = 0; j <= n2 - 1; v += v, j++) if (i&v)
				d -= finishState[j], f[i] = max(f[i], f[i^v]);
			f[i] += (d == 0);
		}
		return n1 + n2 - f[(1 << n1 + n2) - 1] * 2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, minMoves(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(1, Arg2, minMoves(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4, 5, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 7, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(2, Arg2, minMoves(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(3, Arg2, minMoves(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(4, Arg2, minMoves(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int ScanInt(void) {
	int c, r = 0, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0';
	while ( isdigit(d = getchar())) r = r * 10 + d - '0';
	return c=='-'?-r:r;
}

int main(void) {
	SplitAndMergeGame ___test;  
	vector<int> a, b; int n;
	n = ScanInt(); for (int i = 1; i <= n; i++) a.pb(ScanInt());
	n = ScanInt(); for (int i = 1; i <= n; i++) b.pb(ScanInt());
	printf("%d\n", ___test.minMoves(a, b));
	return 0;
}
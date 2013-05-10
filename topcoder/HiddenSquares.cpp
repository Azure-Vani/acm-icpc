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

const int MAXN = 122;
const int inf = 1000000000;

bool rhash[MAXN][MAXN], dhash[MAXN][MAXN];
int down[MAXN][MAXN], Right[MAXN][MAXN];
vector<int> x, y;

class HiddenSquares {
	public:
	map<int, int> Mx, My;
	set<int> X, Y;

	int count(vector <int> x1, vector <int> y1, vector <int> x2, vector <int> y2) {
		int n = x1.size();
		foreach(it, x1) X.insert(*it); foreach(it, x2) X.insert(*it);
		foreach(it, y1) Y.insert(*it); foreach(it, y2) Y.insert(*it);
		int t = 0; x.pb(0), y.pb(0);
		foreach(it, X) Mx[*it] = ++t, x.pb(*it); t = 0;
		foreach(it, Y) My[*it] = ++t, y.pb(*it);
		for (int i = 0; i <= n - 1; i++) x1[i] = Mx[x1[i]], x2[i] = Mx[x2[i]];
		for (int i = 0; i <= n - 1; i++) y1[i] = My[y1[i]], y2[i] = My[y2[i]];
		for (int i = 0; i <= n - 1; i++) {
			for (int j = x1[i]; j < x2[i]; j++) rhash[j][y1[i]] = rhash[j][y2[i]] = true;
			for (int j = y1[i]; j < y2[i]; j++) dhash[x1[i]][j] = dhash[x2[i]][j] = true;
		}
		for (int i = x.size() - 1; i >= 1; i--)
			for (int j = y.size() - 1; j >= 1; j--) {
				if (rhash[i][j]) Right[i][j] = Right[i + 1][j] + x[i + 1] - x[i]; else Right[i][j]  = 0;
				if (dhash[i][j]) down[i][j] = down[i][j + 1] + y[j + 1] - y[j]; else down[i][j] = 0;
			}
		int cnt = 0;
		for (int i = x.size() - 1; i >= 1; i--)
			for (int j = y.size() - 1; j >= 1; j--) {
				for (int k = i + 1; k < (int)x.size(); k++) {
					int L = x[k] - x[i];
					if (!Y.count(y[j] + L)) continue;
					int D = My[y[j] + L];
					if (Right[i][j] >= L && Right[i][D] >= L && down[k][j] >= L && down[i][j] >= L)
						cnt++;
				}
			}
		return cnt;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,3,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 14; verify_case(0, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {4,4}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(1, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0,0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,3,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,4,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {3,4,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 0; verify_case(2, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {453453463,453453500,453453495,453453512,453453478,453453489,
 453453466,453453500,453453498,453453510,453453472,453453512,
 453453519,453453514,453453521,453453518,453453523,453453517,
 453453466,453453525,453453496,453453495,453453463,453453461,
 453453460,453453522,453453471,453453468,453453479,453453517,
 453453485,453453518,453453499,453453464,453453494}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {364646438,364646402,364646449,364646438,364646415,364646401,
 364646446,364646416,364646456,364646414,364646463,364646407,
 364646436,364646450,364646421,364646411,364646414,364646419,
 364646445,364646427,364646405,364646442,364646418,364646464,
 364646457,364646463,364646432,364646426,364646444,364646431,
 364646450,364646418,364646434,364646458,364646402}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {453453488,453453510,453453525,453453523,453453493,453453500,
 453453470,453453511,453453499,453453521,453453518,453453524,
 453453523,453453523,453453524,453453523,453453525,453453519,
 453453473,453453526,453453511,453453517,453453470,453453464,
 453453511,453453524,453453516,453453516,453453492,453453524,
453453513,453453522,453453520,453453505,453453512}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {364646460,364646454,364646462,364646466,364646464,364646455,
 364646457,364646461,364646457,364646450,364646466,364646453,
 364646441,364646451,364646460,364646461,364646446,364646464,
 364646447,364646460,364646454,364646450,364646444,364646466,
 364646458,364646466,364646455,364646442,364646462,364646435,
 364646464,364646444,364646455,364646459,364646430}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 124; verify_case(3, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	HiddenSquares ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

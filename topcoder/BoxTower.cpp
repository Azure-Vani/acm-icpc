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
#define Set(s, i) ((s) ^ (1 << (i)))

typedef long long Int64;

using namespace std; 

const int MAXN = 15;
const int MAXM = 1 << MAXN;

int f[MAXN + 10][3][MAXM + 10];

class BoxTower {
	public:
	int tallestTower(vector <int> x, vector <int> y, vector <int> z) {
		int n = x.size(), m = (1 << (n)) - 1;
		memset(f, 0, sizeof f);
		for (int i = 0; i < n; i++) {
			f[i][0][1 << i] = x[i];
			f[i][1][1 << i] = y[i];
			f[i][2][1 << i] = z[i];
		}
		for (int now = 1; now < m; now++) {
			for (int i = 0; i < n; i++) if ((1 << i) & now) {
				for (int flag = 0; flag < 3; flag++) {
					int w, h;
					if (flag == 0) w = y[i], h = z[i];
					if (flag == 1) w = x[i], h = z[i];
					if (flag == 2) w = x[i], h = y[i];
					for (int j = 0; j < n; j++) if (!((1 << j) & now)) {
						for (int F = 0; F < 3; F++) {
							int w2, h2;
							if (F == 0) w2 = y[j], h2 = z[j];
							if (F == 1) w2 = x[j], h2 = z[j];
							if (F == 2) w2 = x[j], h2 = y[j];
							if ((w2 <= w && h2 <= h) || (w2 <= h && h2 <= w)) {
								f[j][F][now | (1 << j)] = max(f[j][F][now | (1 << j)], (f[i][flag][now] + x[j] + y[j] + z[j] - w2 - h2));
							}
						}
					}
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 3; j++)
				for (int l = 1; l <= m; l++)
					ret = max(ret, f[i][j][l]);
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {10, 50, 40, 20, 30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 50, 40, 20, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 50, 40, 20, 30}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 150; verify_case(0, Arg3, tallestTower(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {20, 30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 30; verify_case(1, Arg3, tallestTower(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {20, 30}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {20, 33}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {20, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 33; verify_case(2, Arg3, tallestTower(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 12}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 110; verify_case(3, Arg3, tallestTower(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	BoxTower ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

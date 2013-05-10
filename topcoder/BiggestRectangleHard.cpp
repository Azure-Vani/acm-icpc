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

typedef long long Int64;

using namespace std; 

bool f[2][41][41][81][81];

class BiggestRectangleHard {
	public:
	int findArea(vector <int> lengths) {
		memset(f, 0, sizeof f);
		int n = lengths.size();
		int now = 1, next = 0;
		f[now][0][0][0][0] = true;
		for (int i = 0; i <= n - 1; i++)  {
			int L = lengths[i];
			memset(f[next], 0, sizeof next);
			for (int x1 = 0; x1 <= 40; x1++) 
				for (int x2 = 0; x2 <= 40; x2++)
					for (int y1 = 0; y1 <= 80; y1++) 
						for (int y2 = 0; y2 <= 80; y2++) if (f[now][x1][x2][y1][y2]) {
							f[next][x1][x2][y1][y2] = true;
							if (x1 + L <= 40) f[next][x1 + L][x2][y1][y2] = true;
							if (x2 + L <= 40) f[next][x1][x2 + L][y1][y2] = true;
							if (y1 + L <= 80) f[next][x1][x2][y1 + L][y2] = true;
							if (y2 + L <= 80) f[next][x1][x2][y1][y2 + L] = true;
						}
			swap(next, now);
		}
		int ret = -1;
		for (int i = 1; i <= 40; i++) for (int j = 1; j <= 80; j++) if (f[now][i][i][j][j])
			ret = std::max(ret, i * j);
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 3, 3, 4, 5, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; verify_case(0, Arg1, findArea(Arg0)); }
	void test_case_1() { int Arr0[] = {9, 9, 5, 6, 2, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, findArea(Arg0)); }
	void test_case_2() { int Arr0[] = {3, 4, 7, 8, 10, 2, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 70; verify_case(2, Arg1, findArea(Arg0)); }
	void test_case_3() { int Arr0[] = {9, 2, 7, 9, 4, 9, 7, 10, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 224; verify_case(3, Arg1, findArea(Arg0)); }
	void test_case_4() { int Arr0[] = {9, 9, 10, 7, 7, 8, 7, 5, 8, 6, 9, 7, 7, 10, 9, 6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 961; verify_case(4, Arg1, findArea(Arg0)); }
	void test_case_5() { int Arr0[] = {2, 6, 4, 10, 2, 8, 1, 8, 2, 1, 4, 8, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 272; verify_case(5, Arg1, findArea(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	BiggestRectangleHard ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

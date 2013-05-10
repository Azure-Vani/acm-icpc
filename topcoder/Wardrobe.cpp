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

int f[101], n;
class Wardrobe {
	public:
	int countUnscrewedHoles(vector <int> a) {
		std::sort(a.begin(), a.end()), n = a.size();
		for (int i = n - 1; i >= 0; i--) {
			int &tmp = f[i];
			for (int j = i; j < n; j++) {
				tmp = std::max(tmp, f[j + 1]);
				for (int d = 1; d <= j - i + 1; d++) if (a[i + d - 1] + 1 < a[j - d + 1]) {
					bool ok = true;
					for (int k = i; k <= j - d; k++) if (a[k] + 1 < a[k + d]) ok = false;
					if (ok) tmp = std::max(tmp, f[j + 1] + d);
				}
			}
		}
		return f[0];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, countUnscrewedHoles(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 2, 3, 2, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, countUnscrewedHoles(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 3, 4, 2, 5, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countUnscrewedHoles(Arg0)); }
	void test_case_3() { int Arr0[] = {12, 14, 12, 25, 15, 22, 19, 13, 26, 19, 24, 18, 14}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, countUnscrewedHoles(Arg0)); }
	void test_case_4() { int Arr0[] = {26, 26, 26, 14, 13, 28, 27, 15, 27, 28, 28, 26}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(4, Arg1, countUnscrewedHoles(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	Wardrobe ___test;  
 	___test.run_test(4); 
	return 0;
}
// END CUT HERE

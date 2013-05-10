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

int n; vector<int> a;
class StoneGameStrategist {
	public:
	bool Sg(const vector<int> &a) {
		int ret = 0;
		for (int i = 0; i <= n - 1; i++) 
			if ((i&1) != (n&1)) 
				ret ^= a[i];
		return ret;
	}
	string play(vector <int> piles) {
		a.clear();
		n = piles.size(); a.pb(piles[0]);
		for (int i = 1; i <= n - 1; i++) a.pb(piles[i] - piles[i - 1]);
		if (!Sg(a)) return string("YOU LOSE");
		for (int k = 1; k <= 1000; k++) {
			for (int i = 0; i <= n - 1; i++) if (a[i] >= k) {
				if ((i&1) == (n&1)) a[i + 1] += k; else a[i] -= k;
				if (!Sg(a)) {
					stringstream sout;
					sout <<"TAKE "<<k<<" STONES "<<"FROM"<<" PILE "<<i;
					return sout.str();
				}
				if ((i&1) == (n&1)) a[i + 1] -= k; else a[i] += k;
			}
		}
		return string("Error");
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YOU LOSE"; verify_case(0, Arg1, play(Arg0)); }
	void test_case_1() { int Arr0[] = {6,12}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "TAKE 6 STONES FROM PILE 1"; verify_case(1, Arg1, play(Arg0)); }
	void test_case_2() { int Arr0[] = {3,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "TAKE 3 STONES FROM PILE 0"; verify_case(2, Arg1, play(Arg0)); }
	void test_case_3() { int Arr0[] = {2, 6, 8, 11, 13, 18}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "TAKE 2 STONES FROM PILE 0"; verify_case(3, Arg1, play(Arg0)); }
	void test_case_4() { int Arr0[] = {32,136,251,369,403,593,624,657,729,731,769}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "YOU LOSE"; verify_case(4, Arg1, play(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	StoneGameStrategist ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

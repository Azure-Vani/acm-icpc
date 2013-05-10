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

const int MAXN = 50010;
vector<Int64> a, b;
Int64 sum_pow[MAXN], sum[MAXN];

class RandomFights {
	public:
	void gen(vector<int>& a, vector<Int64>& r, int n) {
		int m = a.size();
		int j = 0; r.pb(0);
		for (int i = 0; i <= n - 1; i++) {
			r.pb(a[j]);
			int s = (j + 1) % m;
			a[j] = ((a[j] ^ a[s]) + 13) % 49999;
			j = s;
		}
	}
	double expectedNrOfPoints(vector <int> A, vector <int> B, int n) {
		gen(A, a, n); gen(B, b, n);
		std::sort(a.begin(), a.end()); std::sort(b.begin(), b.end());
		if (a == b) return 0;
		double ret = 0;
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + b[i], sum_pow[i] = sum_pow[i - 1] + b[i] * b[i];
		for (Int64 i = 1, j = 1; i <= n; i++) {
			while (j <= n && b[j] < a[i]) j++;
			Int64 tmp1 = (Int64) a[i] * a[i] * (j - 1ll) - 2ll * a[i] * (sum[j - 1]) + sum_pow[j - 1];
			Int64 tmp2 = (Int64) a[i] * a[i] * (n - j + 1) - 2ll * a[i] * (sum[n] - sum[j - 1]) + (sum_pow[n] - sum_pow[j - 1]);
			tmp1 -= tmp2;
			ret += (double) tmp1 / (double) n;
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; double Arg3 = 4.0; verify_case(0, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arg3 = 0.0; verify_case(1, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {3,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; double Arg3 = 20.0; verify_case(2, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {45,35,236,2342,5543,21,32,2,6,23,24,23,41,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2345,45,2345,345}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50; double Arg3 = 1.2721986164E8; verify_case(3, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {34,3245,2534,53,53,46,346,246,346,2,624,624,6,245,6324,6542,624,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {345,234,523,4624,6,2456,345,634,634,7,3457,376,34,6234,62,523,52,35,32}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; double Arg3 = -9713701.714285715; verify_case(4, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1,2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 50000; double Arg3 = 0.0; verify_case(5, Arg3, expectedNrOfPoints(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RandomFights ___test;  
 	___test.run_test(5); 
	return 0;
}
// END CUT HERE

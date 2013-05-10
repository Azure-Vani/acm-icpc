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

const double eps = 0.000000001;

using namespace std; 

class ThreeBuses {
	public:
	double T, t1, t2, t3;
	double Cal(double W) {
		double w = T - W, X = t2, Y = t3;
		if (w <= 0) return 0;
		if (X + Y <= w) return X * Y;
		if (X < Y) std::swap(X, Y);
		if (w <= Y) return 0.5 * w * w;
		if (w <= X) return 0.5 * Y * (w + w - Y);
		return Y * (w - Y) + 0.5 * (X - (w - Y)) * (Y + w - X);
	}
#define f(l, r, L, R, M) ((L + R + 4.0 * M) / 6.0 * (r - l))
	double F(double l, double r, double fl, double fr, double fm) {
		double mid = (l + r) * 0.5, lmid = (l + mid) * 0.5, rmid = (mid + r) * 0.5, nl = Cal(lmid), nr = Cal(rmid);
		double now = f(l, r, fl, fr, fm), lnow = f(l, mid, fl, fm, nl), rnow = f(mid, r, fm, fr, nr);
		if (fabs(now - lnow - rnow) <= eps) return now; else return F(l, mid, fl, fm, nl) + F(mid, r, fm, fr, nr);
	}
	double getProbability(vector <int> wait, vector <int> travel, int timeLeft) {
		T = timeLeft;
		foreach(it, travel) T -= *it;
		double S = 1;
		foreach(it, wait) S *= *it;
		if (T < 0 || (T == 0 && S)) return 0.0;
		std::sort(wait.begin(), wait.end());
		t2 = wait[1], t3 = wait[2];
		if (!wait[0]) {
			if (!wait[1]){
				if (!wait[2]) {
					return 1.0;
				} else {
					return std::min(1.0, (double)T / wait[2]);
				}
			} else {
				return Cal(0) / (wait[1] * wait[2]);
			}
		}
		double C = F(0, wait[0], Cal(0), Cal(wait[0]), Cal(wait[0] * 0.5));
		return C / S;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {4321, 0, 3173}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; double Arg3 = 1.0; verify_case(0, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 15, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 35; double Arg3 = 1.0; verify_case(1, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1, 100, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 10, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 52; double Arg3 = 0.21; verify_case(2, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {100, 100, 70}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 47; double Arg3 = 0.020281904761904737; verify_case(3, Arg3, getProbability(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	ThreeBuses ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

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

const Int64 inf = 1000000000000000000ll;

Int64 S;
struct pack {
	Int64 s, v;
}a, b;

class MonthlyPayment {
	public:
	void Sin(string st, long long &a) {
		stringstream sin(st);
		sin >>a;
	}
	Int64 Opt(Int64 t, pack a) {
		if ((double)a.v / (double)a.s >= 10) return t * 10;
		Int64 div = t / a.s, res = t % a.s;
		Int64 ret1 = div * a.v + res * 10;
		Int64 ret2 = (div + 1) * a.v;
		return std::min(ret1, ret2);
	}
	long long minimalPayment(string totalSMS, string pack1, string pay1, string pack2, string pay2) {
		Sin(totalSMS, S); Sin(pack1, a.s); Sin(pay1, a.v); Sin(pack2, b.s); Sin(pay2, b.v);
		Int64 ret = inf;
		for (int i = 1; i <= 2; i++) {
			for (Int64 k = 0; k <= 2000000 && k * a.s <= S; k++) {
				ret = std::min(ret, a.v * k + Opt(S - k * a.s, b));
			}
			swap(a, b);
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "92"; string Arg1 = "10"; string Arg2 = "90"; string Arg3 = "20"; string Arg4 = "170"; long long Arg5 = 790LL; verify_case(0, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { string Arg0 = "90"; string Arg1 = "10"; string Arg2 = "90"; string Arg3 = "20"; string Arg4 = "170"; long long Arg5 = 770LL; verify_case(1, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { string Arg0 = "99"; string Arg1 = "10"; string Arg2 = "90"; string Arg3 = "20"; string Arg4 = "170"; long long Arg5 = 850LL; verify_case(2, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { string Arg0 = "10"; string Arg1 = "1"; string Arg2 = "11"; string Arg3 = "20"; string Arg4 = "300"; long long Arg5 = 100LL; verify_case(3, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { string Arg0 = "0"; string Arg1 = "10"; string Arg2 = "80"; string Arg3 = "50"; string Arg4 = "400"; long long Arg5 = 0LL; verify_case(4, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { string Arg0 = "28"; string Arg1 = "1"; string Arg2 = "10"; string Arg3 = "1"; string Arg4 = "8"; long long Arg5 = 224LL; verify_case(5, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_6() { string Arg0 = "450702146848"; string Arg1 = "63791"; string Arg2 = "433956"; string Arg3 = "115281"; string Arg4 = "666125"; long long Arg5 = 2604279739220LL; verify_case(6, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_7() { string Arg0 = "45"; string Arg1 = "6"; string Arg2 = "12"; string Arg3 = "7"; string Arg4 = "14"; long long Arg5 = 90LL; verify_case(7, Arg5, minimalPayment(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	MonthlyPayment ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

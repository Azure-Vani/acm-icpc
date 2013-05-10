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
vector<Int64> a;
int n;Int64 m, res[10];

class MatchNumbersHard {
	public:
	
	Int64 Cal(Int64 rem, const vector<Int64> &a, bool flag = false) {
		if (!flag) {
			Int64 min = inf;
			for (int i = 0; i < n; i++) if (min > a[i]) {
				min = a[i];
			}
			return rem / min;
		}
		Int64 ret = 0;
		for (int i = 1; i < n; i++) if (a[i] <= rem) {
			ret = std::max(Cal(rem - a[i], a) + 1, ret);
		}
		return ret;
	}

	vector <string> maxNumber(vector <string> matches, string _n) {
		a.clear(); n = matches.size();
		stringstream sout(_n); sout >>m;
		for (int i = 0; i < n; i++) {
			Int64 tmp;
			sout.clear();
			sout.str(matches[i]);
			sout >>tmp;
			a.pb(tmp);
		}
		bool Fail = true;
		for (int i = 1; i < n; i++) if (a[i] <= m) {
			Fail = false; break;
		}
		if (Fail) {
			vector<string> R(3, "");
			if (a[0] <= m) R[0] = "1", R[1] = R[2] = "0"; else R[0] = "0";
			return R;
		}
		Int64 D = Cal(m, a, true), back = m;
		memset(res, 0, sizeof res);
		for (int i = n - 1; i >= 0; i--) {
			Int64 l = 0, r = m / a[i];
			while (l <= r) {
				Int64 mid = (l + r) >> 1;
				if (mid + Cal(m - mid * a[i], a, mid == 0 && m == back) == D) {
					l = mid + 1;
				} else {
					r = mid - 1;
				}
			}
			res[i] = r;
			m -= a[i] * r;
			D -= r;
		}
		Int64 ret = 0; string head, tail, num;
		for (int i = 0; i < n; i++) ret += res[i];
		stringstream S; S <<ret;
		int j = 50;
		for (int i = 0, k; i < n && j; i++) {
			if (j - res[i] >= 0) j -= res[i], k = res[i]; else k = j, j = 0;
			tail.append(k, (char)(i + '0'));
		}
		j = 50;
		for (int i = n - 1, k; i >= 0 && j; i--) {
			if (j - res[i] >= 0) j -= res[i], k = res[i]; else k = j, j = 0;
			head.append(k, (char)(i + '0'));
		}
		reverse(tail.begin(), tail.end());
		vector<string> R; R.pb(S.str()); R.pb(head); R.pb(tail);
		return R;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"6","7","8"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "21"; string Arr2[] = {"3", "210", "210" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1","7","8"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "21"; string Arr2[] = {"15", "100000000000000", "100000000000000" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"1","1","1","1","1","1","1","1","1","1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "923372036854775807"; string Arr2[] = {"923372036854775807", "99999999999999999999999999999999999999999999999999", "99999999999999999999999999999999999999999999999999" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1","923372036854775807"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "923372036854775807"; string Arr2[] = {"1", "1", "1" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"1","923372036854775806"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "923372036854775807"; string Arr2[] = {"2", "10", "10" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"1","5","10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "10"; string Arr2[] = {"6", "100000", "100000" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_6() { string Arr0[] = {"1","923372036854775807"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "923372036854775806"; string Arr2[] = {"1", "0", "0" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(6, Arg2, maxNumber(Arg0, Arg1)); }
	void test_case_7() { string Arr0[] = {"1", "835810052671059340", "835810052167105935", "658100521671059340", "835810055648722340"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "958100521671059340"; string Arr2[] = {"1", "0", "0" }; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(7, Arg2, maxNumber(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	MatchNumbersHard ___test;  
 	___test.run_test(7); 
	return 0;
}
// END CUT HERE

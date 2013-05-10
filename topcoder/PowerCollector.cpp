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
#define rep(i,l,r) for(Int64 i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

typedef long long Int64;

using namespace std; 

const Int64 inf = 1000000000000000000ll;

class PowerCollector { public:

	Int64 Pow(Int64 a, Int64 b) {
		Int64 ret = 1;double y = 1;
		for (Int64 i = 1; i <= b; i++) {
			ret *= a;
			y *= a;
			if (y > inf) return inf + 1;
		}
		return ret;
	}

	Int64 R(double x, Int64 e, Int64 n) {
		Int64 ret = (Int64)ceil(x);
		while (Pow(ret, e) > n) ret--;
		return ret;
	}

	bool isPrime(Int64 n) {
		for (Int64 i = 2; i * i <= n; i++) if (!(n % i)) return false;
		return true;
	}

	Int64 Count(Int64 n, Int64 p) {
		register Int64 ret = 1, tmp = 0;
		for (Int64 i = 2; i <= p; i++) {
			if (!isPrime(i)) continue;
			tmp = R(pow(n, 1.0 / (double)i), i, n);
			if (tmp == 1) break;
			ret += tmp - Count(tmp, i - 1);
		}
		return ret;
	}

	string countPowers(string N) {
		Int64 n = 0;
		for (Int64 i = 0; i <= (Int64)N.length() - 1; i++) n = n * 10 + N[i] - '0';
		if (n <= 3) return "1";
		 Int64 p = (Int64)floor(log((double)n) / log(2.0)) + 1;
		Int64 ret = Count(n, p);
		char ch[20]; sprintf(ch, LL, ret);
		return (string)ch;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(Int64 Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string prInt64_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(Int64 Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "2199023255552"; string Arg1 = "1496144"; verify_case(0, Arg1, countPowers(Arg0)); }
	void test_case_1() { string Arg0 = "36"; string Arg1 = "9"; verify_case(1, Arg1, countPowers(Arg0)); }
	void test_case_2() { string Arg0 = "1000000000000000000"; string Arg1 = "1001003332"; verify_case(2, Arg1, countPowers(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	PowerCollector ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

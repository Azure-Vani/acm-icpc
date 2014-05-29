#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstring>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

int mod = 1000000007;

long long fib[100]; int L;

class FibonacciXor {
	public:
	inline long long pow(int n) {
		long long ret = 1, a = 2; n -= 2;
		while (n) {
			if (n & 1) ret = ret * a % mod;
			n >>= 1;
			a *= a; a %= mod;
		}
		return ret;
	}
	long long Cal(long long l, long long r) {
		if (l > r) return 0;
		int t1 = lower_bound(fib + 2, fib + L + 1, l) - fib;
		int t2 = upper_bound(fib + 2, fib + L + 1, r) - fib - 1;
		long long ret = 0;
		if (t1 <= t2) {
			ret = Cal(l - fib[t1 - 1] + 1, fib[t1] - 1 - fib[t1 - 1]) + Cal(1, r - fib[t2]);
			ret %= mod;
			for (int i = t1; i < t2; i++) {
				ret += Cal(fib[i] + 1 - fib[i - 1], fib[i + 1] - 1 - fib[i - 1]);
				ret %= mod;
			}
			if (l < fib[t1] && (fib[t1] - l) % 2 == 1) {
				ret += pow(t1 - 1);
				ret %= mod;
			}
			if (r >= fib[t2] && (r - fib[t2] + 1) % 2 == 1) {
				ret += pow(t2);
				ret %= mod;
			}
			for (int i = t1; i < t2; i++) if ((fib[i + 1] - fib[i]) % 2 == 1) {
				ret += pow(i);
				ret %= mod;
			}
		} else {
			if ((r - l + 1) % 2 == 1) {
				ret += pow(t2);
				ret %= mod;
			}
			ret += Cal(l - fib[t2], r - fib[t2]);
		}
		return ret;
	}
	int find(long long A, long long B) {
		fib[1] = 1;
		for (L = 2; L; L++) {
			fib[L] = fib[L - 1] + fib[L - 2];
			if (fib[L] > 1000000000000000ll) break;
		}
		return Cal(A, B);
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 2LL; int Arg2 = 3; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 3LL; long long Arg1 = 10LL; int Arg2 = 25; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 1LL; long long Arg1 = 1000000000000000LL; int Arg2 = 780431495; verify_case(2, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	FibonacciXor ___test;
	___test.run_test(1);
	return 0;
}
// END CUT HERE

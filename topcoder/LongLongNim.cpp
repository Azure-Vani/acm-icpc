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

const int MAXN = (1 << 22) + 100;

bool f[MAXN];
int sum[MAXN], vis[MAXN];;

class LongLongNim {
	public:
	int numberOfWins(int maxN, vector <int> moves) {
		int k = 1, p = 0, s = 0;
		f[0] = true;
		for (int i = 1; i <= std::min(21, maxN); i++) {
			f[i] = true;
			foreach(it, moves) if (*it <= i && f[i - *it]) f[i] = false;
			k |= (f[i] << i);
			s += !f[i];
		}/*
		for (int i = 21, j = 21 + 58; i >= 0; i--, j--) if (f[i] != f[j]){
			assert(0);
		}*/
		foreach(it, moves) {
			p |= 1 << (21 - *it + 1);
		}
		if (maxN <= 21) return maxN - s;
		int Len = 0;
		do {
			Len++;
			int d = (p & k);
			vis[k] = Len;
			sum[Len] = sum[Len - 1];
			k >>= 1;
			if (d == 0) k |= 1 << 21; else sum[Len]++; 
		}while (!vis[k]);
		maxN -= 21;
		int begin = vis[k]; Len -= begin - 1;
		return maxN + 21 - s - (maxN - begin + 1)/ Len * (sum[Len + begin - 1] - sum[begin - 1]) - sum[begin + (maxN - begin + 1) % Len - 1];
	}
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 987654321; int Arr1[] = {3, 7, 8, 12, 13, 17, 19}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 301783264; verify_case(0, Arg2, numberOfWins(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 999; int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 499; verify_case(1, Arg2, numberOfWins(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 567567865; int Arr1[] = {2, 6, 7, 11, 12, 16, 17, 20, 22}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 162162246; verify_case(2, Arg2, numberOfWins(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6543; int Arr1[] = {2,4,7,11,20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1637; verify_case(3, Arg2, numberOfWins(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	LongLongNim ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

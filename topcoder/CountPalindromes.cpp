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

const int MAXN = 52, MAXM = 17;
const int Mod = 835454957;

bool vis[103][2][MAXN * MAXM];
int n, f[103][2][MAXN * MAXM], cur;
vector<string> a;
map<string, int> M;

class CountPalindromes {
	public:
	unsigned int Mismatch(const string& a, const string& b) {
		int L1 = a.length(), L2 = b.length(), i = 0;
		while (i < std::min(L1, L2) && a[i] == b[i]) i++;
		return i;
	}
	bool isPali(const string& st) {
		string ss = st; reverse(ss.begin(), ss.end());
		return st == ss;
	}
	int Dfs(int res, int g, const string& st) {
		if (res < 0) return 0; int sid;
		if (!M.count(st)) sid = M[st] = ++cur; else sid = M[st];
		int &ret = f[res][g][sid]; bool &tmp = vis[res][g][sid];
		if (tmp) return ret; tmp = true;
		ret = isPali(st);
		for (int i = 0; i <= n - 1; i++) {
			string next = a[i]; if (!g) reverse(next.begin(), next.end());
			if (Mismatch(next, st) == next.length()) {
				ret += Dfs(res - next.length() - 1, g, st.substr(next.length(), st.length() - next.length()));
			} else if (Mismatch(next, st) == st.length()) {
				ret += Dfs(res - next.length() - 1, !g, next.substr(st.length(), next.length() - st.length()));
			}
			ret %= Mod;
		}
		return ret;
	}
	int count(vector <string> words, int k) {
		n = words.size(), a = words;
		int ret = Dfs(k + 1, 0, "");
		return ret ? ret - 1 : Mod - 1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"tragic","cigar"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; int Arg2 = 1; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"z","zz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 5; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"aba","acaba","baca","cac","b","c","a"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 70; int Arg2 = 370786966; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"hello"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; int Arg2 = 0; verify_case(3, Arg2, count(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	CountPalindromes ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

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
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,r) for(int i = 1; i <= r; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

int f[55 * 55][55 * 55], inp[55 *55], d[55 * 55], dis[55 *55], oup[55];

vector<string> a,b,c;

class ScotlandYard {
	public:
		bool ok(int l1, int l2, int l3, int l4) {
			return (a[l1][l3] == 'Y' && a[l2][l4] == 'Y') || (b[l1][l3] == 'Y' && b[l2][l4] == 'Y') || (c[l1][l3] == 'Y' && c[l2][l4] == 'Y');
		}
	int maxMoves(vector <string> taxi, vector <string> bus, vector <string> metro) {
		a = taxi, b = bus, c = metro;
		memset(f, 0, sizeof f);
		memset(inp, 0, sizeof inp);
		memset(dis, 0, sizeof dis);
		memset(oup, 0, sizeof oup);
		int n = taxi.size();
		REP(l1,0,n-1) REP(l2,0,n-1) REP(l3,0,n-1) REP(l4,0,n-1) if (! (l1 == l2 && l3 == l4)) {
			if (taxi[l1][l2] == 'Y' || bus[l1][l2] == 'Y' || metro[l1][l2] == 'Y') oup[l1] = 1;
			if (ok(l1,l2,l3,l4) || (l3 != l4 && ok(l1,l1,l3,l4)) || (l3 != l4 && ok(l2,l2,l3,l4)))
				f[l1 * 50 + l2][l3 * 50 + l4] = true, inp[l3 * 50 + l4]++;
		}
		int N = (n - 1) * 50 + n, head = 1, tail = 0;
		REP(i,0,N-1) if (!inp[i]) d[++tail] = i;
		while (head <= tail) {
			int now = d[head++];
			for (int i = 0; i < N; i++) if (f[now][i]) {
				if (!--inp[i]) d[++tail] = i;
				dis[i] = max(dis[i], dis[now] + 1);
			}
		}
		int Ans = 0;
		REP(i,0,N-1) {if (inp[i]) return -1; Ans = max(Ans, dis[i] + (oup[i % 50] || oup[i / 50]));}
		return Ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
 "NNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(0, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"NYY",
 "NNN",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(1, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"NYYY",
 "YNYY",
 "YYNY",
 "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(2, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"NNY",
 "NNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYN",
 "NNY",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "YNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(3, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"NNN",
 "YNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "YNN",
 "YNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "YYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(4, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"NNNNNNNNNN", "YNNNNNNNNN", "YNNNNNNNNN", "YNNNNNNNNN", "NNNNNYYNNN", "NNNNNNYNYN", "NNNNNNNNNN", "YNNNNNNNNN", "NNNNNNNNNN", "NNNNNYYNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); 
		string Arr1[] =  {"NNNNNYNNNN", "NNNNNNNNNN", "NNNNNNNNNN", "NNNNNYNNNN", "NNNNNNNNNN", "NNNNYNNNNN", "NNNNNNNNNN", "NNNNNNYNNY", "NNNNYNNNNN", "NNYNNNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = 
		 {"NNNNNNNNNN", "YNNNNNNNNN", "NNNNYNNNNN", "NNNNNNNNNN", "NNNNNNNNNN", "YYNYNNNNNN", "NNNNNNNNNN", "NNNNNNYNNY", "NNYYNNNNNN", "NNNNNNNNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(5, Arg3, maxMoves(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	ScotlandYard ___test;  
 	___test.run_test(5); 
	return 0;
}
// END CUT HERE

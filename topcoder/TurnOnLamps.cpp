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
#define REP(i,l,r) for(inti = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 100;

struct Edge {
	int y, isImportant, state; Edge *next;
	Edge(int y, int isImportant, int state, Edge *next):y(y), isImportant(isImportant), state(state), next(next){}
}*a[MAXN];

int f[MAXN];

class TurnOnLamps {
	public:
	void Dfs(int u) {
		for (Edge *p = a[u]; p; p = p->next) Dfs(p->y);
		for (Edge *p = a[u]; p; p = p->next) {
			f[u] += f[p->y];
			if (p->isImportant && (p->state ^ (f[p->y] & 1)) == 0) f[u]++;
		}
	}
	int minimize(vector <int> roads, string initState, string isImportant) {
		int n = roads.size() + 1; memset(a, 0, sizeof a); memset(f, 0, sizeof f);
		for (int i = 0; i < n - 1; i++) {
			a[roads[i]] = new Edge(i + 1, isImportant[i] == '1', initState[i] == '1', a[roads[i]]);
		}
		Dfs(0);
		int Ans = f[0];
		return (Ans >> 1) + (Ans & 1);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "0001"; string Arg2 = "0111"; int Arg3 = 1; verify_case(0, Arg3, minimize(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "0000"; string Arg2 = "0111"; int Arg3 = 2; verify_case(1, Arg3, minimize(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,0,1,1,4,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "000100"; string Arg2 = "111111"; int Arg3 = 2; verify_case(2, Arg3, minimize(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,1,1,4,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "100100"; string Arg2 = "011101"; int Arg3 = 2; verify_case(3, Arg3, minimize(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,0,2,2,3,1,6,3,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "010001110"; string Arg2 = "000110100"; int Arg3 = 1; verify_case(4, Arg3, minimize(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0,0,1,2,4,4,6,1,2,5,2,8,8,3,6,4,14,7,18,14,11,7,1,12,7,5,18,23,0,14,11,10,2,2,6,1,30,11,9,12,5,35,25,11,23,17,14,45,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "0000000000010000000000000010000010100000000000000"; string Arg2 = "1010111111111011011111000110111111111111111110111"; int Arg3 = 14; verify_case(5, Arg3, minimize(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	TurnOnLamps ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

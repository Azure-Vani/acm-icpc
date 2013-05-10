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

const int MAXN = 50;
int a[MAXN][MAXN], n, c[MAXN][MAXN], s, t;
int vis[MAXN], cur, level[MAXN], d[MAXN];

class Terrorists {
	public:
	bool Bfs(void) {
		memset(level, -1, sizeof level);
		int head = 1, tail = 1; d[1] = s; level[s] = 0;
		while (head <= tail) {
			int now = d[head++];
			for (int i = 0; i < n; i++) if (level[i] == -1 && c[now][i]) 
				level[d[++tail] = i] = level[now] + 1;
		}
		return level[t] != -1;
	}
	int Dfs(int u, int s) {
		if (u == t) return s;
		int r = 0;
		for (int i = 0; i < n && r < s; i++) if (c[u][i] && level[i] == level[u] + 1) {
			int t = Dfs(i, std::min(s - r, c[u][i]));
			c[u][i] -= t, c[i][u] += t, r += t;
		}
		if (!r) level[u] = -1;
		return r;
	}
	int Flow(void) {
		int tmp, r = 0;
		while (Bfs()) while (tmp = Dfs(s, 1000000000)) r += tmp;
		return r;
	}
	int requiredCost(vector <string> roads) {
		n = roads.size();
		for (int i = 0; i <= n - 1; i++) for (int j = 0; j <= n - 1; j++) a[i][j] = roads[i][j] - '0';
		int ret = 1000000000;
		for (s = 0; s <= n - 1; s++) for (t = s + 1; t <= n - 1; t++) {
			memcpy(c, a, sizeof a);
			ret = std::min(ret, Flow());
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0911",
 "9011",
 "1109",
 "1190"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, requiredCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"0399",
 "3033",
 "9309",
 "9390"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(1, Arg1, requiredCost(Arg0)); }
	void test_case_2() { string Arr0[] = {"030900",
 "304120",
 "040174",
 "911021",
 "027207",
 "004170"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(2, Arg1, requiredCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"044967263",
 "409134231",
 "490642938",
 "916036261",
 "634306024",
 "742660550",
 "229205069",
 "633625604",
 "318140940"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 27; verify_case(3, Arg1, requiredCost(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	Terrorists ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

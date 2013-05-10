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

int f[100], len[100], n;
int Min[100], Max[100];

int find(int x) {
	if (x == f[x]) return x;
	int ret = find(f[x]);
	len[x] += len[f[x]];
	f[x] = ret;
	return ret;
}
int gcd(int a, int b) {
	if (!b) return a; else return gcd(b, a % b);
}

class MergingGraph {
	public:
	int distanceToCycle(vector <string> adj) {
		n = adj.size();
		int d = 0, OK = false;
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 0, y; i <= n - 1; i++) {
			stringstream sin(adj[i]);
			while (sin >>y) {
				OK =true;
				int x = i + 1; y++;
				int fx = find(x), fy = find(y);
				if (fx != fy) {
					f[fx] = fy;
					len[fx] = len[y] - len[x] + 1;
				} else {
					int k = abs(len[y] - len[x] + 1);
					if (!k) continue;
					d = gcd(d, k);
				}
			}
		}
		if (!OK) return n;
		if (!d) {
			memset(Min, 60, sizeof Min);
			for (int i = 1; i <= n; i++) {
				int t = find(i);
				Min[t] = std::min(Min[t], len[i]);
				Max[t] = std::max(Max[t], len[i]);
			}
			int ret = 0;
			for (int i = 1; i <= n; i++) {
				if (find(i) == i)
					ret += Max[i] - Min[i];
			}
			return n - ret;
		}
		return n - d;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1 1", "2", "0 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, distanceToCycle(Arg0)); }
	void test_case_1() { string Arr0[] = {"0 1 1", "2", "0 0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, distanceToCycle(Arg0)); }
	void test_case_2() { string Arr0[] = {"1", "", "3", ""}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, distanceToCycle(Arg0)); }
	void test_case_3() { string Arr0[] = {"2", "5 4", "", "0", "0", "0 0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, distanceToCycle(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	MergingGraph ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

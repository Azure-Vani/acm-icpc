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

const int MAXN = 100010;

bool vis[6][MAXN];
double w[1 << 6];
int n, m, sum[6], b[1 << 6], num[1 << 6];

bool cmp(int a, int b) {
	return w[a] > w[b];
}
class BerryPacker {
	public:
	double bestPacking(vector <int> first, vector <int> period, int berries) {
		n = berries, m = first.size();
		for (int i = 0; i < m; i++) {
			for (int j = first[i] + 1; j <= n; j += period[i]) 
				vis[i][j] = true;
		}
		double ret = 0;
		for (int L = 1; L <= n; L++) {
			int now = 0;
			for (int i = 0; i <= m - 1; i++) if (vis[i][L]) {
				now |= (1 << i);
				sum[i]++;
			}
			b[now]++;
			if (L * 9 < n) continue;
			for (int i = 0; i <= (1 << m) - 1; i++) {
				int tmp = i; w[i] = 0; num[i] = i;
				while (tmp) {
					int k = __builtin_ctz(tmp);
					tmp -= tmp & - tmp;
					if (sum[k]) w[i] += (double) L / (double) sum[k];
				}
			}
			std::sort(num, num + (1 << m), cmp);
			double Cal = 0;
			for (int i = 0, res = n - L; i <= (1 << m) - 1; i++) {
				int t = num[i];
				int u = std::min(res, b[t] * 8);
				Cal += w[t] * (u + b[t]), res -= u;
			}
			ret = std::max(ret, Cal);
		}
		return ret / (double) m;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3, 4, 549}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] =  {3, 5, 9, 11, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 550; double Arg3 = 969.6; verify_case(0, Arg3, bestPacking(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; double Arg3 = 9.0; verify_case(1, Arg3, bestPacking(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {2,5,9,25}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,3,11,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 100; double Arg3 = 251.50649350649354; verify_case(2, Arg3, bestPacking(Arg0, Arg1, Arg2)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	BerryPacker ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

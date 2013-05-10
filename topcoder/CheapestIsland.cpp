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
#include <iterator>
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
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)
#define blank(a, b) ((a)[b] == 0 || (b) < 0 || (b) >= m)

typedef long long Int64;

using namespace std; 

const int MAXN = 9;

int n, m, a[MAXN][MAXN];
int now, next, ret = 0;

map<vector<int>, int> f[2];

class CheapestIsland {
	public:
	void Min(int b, const vector<int> &S) {
		if (*max_element(S.begin(), S.end()) == 1)
			ret = std::min(ret, b);
		map<vector<int>, int>::iterator it = f[next].find(S);
		if (it == f[next].end() || it->second > b) {
			f[next][S] = b;
		}
	}

	vector<int> Update(const vector<int>& a) {
		int s[12] = {0};
		for (int i = 1; i <= m + 1; i++)  
			s[i] = s[i - 1] + (bool)count(a.begin(), a.end(), i);
		vector<int> b = a;
		foreach(it, b) *it = s[*it];
		return b;
	}
	vector<int> fix(const vector<int>& a, int pos) {
		vector<int> b = a;
		int L = blank(a, pos - 1) ? -1 : a[pos - 1],
		    R = blank(a, pos) ? -1 : a[pos];
		b[pos] = m + 1;
		foreach(it, b) if (*it == L || *it == R) *it = m + 1;
		return Update(b);
	}

	template<class T>
	void Out(const vector<T> &a) {
		copy(a.begin(), a.end(), ostream_iterator<T>(cout, ""));
		cout <<endl;
	}

	vector<int> cancle(const vector<int>& a, int pos) {
		vector<int> b = a;
		b[pos] = 0;
		return Update(b);
	}

	bool check(const vector<int>& a, int pos) {
		return a[pos] == 0 || count(a.begin(), a.end(), a[pos]) > 1;
	}

	int minCost(vector <string> cells) {
		n = cells.size();
		for (int i = 0; i < n; i++) {
			stringstream fin(cells[i]);
			int j = 0;
			while (fin >>a[i][j]) j++;
			m = j;
		}
		now = 0, next = 1;
		f[next][vector<int>(m,0)] = 0;
		for (int i = 0; i <= n - 1; i++) {
			for (int j = 0; j <= m - 1; j++) {
				now ^= 1, next ^= 1;
				f[next].clear();
				foreach(it, f[now]) {
					//choose a[i][j]
					vector<int> tmp = fix(it->first, j);
					Min(it->second + a[i][j], tmp);
					//don't choose
					if (check(it->first, j)) {
						tmp = cancle(it->first, j);
						Min(it->second, tmp);
					}
				}
			}
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"-10 1", 
"2 -10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -19; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"1 2 3", 
"4 5 6", 
"7 8 9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minCost(Arg0)); }
	void test_case_2() { string Arr0[] = {"-5 100 -5", 
"-5 100 -5"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -10; verify_case(2, Arg1, minCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"-5 -5 -5 -5 -5 -5 -5 -5 -5", "-5 99 99 99 99 99 99 99 -5", "-5 99 -5 -5 -5 -5 -5 99 -5", "-5 99 -5 99 99 99 -5 99 -5", "-5 99 -5 99 -5 99 -5 99 -5", "-5 99 -5 99 -5 99 -5 99 -5", "-5 99 -5 99 -5 -5 -5 99 -5", "-5 99 -5 99 99 99 99 99 -5", "-5 99 -5 -5 -5 -5 -5 -5 -5"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -245; verify_case(3, Arg1, minCost(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	freopen("out", "w", stdout);
	CheapestIsland ___test;  
 	___test.run_test(3); 
	return 0;
}
// END CUT HERE

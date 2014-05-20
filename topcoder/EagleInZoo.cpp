// BEGIN CUT HERE

// END CUT HERE
#line 5 "EagleInZoo.cpp"
#include <cstring>
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

using namespace std;

class EagleInZoo {
	public:
		vector<int> Edge[101]; vector<int> p;
		double f[101][101]; int i;
		void Dfs(int u, double pnow) {
			if (u != 0) {
				f[i][u] = f[i - 1][u] + (f[i - 1][p[u - 1]] - f[i - 1][u]) * pnow;
			} else f[i][u] = 1;
			for (int j = 0; j < (int)Edge[u].size(); j++) Dfs(Edge[u][j], pnow * (1.0 / Edge[u].size()));
		}
	double calc(vector <int> parent, int K) {
		if (K == 1) return 1;
		memset(f, 0, sizeof f);
		for (i = 0; i < (int)parent.size(); i++) Edge[i].clear();
		p = parent;
		for (i = 0; i < (int)parent.size(); i++) Edge[parent[i]].push_back(i + 1);
		f[1][0] = 1;
		for (i = 2; i <= K; i++) {
			Dfs(0, 1);
		}
		double Ans = 0;
		for (int i = 1; i <= (int)parent.size(); i++) Ans += f[K][i] - f[K - 1][i];
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; double Arg2 = 1.0; verify_case(0, Arg2, calc(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; double Arg2 = 0.5; verify_case(1, Arg2, calc(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,1,0,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; double Arg2 = 0.75; verify_case(2, Arg2, calc(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,0,1,1,2,4,4,4,5,5,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; double Arg2 = 0.14595168754091617; verify_case(3, Arg2, calc(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; double Arg2 = 0.3272154791654077; verify_case(4, Arg2, calc(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {0,1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; double Arg2 = 0.0; verify_case(5, Arg2, calc(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	EagleInZoo ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

#line 81 "Family.cpp"
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

class Family {
	public:
	vector<int> Edge[200];
	int ok, color[200];
	void Dfs(int u, int c) {
		color[u] = c;
		for (int i = 0; i < (int)Edge[u].size(); i++) {
			if (color[Edge[u][i]] == -1) Dfs(Edge[u][i], c ^ 1); else if (color[Edge[u][i]] == c) ok = 0;
		}
	}
	string isFamily(vector <int> parent1, vector <int> parent2) {
		ok = 1; memset(color, -1, sizeof color);
		for (int i = 0; i < 200; i++) Edge[i].clear();
		for (int i = 0; i < (int)parent1.size(); i++) {
			int x = parent1[i], y = parent2[i]; if (x == -1 || y == -1) continue;
			Edge[x].push_back(y);
			Edge[y].push_back(x);
		}
		for (int i = 0; i < (int)parent1.size(); i++) if (color[i] == -1) Dfs(i, 0);
		return ok ? string("Possible") : string("Impossible");
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1,-1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(0, Arg2, isFamily(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1,-1,-1,-1,-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,-1,-1,-1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(1, Arg2, isFamily(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1,-1,0,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,1,2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(2, Arg2, isFamily(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-1,-1,-1,-1,1,-1,0,5,6,-1,0,3,8,6}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,-1,-1,3,-1,4,6,5,-1,5,4,6,1}
; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(3, Arg2, isFamily(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-1,-1,-1,2,2,-1,5,6,4,6,2,1,8,0,2,4,6,9,-1,16,-1,11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,-1,-1,1,0,-1,1,4,2,0,4,8,2,3,0,5,14,14,-1,7,-1,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(4, Arg2, isFamily(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	Family ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

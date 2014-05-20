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
#include <cstring>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

int a[4000][4000];
class PerfectSquare {
	public:
	set<int> S; map<int, int> M;
	int ways(vector <int> x) {
		memset(a, 0, sizeof a);
		foreach(it, x) {
			int tmp = *it;
			for (int i = 2; i * i <= *it; i++) if (tmp % i == 0) {
				S.insert(i);
				while (tmp % i == 0) tmp /= i;
			}
			if (tmp != 1) S.insert(tmp);
		}
		int L = 0;
		foreach(it, S) {
			foreach(ot, x) while (*ot % *it == 0) *ot /= *it, a[L][ot - x.begin()] ^= 1;
			L++;
		}
		int n = x.size(), row = (int)(sqrt(n) + 0.5);
		for (int i = 0; i < row; i++) {
			for (int j = i * row; j < (i + 1) * row; j++) a[L][j] = 1;
			a[L++][n] = 1;
			for (int j = i; j < n; j += row) a[L][j] = 1;
			a[L++][n] = 1;
		}
		int fixed = n, t = 0;
		for (int i = 0, j; i < n; i++) {
			for (j = t; j < L; j++) if (a[j][i]) break;
			if (j == L) continue;
			for (int k = i; k <= n; k++) swap(a[j][k], a[t][k]);
			for (int k = t + 1; k < L; k++) if (a[k][i])
				for (int l = i; l <= n; l++) a[k][l] ^= a[t][l];
			t++; fixed--;
		}
		for (int i = 0; i < L; i++) {
			int ok = a[i][n] == 1;
			for (int j = 0; j < n && ok; j++) if (a[i][j]) ok = false;
			if (ok) return 0;
		}
		int Ans = 1;
		while (fixed--) Ans = Ans * 2ll % 1000000007;
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1,
 1, 2}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
	void test_case_1() { int Arr0[] = {620, 620,
 620, 620}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, ways(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 2, 3,
 4, 5, 6,
 7, 8, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, ways(Arg0)); }
	void test_case_3() { int Arr0[] = {2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2,
 2, 2, 2, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
	void test_case_4() { int Arr0[] = {2, 3, 4, 5,
 6, 7, 8, 9,
 10,11,12,13,
 14,15,16,17}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(4, Arg1, ways(Arg0)); }
	void test_case_5() { int Arr0[] = {9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,
 9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690,9699690}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 993282280; verify_case(5, Arg1, ways(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	PerfectSquare ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

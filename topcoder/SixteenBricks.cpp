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

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

class SixteenBricks {
	public:
	int f[1 << 16];
	inline int id(int i, int j) {return i * 4 + j;}
	int maximumSurface(vector <int> height) {
		sort(height.rbegin(), height.rend()); memset(f, 0, sizeof f);
		for (int S = 0; S < (1 << 16) - 1; S++) {
			int tmp = S, index = 0; while (tmp) tmp -= tmp & -tmp, index++;
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) if (!(S >> id(i, j) & 1)) {
					int d = 1;
					for (int k = 0; k < 4; k++) {
						int nx = i + dx[k], ny = j + dy[k];
						if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4 || !(S >> id(nx, ny) & 1)) 
							d += height[index];
						else d -= height[index];
					}
					f[S | (1 << id(i, j))] = max(f[S | (1 << id(i, j))], f[S] + d);
				}
		}
		return f[(1 << 16) - 1];
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 32; verify_case(0, Arg1, maximumSurface(Arg0)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 64; verify_case(1, Arg1, maximumSurface(Arg0)); }
	void test_case_2() { int Arr0[] = {77, 78, 58, 34, 30, 20, 8, 71, 37, 74, 21, 45, 39, 16, 4, 59}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1798; verify_case(2, Arg1, maximumSurface(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	SixteenBricks ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

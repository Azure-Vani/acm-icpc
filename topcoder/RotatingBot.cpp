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
#include <ext/numeric>

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define foreach(i,n) for(typeof(n.begin()) i = n.begin(); i != n.end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 3000;

bool a[MAXN + 2][MAXN + 2];

class RotatingBot {
	public:
	int minArea(vector <int> moves) {
		/*int n = moves.size(); 
		if (n == 1) {
			return moves[0] + 1;
		}
		if (n == 2) {
			return (moves[1] + 1) * (1 + moves[0]);
		}
		if (n == 3) {
			if (moves[2] < moves[0]) return -1;
			return (moves[2] + 1) * (moves[0] + 1);
		}
		if (moves[2] == moves[0]) {
			for (int i = 3; i < moves.size(); i++) {
				
			}
		}*/
		memset(a, 0, sizeof a);
		int x = 1500, y = 1500;
		for (int i = 0; i <= MAXN; i++) a[0][i] = true, a[i][0] = true, a[MAXN + 1][i] = a[i][MAXN + 1] = true;
		a[x][y] = true;
		int Maxx = x, Maxy = y, Minx = y, Miny = y;
		for (int i = 0; i < (int)moves.size(); i++) {
			int t = i % 4;
			if (t == 0) {
				for (int j = 1; j <= moves[i]; j++) {
					x++;
					if (a[x][y]) return -1;
					a[x][y] = true;
					Maxx = max(Maxx, x);
				}
			}
			if (t == 1) {
				for (int j = 1; j <= moves[i]; j++) {
					y++;
					if (a[x][y]) return -1;
					a[x][y] = true;
					Maxy = max(Maxy, y);
				}
			}
			if (t == 2) {
				for (int j = 1; j <= moves[i]; j++) {
					x--;
					if (a[x][y]) return -1;
					a[x][y] = true;
					Minx = min(x, Minx);
				}
			}
			if (t == 3) {
				for (int j = 1; j <= moves[i]; j++) {
					y--;
					if (a[x][y]) return -1;
					a[x][y] = true;
					Miny = min(y, Miny);
				}
			}
		}
		for (int i = 1; i <= MAXN; i++)
			for (int j = 1; j <= MAXN; j++) if (a[i][j]) {
				Maxx = max(Maxx, i);
				Maxy = max(Maxy, j);
				Minx = min(Minx, i);
				Miny = min(Miny, j);
			}
		memset(a, 0, sizeof a);
		x = 1500, y = 1500; a[x][y] = true;
		for (int i = 0; i < (int)moves.size(); i++) {
			int t = i % 4;
			if (t == 0) {
				for (int j = 1; j <= moves[i]; j++) {
					x++;
					if (a[x][y]) return -1;
					a[x][y] = true;
				}
				if (!a[x + 1][y] && i + 1 != moves.size() && x != Maxx) return -1;
			}
			if (t == 1) {
				for (int j = 1; j <= moves[i]; j++) {
					y++;
					if (a[x][y]) return -1;
					a[x][y] = true;
				}
				if (!a[x][y + 1] && i + 1 != moves.size() && y != Maxy) return -1;
			}
			if (t == 2) {
				for (int j = 1; j <= moves[i]; j++) {
					x--;
					if (a[x][y]) return -1;
					a[x][y] = true;
				}
				if (!a[x - 1][y] && i + 1 != moves.size() && x != Minx) return -1;
			}
			if (t == 3) {
				for (int j = 1; j <= moves[i]; j++) {
					y--;
					if (a[x][y]) return -1;
					a[x][y] = true;
				}
				if (!a[x][y - 1] && i + 1 != moves.size() && y != Miny) return -1;
			}
		}
		return (Maxx - Minx + 1) * (Maxy - Miny + 1);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(0, Arg1, minArea(Arg0)); }
	void test_case_1() { int Arr0[] = {3,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 44; verify_case(1, Arg1, minArea(Arg0)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(2, Arg1, minArea(Arg0)); }
	void test_case_3() { int Arr0[] = {9,5,11,10,11,4,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 132; verify_case(3, Arg1, minArea(Arg0)); }
	void test_case_4() { int Arr0[] = {12,1,27,14,27,12,26,11,25,10,24,9,23,8,22,7,21,6,20,5,19,4,18,3,17,2,16,1,15}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 420; verify_case(4, Arg1, minArea(Arg0)); }
	void test_case_5() { int Arr0[] = {8,6,6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(5, Arg1, minArea(Arg0)); }
//	void test_case_6() { int Arr0[] = {8,6,6}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 63; verify_case(6, Arg1, minArea(Arg0)); }
//	void test_case_7() { int Arr0[] = {5,4,5,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(7, Arg1, minArea(Arg0)); }
	void test_case_6() { int Arr0[] = {1,1,2,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(6, Arg1, minArea(Arg0)); }
	void test_case_7() { int Arr0[] = {4,3,5,4,6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(7, Arg1, minArea(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	RotatingBot ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

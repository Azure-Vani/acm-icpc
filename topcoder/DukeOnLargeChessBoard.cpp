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
#include <cmath> 
#include <cstdlib> 
#include <ctime> 
#include <cassert>

#define mk make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899
#define In(x,l,r) ((x) >= (l) && (x) <= (r))
#define Make(l,r) {((x) = (l));(y) = (r);break;}

typedef long long Int64;

using namespace std; 

const int n = 999999;

int X, Y, x, y;

class DukeOnLargeChessBoard { public:
	inline void DoIt(int X, int Y) {
		while (true) {
			if (X == 0) Make(X, Y);
			if (Y == 0) {if (X & 1) Make(0, n) else Make(0, 0);}
			if (Y == n) {if (X & 1) Make(0, 0) else Make(0, n);}
			if (X == 1) Make(0, n);
			if (Y == 1) Make(X - 1, 0);
			X -= 2, Y -= 2;
		}
	}

	char ch[20];

	string lastCell(string initPosition) {
		sscanf(initPosition.c_str(), "(%d, %d)", &X, &Y);
		while (true) {
			if (X == 0 && Y == 0) Make(0,1);
			if (X == n && Y == n) Make(0,n);
			if (X == n && Y == 0) Make(0,0);
			if (X == 0 && Y == n) Make(0,n-1);
			if (Y == 1) {if (X == 0) Make(0,2) else Make(n,0);}
			if (Y == n) {if (X & 1) Make(0,n) else {DoIt(X, n - 1); break;}}
			if (X == 0) Make(0, Y + 1);
			if (Y == 0) {if (X & 1) Make(0, 0) else {DoIt(X, 1); break;}}
			if (Y == n - 1 && (!(X & 1))) Make(0, n);
			if (X & 1) {
				DoIt(X - 1, Y - 2);
			}else DoIt(X - 2, Y - 1);
			break;
		}
		sprintf(ch, "(%06d, %06d)", x, y);
		//printf("%d %d\n", x, y);
		return ch;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "(999999, 999999)"; string Arg1 = "(000000, 999999)"; verify_case(0, Arg1, lastCell(Arg0)); }
	void test_case_1() { string Arg0 = "(999999, 000000)"; string Arg1 = "(000000, 000000)"; verify_case(1, Arg1, lastCell(Arg0)); }
	void test_case_2() { string Arg0 = "(000002, 999998)"; string Arg1 = "(000000, 999999)"; verify_case(2, Arg1, lastCell(Arg0)); }
	void test_case_3() { string Arg0 = "(999998, 000001)"; string Arg1 = "(999999, 000000)"; verify_case(3, Arg1, lastCell(Arg0)); }
	void test_case_4() { string Arg0 = "(123456, 235711)"; string Arg1 = "(000000, 112256)"; verify_case(4, Arg1, lastCell(Arg0)); }
	void test_case_5() { string Arg0 = "(987654, 123456)"; string Arg1 = "(864197, 000000)"; verify_case(5, Arg1, lastCell(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	DukeOnLargeChessBoard ___test;  
 	___test.run_test(-1); 
	return 0;
}
// END CUT HERE

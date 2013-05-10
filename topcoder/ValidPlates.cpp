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
using namespace __gnu_cxx;

const int MAXN = 20;
const int inf = 2000000002;

void Add(int &a, Int64 b, Int64 c) {
	b *= c; if (b > inf) b = inf;
	b += a; if (b > inf) b = inf;
	a = b;
}

struct Matrix {
	int a[MAXN][MAXN], n;
	Matrix(int _n = 0) {
		n = 20; memset(a, 0, sizeof a);
		for (int i = 0; i <= n - 1; i++)
			a[i][i] = _n;
	}
	int& operator ()(int i, int j) {return a[i][j];}
	void operator =(const Matrix& oth) {
		memcpy(a, oth.a, sizeof a);
		n = oth.n;
	}
	Matrix operator *(const Matrix& oth) const {
		Matrix ret;
		for (int i = 0; i <= n - 1; i++) {
			for (int j = 0; j <= n - 1; j++) {
				int &tmp = ret(i, j); tmp = 0;
				for (int k = 0; k <= n - 1; k++) 
					Add(tmp, a[i][k], oth.a[k][j]);
			}
		}
		return ret;
	}
};

Matrix init;
char res[53];

class ValidPlates {
	public:
	int Eval(int L) {
		Matrix tmp = init;
		Matrix r;
		r = power(tmp, L);
		int ret = 0;
		for (int i = 1; i <= 9; i++) 
			for (int j = 0; j <= 9; j++) {
				Add(ret, 1,r(i, j + 10));
			}
		return ret;
	}
	int Eval(int s, int L) {
		Matrix tmp = init;
		Matrix r;
		r = power(tmp, L);
		int ret = 0;
		for (int i = 0; i <= 9; i++) 
			Add(ret, 1, r(s, i));
		return ret;
	}
	string getPlate(vector <string> profane, int seqno) {
		if (seqno < 10) {
			stringstream sin;
			sin <<seqno;
			return sin.str();
		}
		for (int i = 0; i <= 9; i++) {
			for (int j = 0; j <= 9; j++) 
				init(i, j) = 1;
			init(i, i + 10) = 1;
			init(i + 10, i + 10) = 1;
		}
		init.n = 20;
		foreach(it, profane) {
			stringstream sin(*it);
			string st;
			while (sin >>st)
				init(st[0] - '0', st[1] - '0') = 0;
		}
		Int64 l = 2, r = seqno + 2, t = Eval(r);
		if ((int)t < seqno) return string();
		while (l <= r) {
			Int64 mid = (l + r) >> 1;
			int t = Eval(mid);
			if (t >= seqno)
				r = mid - 1;
			else
				l = mid + 1;
		}
		int Len = l;
		seqno -= Eval(Len - 1); Len--;
		for (int i = 1; i <= 9; i++) {
			int t = Eval(i, Len);
			if (t >= seqno) {
				res[0] = i + '0';
				break;
			} else seqno -=t;
		}
		for (int i = 1; i <= std::min(l - 1, 49ll); i++) {
			Len--;
			for (int j = 0; j <= 9; j++) if (init(res[i - 1] - '0', j)) {
				int t = Eval(j, Len);
				if (t >= seqno) {
					res[i] = j + '0';
					break;
				} else seqno -= t;
			}
		}
		string st = res;
		if (l > 50) st.replace(st.length() - 3, 3, "...");
		return st;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; string Arg2 = "1000"; verify_case(0, Arg2, getPlate(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"10"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; string Arg2 = "11"; verify_case(1, Arg2, getPlate(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"00 01 02 03 04 05 06 07 08 09", "10 12 13 14 15 16 17 18 19", "20 21 22 23 24 25 26 27 28 29", "30 31 32 33 34 35 36 37 38 39", "40 41 42 43 44 45 46 47 48 49", "50 51 52 53 54 55 56 57 58 59", "60 61 62 63 64 65 66 67 68 69", "70 71 72 73 74 75 76 77 78 79", "80 81 82 83 84 85 86 87 88 89", "90 91 92 93 94 95 96 97 98 99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2000000000; string Arg2 = "2277659869"; verify_case(2, Arg2, getPlate(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"00 01 02 03 04 05 06 07 08 09 11 12 13 14 15 16 17",
 "18 19 22 23 24 25 26 27 28 29 33 34 35 36 37 38 39",
 "44 45 46 47 48 49 55 56 57 58 59 66 67 68 69 77 78",
 "79 88 89 99 99 99 99 99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1023; string Arg2 = ""; verify_case(3, Arg2, getPlate(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"00 01 02 03 04 05 07 08 09",
 "10 11 12 13 14 15 17 18 19",
 "20 21 22 24 25 26 27 28 29",
 "30 31 32 33 34 36 37 38 39",
 "41 43 45 46 48",
 "52 53 54 55 56 58 59",
 "60 61 63 64 66 67 68 69",
 "70 72 73 74 75 76 77 78",
 "80 81 82 83 84 86 87 88 89",
 "90 91 92 94 95 96 97 98"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2000000000; string Arg2 = "79999999351623516571657999935799993"; verify_case(4, Arg2, getPlate(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"00 01 02 03 04 05 06 07 08 09",
 "10 11 12 13 14 16 17 19",
 "20 21 22 23 24 25 26 27 28 29",
 "30 31 32 33 34 35 36 38 39",
 "41 42 43 44 45 46 49",
 "50 52 53 54 55 57 58 59",
 "60 61 62 63 64 65 66 67 68 69",
 "70 72 73 74 75 76 77 78 79",
 "80 81 82 83 84 85 86 87 88 89",
 "90 91 92 93 94 95 98 99"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2000000000; string Arg2 = "37151515151515151515151515151515151515151515151..."; verify_case(5, Arg2, getPlate(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	ValidPlates ___test;  
 	___test.run_test(2); 
	return 0;
}
// END CUT HERE

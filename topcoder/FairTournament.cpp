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

const int base = 10000000;

class BigInteger {public:
	vector<int> a;
	vector<int>::size_type size(void) const {return a.size();}
	int& operator ()(const int& index) {return a[index];}
	void Carry(void) {
		for (int i = 0; i <= (int)a.size() - 1; i++) {
			int add = a[i] / base; a[i] %= base;
			if (!add) continue;
			if (i == (int)a.size() - 1) a.pb(add); else a[i + 1] += add;
		}
	}
	void operator =(int oth) {
		a.resize(0);
		while (oth) a.pb(oth % base), oth /= base;
	}
	bool operator !=(int oth) {
		if (a.size() == 0) return false;
		return a.size() > 1 || a[0] != oth;
	}
	BigInteger operator +=(BigInteger& oth) {
		if (oth.size() > a.size()) a.resize(oth.size());
		int n = std::min(a.size(), oth.size());
		for (int i = 0; i <= n - 1; i++) 
			a[i] += oth(i);
		Carry();
		return *this;
	}
};

string str(Int64 i) {
	stringstream sin; sin << i; return sin.str();
}
string str(const BigInteger& oth) {
	string st;
	for (vector<int>::const_reverse_iterator it = oth.a.rbegin(); it != oth.a.rend(); it++) {
		stringstream sin;
		sin <<*it;
		if (it != oth.a.rbegin()) for (int j = 1; j <= 7 - (int)sin.str().length(); j++) st += "0";
		st += sin.str();
	}
	return st;
}

const int MAXN = 103;
const int MAXM = (1 << 13) + 100;

BigInteger f[2][MAXM];

class FairTournament {
	public:
	string countPermutations(int n, int k) {
		int k2 = k << 1, t = 1, u = 0, m = (1 << (k + 1)) - 1;
		f[t][m] = 1;
		for (int i = 1; i <= n; i++) {
			std::swap(u, t);
			for (int j = 0; j <= (1 << (k2 + 1)) - 1; j++) f[t][j] = 0;
			for (int j = 0; j <= (1 << (k2 + 1)) - 1; j++) if (f[u][j] != 0) {
				if (j & (1 << k2)) {
					int next = j;
					next ^= (1 << k2);
					next <<= 1;
					++next;
					f[t][next] += f[u][j];
				} else {
					int s = j;
					while (s) {
						int low = s & -s, next = j;
						next ^= low; next <<= 1;
						++next;
						f[t][next] += f[u][j];
						s -= low;
					}
				}
			}
		}
		return str(f[t][m]);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 57; int Arg1 = 4; string Arg2 = "159128297041016435714751131714066"; verify_case(0, Arg2, countPermutations(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; string Arg2 = "6"; verify_case(1, Arg2, countPermutations(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 3; string Arg2 = "19708"; verify_case(2, Arg2, countPermutations(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 1; string Arg2 = "573147844013817084101"; verify_case(3, Arg2, countPermutations(Arg0, Arg1)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	FairTournament ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

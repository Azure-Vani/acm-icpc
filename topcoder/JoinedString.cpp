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

#define mp make_pair
#define pb push_back
#define rep(i,l,r) for(int i = l; i <= r; i++)
#define sqr(x) ((x)*(x))
#define pi 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899

typedef long long Int64;

using namespace std; 

const int MAXN = 19;
const int MAXM = 5300;

class JoinedString {
	public:

	bool hash[MAXN];
	int n, dis[MAXN][MAXN];
	vector <string> st;

	int Cal(string st, string ss) {
		int limit = std::min(st.length(), ss.length());
		for (int i = limit - 1; i >= 1; i--) {
			if (st.substr(st.length() - i, i) == ss.substr(0, i))
				return i;
		}
		return 0;
	}

	bool Sub(string st, string ss) {
		return ss.find(st) != string::npos;
	}

	int f[MAXN][MAXM]; string g[MAXN][MAXM];
	int a[MAXN][MAXN];
	std::pair<int, int> d[MAXN * MAXM + 100000];

	string joinWords(vector <string> words) {
		memset(hash, 0, sizeof hash);
		n = words.size();
		for (int i = 0; i <= n - 1; i++) {
			for (int j = 0; j <= n - 1; j++) if (i != j) {
				if (Sub(words[i], words[j])) {
					if (words[i] != words[j] || i < j) hash[i] = true;
				}
			}
		}

		for (int i = 0; i <= n - 1; i++) if (!hash[i])
			st.pb(words[i]);
		std::sort(st.begin(), st.end());
		memset(f, 60, sizeof f);
		n = st.size();
		for (int i = 0; i <= n - 1; i++) 
			for (int j = 0; j <= n - 1; j++) {
				a[i][j] = Cal(st[i], st[j]);
			}

		int head = 0, tail = 1;
		for (int i = 0; i <= n - 1; i++) {
			d[++tail] = std::mp(i, 1 << i);
			f[i][1 << i] = st[i].length();
			g[i][1 << i] = st[i];
		}

		while (head <= tail) {
			int pos = d[head].first, S = d[head++].second;
			for (int i = 0; i <= n - 1; i++) if ((S & (1 << i)) == 0) {
				string next_str = g[pos][S] + st[i].substr(a[pos][i], st[i].length() - a[pos][i]);
				int next = S | (1 << i);
				if (f[i][next] > f[pos][S] + (int)st[i].length() - a[pos][i] || 
						(f[i][next] == f[pos][S] + (int)st[i].length() - a[pos][i] && next_str < g[i][next])) {
					f[i][next] = f[pos][S] + st[i].length() - a[pos][i];
					g[i][next] = next_str;
					d[++tail] = mp(i, next);
				}
			}
		}
		int min = 100000, S = (1 << n) - 1;string ret;
		for (int i = 0; i <= n - 1; i++) if (min > f[i][S] || (min == f[i][S] && ret > g[i][S])) {
			min = f[i][S];
			ret = g[i][S];
		}
		return ret;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BAB", "ABA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ABAB"; verify_case(0, Arg1, joinWords(Arg0)); }
	void test_case_1() { string Arr0[] = {"ABABA", "AKAKA", "AKABAS", "ABAKA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ABABAKAKABAS"; verify_case(1, Arg1, joinWords(Arg0)); }
	void test_case_2() { string Arr0[] = {"AAA","BBB", "CCC", "ABC", "BCA", "CAB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "AAABBBCABCCC"; verify_case(2, Arg1, joinWords(Arg0)); }
	void test_case_3() { string Arr0[] = {"OFG", "SDOFGJTILM", "KBWNF", "YAAPO", "AWX", "VSEAWX", "DOFGJTIL", "YAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "KBWNFSDOFGJTILMVSEAWXYAAPO"; verify_case(3, Arg1, joinWords(Arg0)); }
	void test_case_4() { string Arr0[] = {"NVCSKFLNVS", "HUFSPMRI", "FLNV", "KMQD", "RPJK", "NVSQORP", "UFSPMR", "AIHUFSPMRI"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "AIHUFSPMRINVCSKFLNVSQORPJKMQD"; verify_case(4, Arg1, joinWords(Arg0)); }
	void test_case_5() { string Arr0[] = {"BA", "BA", "BA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "BA"; verify_case(5, Arg1, joinWords(Arg0)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	JoinedString ___test;  
 	___test.run_test(5); 
	return 0;
}
// END CUT HERE

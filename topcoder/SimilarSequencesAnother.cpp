// BEGIN CUT HERE
// END CUT HERE
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstring>
#include <tr1/unordered_map>

#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); ++it)

using namespace std;

const int mod = 1000000009;

int _[] = {1, 2, 3, 4};

inline int Max(int a, int b) {return a > b ? a : b;}
class SimilarSequencesAnother {
	public:

	inline void Add(int &a, int b) {a += b; if (a >= mod) a -= mod;}
	typedef vector<int> VII;
	typedef pair<VII, VII> State;
	
	map<State, int> f[101];

	int fim[32], n;
	inline void Make(vector<int> &a) {
		memset(fim, 0, sizeof fim); int top = 1;
		foreach(it, a) if (!fim[*it]) fim[*it] = top++;
		foreach(it, a) *it = fim[*it];
	}

	inline void Trans(int i, const State& now, const pair<int, int>& l1, const pair<int, int>& l2, int tmp, int d = 0) {
		State next = now;
		next.second[0] = now.second[1];
		next.second[1] = l1.first;
		next.second[2] = now.second[3];
		next.second[3] = l2.first;
		next.first[0] = Max(now.first[1], now.first[0] + (next.second[3] == now.second[0]));
		next.first[1] = Max(Max(next.first[0], now.first[2]), now.first[1] + (next.second[3] == now.second[1]));
		next.first[4] = Max(now.first[3], now.first[4] + (next.second[1] == now.second[2]));
		next.first[3] = Max(Max(next.first[4], now.first[2]), now.first[3] + (next.second[1] == now.second[3]));
		next.first[2] = Max(Max(next.first[1], next.first[3]), now.first[2] + (next.second[3] == next.second[1]));
		if (next.first[2] + n - i - 1 <  n - 2) {
			return;
		}
		Make(next.second);
		int &up = f[i + 1][next];
		Add(up, (long long)(((long long)l1.second * l2.second - d) % mod) * tmp % mod);

		// printf("@%d(%d):\n", i + 1, up);
		// foreach(it, next.first) printf("%d ", *it); puts("");
		// foreach(it, next.second) printf("%d ", *it); puts("");
	}

	int getCount(int N, int bound) {
		for (int i = 0; i <= 100; i++) f[i].clear(); n = N;
		f[0][make_pair(vector<int>(5, 0), vector<int>(_, _ + 4))] = 1;
		for (int i = 0; i < N; i++) {
			foreach(it, f[i]) {
				State now = it->first; int tmp = it->second;
				vector<pair<int, int> > trans;
				if (i == 0) {
					trans.push_back(make_pair(5, bound)); 
				}else
				if (i == 1) {
					if (now.second[1] == now.second[3]) {
						trans.push_back(make_pair(now.second[1], 1));
						if (bound > 1) trans.push_back(make_pair(5, bound - 1));
					} else {
						trans.push_back(make_pair(now.second[1], 1));
						trans.push_back(make_pair(now.second[3], 1));
						if (bound > 2) trans.push_back(make_pair(5, bound - 2));
					}
				} else {
					int t = *max_element(now.second.begin(), now.second.end());
					for (int i = 1; i <= t; i++) trans.push_back(make_pair(i, 1));
					if (bound > t) trans.push_back(make_pair(t + 1, bound - t));
				}
				for (int l1 = 0; l1 < (int)trans.size(); l1++)
					for (int l2 = 0; l2 < (int)trans.size(); l2++) if (l1 != (int)trans.size() - 1 || l2 != (int)trans.size() - 1) {
						Trans(i, now, trans[l1], trans[l2], tmp);
					}
				pair<int, int> tt = trans[trans.size() - 1];
				Trans(i, now, make_pair(tt.first, 1), make_pair(tt.first, tt.second), tmp);
				Trans(i, now, make_pair(tt.first, tt.second), make_pair(tt.first + 1, tt.second), tmp, tt.second);
			}
		}
		int Ans = 0;
		foreach(it, f[N]) if (it->first.first[2] >= N - 2) {
			Add(Ans, it->second);
		}
		return Ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 10; int Arg2 = 10000; verify_case(0, Arg2, getCount(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 687; verify_case(1, Arg2, getCount(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 8; int Arg1 = 1; int Arg2 = 1; verify_case(2, Arg2, getCount(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 123456789; int Arg2 = 439681851; verify_case(3, Arg2, getCount(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1; int Arg1 = 1000000000; int Arg2 = 81; verify_case(4, Arg2, getCount(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
SimilarSequencesAnother ___test;
___test.run_test(-1);
return 0;
}
// END CUT HERE


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

class CandidatesSelection {
	public:
	int n, m, pos[100];

	string possible(vector <string> score, vector <int> result) {
		n = score.size(); m = score[0].size();
		foreach(it, result) pos[*it] = it - result.begin();
		vector<pair<string, int> > p; for (int i = 0; i < n; i++) p.push_back(make_pair("", i));
		vector<pair<int, int> > inter; inter.push_back(make_pair(0, n - 1));
		int used[100] = {0};
		for (int k = 0; k <= m; k++) {
			sort(p.begin(), p.end());
			int ok = 1; for (int i = 0; i < n; i++) if (p[i].second != result[i]) ok = 0;
			if (ok) return "Possible";
			for (int j = 0; j < m; j++) if (!used[j]) {
				int vaild = 1;
				foreach(it, inter) {
					for (int l = it->first; l <= it->second && vaild; l++)
						for (int r = it->first; r <= it->second && vaild; r++)
							if (score[p[l].second][j] < score[p[r].second][j] && pos[p[l].second] > pos[p[r].second]) {
								vaild = false;
							}
				}
				if (vaild) {
					for (int i = 0; i < n; i++) p[i].first = p[i].first + score[p[i].second][j];
					sort(p.begin(), p.end());
					inter.clear();
					for (int i = 0, j = i; i < n; i = j) {
						while (j < n && p[i].first == p[j].first) j++;
						inter.push_back(make_pair(i, j - 1));
					}
					used[j] = 1;
					break;
				}
			}
		}
		return "Impossible";
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BBBB", "BBBA", "BBAB", "BBAA", "BABB", "BABA", "BAAB", "BAAA", "ABBB", "ABBA", "ABAB", "ABAA", "AABB", "AABA", "AAAB", "AAAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(0, Arg2, possible(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"BAB", "ABB", "AAB", "ABA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,0,1,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(1, Arg2, possible(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"BAB", "ABB", "AAB", "ABA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 3, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(2, Arg2, possible(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"AAA", "ZZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Impossible"; verify_case(3, Arg2, possible(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"ZZZ", "AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(4, Arg2, possible(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"ZYYYYX","YXZYXY","ZZZZXX","XZXYYX","ZZZYYZ","ZZXXYZ","ZYZZXZ","XZYYZX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,7,1,0,2,5,6,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Possible"; verify_case(5, Arg2, possible(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	CandidatesSelection ___test;
	___test.run_test(0);
	return 0;
}
// END CUT HERE

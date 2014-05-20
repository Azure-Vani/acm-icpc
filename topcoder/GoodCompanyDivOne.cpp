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

#define foreach(it, T) for(__typeof((T).begin()) it = (T).begin(); it != (T).end(); ++it)

using namespace std;

const int MAXN = 210;

int nx, ny; // 左边的点标号从1到nx，右边点标号从1到ny
long long inf, cost[MAXN][MAXN], fx[MAXN], fy[MAXN], dist[MAXN]; //权值若为long long的话，只需改动此行即可
int used[MAXN], maty[MAXN], which[MAXN];

inline void AddEdge(int x, int y, int z) {
	cost[x][y] = z;
}

pair<int, long long> KM(void) {
	for (int x = 1; x <= nx; x++) {
		int y0 = 0; maty[0] = x;
		for (int y = 0; y <= ny; y++) { dist[y] = inf + 1; used[y] = false; }

		do {
			used[y0] = true;
			int x0 = maty[y0], y1 = 0;
			long long delta = inf + 1;

			for (int y = 1; y <= ny; y++) if (!used[y]) {
				long long curdist = cost[x0][y] - fx[x0] - fy[y];
				if (curdist < dist[y]) {
					dist[y] = curdist;
					which[y] = y0;
				}
				if (dist[y] < delta) {
					delta = dist[y];
					y1 = y;
				}
			}

			for (int y = 0; y <= ny; y++) if (used[y]) {
				fx[maty[y]] += delta;
				fy[y] -= delta;
			} else dist[y] -= delta;

			y0 = y1;
		} while (maty[y0] != 0);

		do {
			int y1 = which[y0];
			maty[y0] = maty[y1];
			y0 = y1;
		} while (y0);
	}

	long long ret = 0;
	int npair = 0;
	for (int y = 1; y <= ny; y++) {
		int x = maty[y];
		if (cost[x][y] < inf) {
			ret += cost[x][y];
			npair++;
		}
	}

	return make_pair(npair, ret);
}

inline void clear(void) {
	memset(fx, 0, sizeof fx);
	memset(fy, 0, sizeof fy);
	memset(maty, 0, sizeof maty);
	memset(cost, 0x3f, sizeof cost);
	inf = cost[0][0];
}

vector<int> Edge[50];

class GoodCompanyDivOne {
	public:
	int n, m; vector<int> cost; int f[50][50];

	void Dfs(int u) {
		foreach(it, Edge[u]) Dfs(*it);
		if ((int)Edge[u].size() > m) return;
		ny = nx = m;
		int g[50]; memset(g, 0x3f, sizeof g);
		for (int k = 0; k < m; k++) {
			clear(); 
			for (int i = 0; i < (int)Edge[u].size(); i++) {
				for (int j = 0; j < m; j++) if (j != k) AddEdge(i + 1, j + 1, f[Edge[u][i]][j]);
			}
			pair<int, long long> tmp = KM();
			if (tmp.first != (int)Edge[u].size()) continue;
			g[k] = tmp.second + cost[k];
		}
		for (int k = 0; k < m; k++) {
			if (k != 0) f[u][k] = g[k] + cost[0]; else f[u][k] = g[k] + cost[1];
			for (int i = 0; i < m; i++) if (i != k) f[u][k] = min(f[u][k], g[i] + cost[k]);
		}
	}

	int minimumCost(vector <int> superior, vector <int> training) {
		sort(training.begin(), training.end());
		memset(f, 0x3f, sizeof f); n = superior.size(); m = training.size();
		for (int i = 0; i < 50; i++) Edge[i].clear();
		for (int i = 1; i < n; i++) Edge[superior[i]].push_back(i);
		cost = training;
		int inf = f[0][0], Ans = inf;
		Dfs(0);
		for (int i = 0; i < m; i++) Ans = min(Ans, f[0][i]);
		if (Ans == inf) return -1; else return Ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {-1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(0, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {-1, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(1, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-1, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, minimumCost(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-1, 0, 0, 2, 2, 2, 1, 1, 6, 0, 5, 4, 11, 10, 3, 6, 11, 7, 0, 2, 13, 14, 2, 10, 9, 11, 22, 10, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 2, 6, 6, 8, 3, 3, 1, 1, 5, 8, 6, 8, 2, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 71; verify_case(3, Arg2, minimumCost(Arg0, Arg1)); }

// END CUT HERE

};
// BEGIN CUT HERE
int main(){
GoodCompanyDivOne ___test;
___test.run_test(-1);
return 0;
}
// END CUT HERE


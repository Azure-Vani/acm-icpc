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

const int MAXN = 100;

struct Edge {
	int y, z; Edge *next;
	Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
}*a[MAXN];

int deep[MAXN], father[MAXN], vis[MAXN];

class Ethernet {
	public:
	int n;

	inline void AddEdge(int x, int y, int z) {
		a[x] = new Edge(y, z, a[x]);
	}

	void Dfs(int u) {
		for (Edge *p = a[u]; p; p = p->next) {
			deep[p->y] = deep[u] + p->z;
			father[p->y] = u;
			Dfs(p->y);
		}
	}

	int getAnother(int u) {
		int ret = u;
		for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y]) {
			int t = getAnother(p->y);
			if (deep[t] > deep[ret]) ret = t;
		}
		return ret;
	}

	void color(int u) {
		vis[u] = 1;
		for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y]) {
			color(p->y);
		}
	}

	int connect(vector <int> parent, vector <int> dist, int maxDist) {
		memset(a, 0, sizeof a); memset(vis, 0, sizeof vis);
		n = parent.size() + 1;
		for (int i = 0; i < n - 1; i++) AddEdge(parent[i], i + 1, dist[i]);
		Dfs(0);
		int Ans = 0;
		while (true) {
			int depth = -1, w = -1;
			for (int i = 0; i < n; i++) if (!vis[i] && deep[i] > depth) depth = deep[i], w = i;
			if (w == -1) break;
			vis[w] = 1;
			while (w) {
				w = father[w];
				int another = getAnother(w);
				if (deep[another] + depth - 2 * deep[w] <= maxDist) {
					color(w);
				} else break;
			}
			Ans++;
		}
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; int Arg3 = 1; verify_case(0, Arg3, connect(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; int Arg3 = 4; verify_case(1, Arg3, connect(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,1,2,3,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = 3; verify_case(2, Arg3, connect(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 2; verify_case(3, Arg3, connect(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,1,0,3,0,5,0,6,0,6,0,6,4,6,9,4,5,5,2,5,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {93,42,104,105,59,73,161,130,30,81,62,93,131,133,139,5,13,34,25,111,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 162; int Arg3 = 11; verify_case(4, Arg3, connect(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	Ethernet ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE

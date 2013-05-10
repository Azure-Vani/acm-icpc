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
#define foreach(i, T) for(typeof((T).begin()) i = (T).begin(); i != (T).end(); ++i)

typedef long long Int64;

using namespace std; 

const int MAXN = 53;
const int inf = 1000000 * 50;

int inp[MAXN], d[MAXN], hash[MAXN];
int near[MAXN], son[MAXN], lab[MAXN];
bool incircle[MAXN];

class ByteLand { public:

	vector<int> road, distance;
	vector<int> Edge[MAXN];

	int n, cur;

	int head, tail;

	void Dfs(int u) {
		lab[u] = cur; foreach(it, Edge[u]) if (!lab[*it]) Dfs(*it);
	}

	int Check(int limit) {
		int ret = 0;
		 for (int v = 1; v <= cur; v++) {
			int count = inf;
			for (int i = 0; i < n; i++) if (lab[i] == v && incircle[i]) {
				int backup = road[i], backup2 = distance[i], tmp = 0;
				road[i] = 51; distance[i] = inf;
				memset(inp, 0, sizeof inp);
				memset(near, 60, sizeof near);
				memset(son, 0, sizeof son);
				head = 1, tail = 0;
				for (int j = 0; j <= n - 1; j++) if (lab[j] == v) inp[road[j]]++;
				for (int j = 0; j <= n - 1; j++) if (lab[j] == v && !inp[j]) d[++tail] = j;
				while (head <= tail) {
					int now = d[head++];
					if (now == 51) break;
					int P = road[now];
					if (!--inp[P]) d[++tail] = P;
					if (hash[now]) near[now] = 0;
					if (near[now] + son[now] > limit && son[now] + distance[now] > limit) {
						tmp++;
						near[now] = 0;
						son[now] = -inf;
					}
					near[P] = std::min(near[P], near[now] + distance[now]);
					if (near[now] + son[now] > limit) 
						son[P] = std::max(son[P], son[now] + distance[now]);
				}
				road[i] = backup, distance[i] = backup2;
				count = std::min(count, tmp);
			}
			ret += count;
		}
		return ret;
	}

	int buildCastles(vector <int> road, vector <int> distance, vector <int> castle, int k) {
		n = road.size();
		this->road = road, this->distance = distance;
		for (int i = 0; i < (int)castle.size(); i++) hash[castle[i]] = true;
		for (int i = 0; i < n; i++) Edge[i].pb(road[i]), Edge[road[i]].pb(i);
		cur = 0;
		for (int i = 0; i <= n - 1; i++) if (!lab[i]) ++cur, Dfs(i);
		for (int i = 0; i <= n - 1; i++) inp[road[i]]++;
		head = 1, tail = 0;
		for (int i = 0; i <= n - 1; i++) if (!inp[i]) d[++tail] = i;
		while (head <= tail) {
			int now = d[head++];
			if (!--inp[road[now]]) d[++tail] = road[now];
		}
		for (int i = 0; i <= n - 1; i++) incircle[i] = inp[i];
		int l = 0, r = 1000000 * 50;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Check(mid) <= k)
				r = mid - 1;
			else
				l = mid + 1;
		}
		return l;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {12, 0, 19, 2, 4, 13, 13, 4, 17, 5, 9, 17, 5, 8, 19, 8, 12, 0, 8, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 4, 9, 4, 2, 5, 4, 7, 7, 1, 6, 9, 4, 5, 1, 8, 8, 4, 2, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 14, 16}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; int Arg4 = 15; verify_case(0, Arg4, buildCastles(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1,2,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; int Arg4 = 1; verify_case(1, Arg4, buildCastles(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; int Arg4 = 0; verify_case(2, Arg4, buildCastles(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0,2,0,0,2,2,8,3,8,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,9,1,8,1,3,7,2,8,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3,4,6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 3; verify_case(3, Arg4, buildCastles(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; int Arg4 = 5; verify_case(4, Arg4, buildCastles(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE
 
};
// BEGIN CUT HERE
int main(void) {
	ByteLand ___test;  
 	___test.run_test(0); 
	return 0;
}
// END CUT HERE

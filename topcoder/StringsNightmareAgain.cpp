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

const int MAXN = 200010;

struct Node {
	Node *next[26], *par; int val, end, pos; // 26 is volatile
}POOL[MAXN << 1], *data = POOL, *root, *last; //Note that the size of POOL should be doubled.

inline void Add(int x, int i) {
	Node *p = last, *np = data++;
	np->val = p->val + 1; np->end = true; np->pos = i;
	while (p && !p->next[x]) 
		p->next[x] = np, p = p->par;
	if (p == 0) {
		np->par = root;
	} else {
		Node *q = p->next[x];
		if (q->val == p->val + 1) {
			np->par = q;
		} else {
			Node *nq = data++;
			nq->val = p->val + 1;
			memcpy(nq->next, q->next, sizeof q->next);
			nq->par = q->par;
			np->par = q->par = nq;
			while (p && p->next[x] == q)
				p->next[x] = nq, p = p->par;
		}
	}
	last = np;
}

void Clear(void) {
	data = POOL; last = root = data++;
}
char ch[MAXN]; int p[MAXN], Max[MAXN], Min[MAXN], delta[MAXN];

int cmp(int x, int y) {return POOL[x].val < POOL[y].val;}

class StringsNightmareAgain {
	public:
	long long UniqueSubstrings(int a, int b, int c, int d, int n) {
		Clear(); memset(delta, 0, sizeof delta);
		for (int i = 0; i < n; i++) ch[i] = 'a';
		for (int i = 0; i < a; ++i) {
			b = ((long long)b*c+d)%n;
			ch[b] = 'b';
		}
		for (int i = 0; i < n; i++) Add(ch[i] - 'a', i);
		int L = data - POOL;
		for (int i = 0; i < L; i++) p[i] = i;
		sort(p, p + L, cmp);
		memset(Min, 0x3f, sizeof Min);
		memset(Max, -1, sizeof Max);
		long long Ans = 0;
		for (int i = L - 1; i >= 0; i--) {
			int now = p[i];
			if (POOL[now].end) {
				Max[now] = max(Max[now], POOL[now].pos);
				Min[now] = min(Min[now], POOL[now].pos);
			}
			if (i) {
				delta[now] = POOL[POOL[now].par - POOL].val;
				Max[POOL[now].par - POOL] = max(Max[POOL[now].par - POOL], Max[now]);
				Min[POOL[now].par - POOL] = min(Min[POOL[now].par - POOL], Min[now]);
			}
			if (Max[now] != Min[now]) {
				int tmp = (long long)min(POOL[now].val, Max[now] - Min[now]) - delta[now];
				if (tmp > 0) Ans += tmp;
			}
		}
		return Ans;
	}

	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 0; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 4; long long Arg5 = 2LL; verify_case(0, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 3; int Arg2 = 1; int Arg3 = 1; int Arg4 = 6; long long Arg5 = 3LL; verify_case(1, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 1; int Arg3 = 1; int Arg4 = 6; long long Arg5 = 3LL; verify_case(2, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 4; int Arg1 = 3; int Arg2 = 3; int Arg3 = 3; int Arg4 = 10; long long Arg5 = 5LL; verify_case(3, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 2; int Arg3 = 3; int Arg4 = 11; long long Arg5 = 9LL; verify_case(4, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_5() { int Arg0 = 10; int Arg1 = 1000000; int Arg2 = 1000000; int Arg3 = 1; int Arg4 = 51; long long Arg5 = 63LL; verify_case(5, Arg5, UniqueSubstrings(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE

int main(){
	StringsNightmareAgain ___test;
	___test.run_test(5);
	return 0;
}
// END CUT HERE

//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <set>

#define pb push_back
#define mp make_pair
#define foreach(i,n) for(__typeof(n.begin()) (i) = n.begin(); (i) != n.end(); ++(i))

using namespace std;

namespace Solve {
	const int MAXN = 50010;
	const int base = 13331;
	typedef unsigned long long Int64;

	struct Node {
		Node* ch[26];bool end;
		Node(){end = false; memset(ch, 0, sizeof ch);}
	}*root;

	int n;
	char c[100];

	inline void Input(void) {
		root = new Node;
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) {
			Node *t = root;
			scanf("%s\n", c);
			for (int i = 0; c[i]; i++) {
				if (!t->ch[c[i] - 'a']) t->ch[c[i] - 'a'] = new Node;
				t = t->ch[c[i] - 'a'];
			}
			t->end = true;
		}
	}

	std::set<Int64> S;

	Int64 Dfs(Node *u) {
		if (u == NULL) return 0;
		Int64 ret = 0;
		for (int i = 0; i < 26; i++) {
			Int64 t = Dfs(u->ch[i]);
			ret = ret * base + t + i;
		}
		if (u->end) ret ^= 1200007ll; else ret ^= 70000001ll;
		S.insert(ret);
		return ret;
	}

	inline void solve(void) {
		Input();
		Dfs(root);
		printf("%ld\n", S.size());
	}
}

int main(void) {
#ifdef FILEIO
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	Solve::solve();
	return 0;
}
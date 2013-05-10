//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 2000003;
	char *ch[MAXN], c[MAXN];

	struct Node {
		char *v; Node *child, *brother; int len, cnt;
	}*root, T[1000000], *sid = T;

	char POOL[9500000], *pid = POOL;

	int n;
	inline void Input(void) {
		scanf("%d\n", &n);
		root = new Node;
		for (int _ = 1; _ <= n; _++) {
			fflush(stdout);
			gets(c);
			int Len = strlen(c);
			ch[_] = pid;
			memcpy(ch[_], c, sizeof(char) * (Len + 1));
			pid += Len + 1;
			Node *now = root, *t;
			for (int j = 0; j < Len; ) {
				bool virgin = true;
				for (t = now->child; t; t = t->brother) if (c[j] == *t->v) {
					int k = 1;
					while (k < t->len && c[j + k] == *(t->v + k)) k++;
					j += k;
					if (k == t->len) {
						now = t;
						virgin = false;
					} else {
						Node* tmp = ++sid;
						tmp->child = t->child, tmp->brother = NULL;
						tmp->v = t->v + k, tmp->len = t->len - k, tmp->cnt = t->cnt;
						t->child = tmp, t->len = k;
						now = t;
					}
					t->cnt++;
					break;
				}
				if (virgin) {
					Node *tmp = ++sid;
					tmp->child = NULL, tmp->brother = now->child, tmp->cnt = 1, tmp->v = ch[_] + j, tmp->len = Len - j;
					now->child = tmp;
					break;
				}
			}
		}
	}

	long long Ans = 0;
	void Dfs(Node *now, int d) {
		Ans = std::max(Ans, (long long)d * now->cnt);
		for (Node *t = now->child; t; t = t->brother)
			Dfs(t, d + t->len);
	}

	inline void solve(void) {
		Input();
		Dfs(root, 0);
		printf("%lld\n", Ans);
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
namespace Solve {
	typedef unsigned long long Int64;
	struct Node{int index, value;Node(int a, int b):index(a), value(b){}};
	typedef std::list<Node> II;
	const int MAXN = 500020;
	const int Base = 13331;

	char ch[MAXN];
	II a; int n;
	Int64 hash[MAXN], pow[MAXN];
	struct Edge {
		II::iterator it; Edge *next;
		Edge(II::iterator it, Edge *next):it(it), next(next){}
	}*e[MAXN];

	void solve(void) {
		gets(ch + 1);
		n = strlen(ch + 1); pow[0] = 1;
		for (int i = 1; i <= n; i++) 
			hash[i] = hash[i - 1] * Base + ch[i], pow[i] = pow[i - 1] * Base;
		for (int i = 1; i <= n; i++) {
			int l = 0, r = n - i + 1;
			while (l <= r) {
				int mid = (l + r) >> 1;
				Int64 t = hash[i + mid - 1] - hash[i - 1] * pow[mid];
				if (t == hash[mid])
					l = mid + 1;
				else
					r = mid - 1;
			}
			a.push_back(Node(i, r));
			II::iterator it = a.end(); it--;
			e[r] = new Edge(it, e[r]);
		}
		a.push_back(Node(n + 1, n + 1));
		int MaxR = 0;
		for (int i = 1; i <= n; i++) {
			int last = 1;
			for (Edge *p = e[i - 1]; p; p = p->next) {
				II::iterator it = p->it, next, prev;
				if (it->value == i - 1) {
					prev = next = it; prev--, next++;
					MaxR = std::max(MaxR, next->index - prev->index);
					a.erase(it++);
				}else it++;
			}
			if (MaxR <= i) {printf("%d\n", i); return;}
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

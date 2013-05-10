//#define Debug
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 100020;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n;
	struct Edge {
		int y, z; Edge *next, *opt; bool flag;
		Edge(int y, int z, Edge* next):y(y),z(z),next(next){flag = true;}
	}*a[MAXN];

	void Input(void) {
		n = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
	}

	int s[MAXN];
	void Bfs(void) {
		std::queue<int> Q;
		Q.push(1);
		while (!Q.empty()) {
			int now = Q.front(); Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				p->opt->flag = false;
				s[p->y] = s[now] ^ p->z;
				Q.push(p->y);
			}
		}
	}

	class XorTrie {public:
		XorTrie *ch[2];
		XorTrie(){ch[0] = ch[1] = NULL;}
		inline void Insert(int u) {
			unsigned int flag = 1 << 31 - 1;
			XorTrie *it = this;
			for (int i = 31; i >= 1; i--, flag >>= 1) {
				bool now = u & flag;
				if (!it->ch[now]) it->ch[now] = new XorTrie;
				it = it->ch[now];
			}
		}
		inline int Ask(int u) {
			int ret = 0;
			unsigned int flag = 1 << 31 - 1;
			XorTrie *it = this;
			for (int i = 31; i >= 1; i--, flag >>= 1) {
				bool now = u & flag;
				if (it->ch[!now]) {
					ret |= flag;
					it = it->ch[!now];
				} else it = it->ch[now];
			}
			return ret;
		}
	}*root;

	void Work(void) {
		root = new XorTrie;
		int Ans = 0;
		for (int i = 1; i <= n; i++) {
			root->Insert(s[i]);
			Ans = std::max(Ans, root->Ask(s[i]));
		}
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
		Bfs();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <vector>
#include <map>
#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)
#define rep(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	const int MAXM = 550000;
	const int MAXN = 60010;

	inline char* ScanStr(char ret[]) {
		int l = 0, c;
		while (c = getchar(), c == '\n' || c == '\r');
		ret[l++] = c;
		while (c = getchar(), c != '\n' && c != '\r') ret[l++] = c;
		ret[l++] = '\0';
		return ret + l;
	}

	char buf[MAXM], *model[MAXN], *pattern[MAXN];

	int n, m;

	inline void Input(void) {
		scanf("%d%d", &n, &m);
		model[1] = buf;
		rep(i, 1, n) 
			model[i + 1] = ScanStr(model[i]);
		pattern[1] = model[n + 1];
		rep(i, 1, m) pattern[i + 1] = ScanStr(pattern[i]);
	}

	struct Node {
		map<int, Node*> ist; vector<int> end;
		Node *fail;
	}*root, POOL[MAXM], *data = POOL;

	Node* end[MAXM];

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXM];

	int L;
	 
	inline void Insert(char ch[], int flag, int num) {
		Node *now = root; char *pid = ch;
		while (*pid) {
			if (now->ist.count(*pid)) {
				now = now->ist[*pid];
			} else {
				Node *next = data++;
				now->ist[*pid] = next;
				now = next;
			}
			if (flag == 1) now->end.push_back(num);
			pid++;
		}
		if (flag == 2) end[num] = now;
	}

	Node *d[MAXM];

	inline void Pre(void) {
		root = data++;
		rep(i, 1, n) Insert(model[i], 1, i);
		rep(i, 1, m) Insert(pattern[i], 2, i);
		int head = 1, tail = 0;
		foreach(it, root->ist) d[++tail] = it->second, it->second->fail = root;
		while (head <= tail) {
			Node *now = d[head++];
			foreach(it, now->ist) {
				Node *tmp = now->fail;
				while (tmp != root && !tmp->ist.count(it->first)) tmp = tmp->fail;
				if (tmp->ist.count(it->first)) tmp = tmp->ist[it->first];
				it->second->fail = tmp;
				d[++tail] = it->second;
			}
		}
		rep(i, 1, tail) a[d[i]->fail - POOL] = new Edge(d[i] - POOL, a[d[i]->fail - POOL]);
	}

	int list[MAXM], pos; pair<int, int> interval[MAXM];

	inline void Dfs(int u) {
		interval[u].first = pos + 1;
		foreach(it, POOL[u].end) list[++pos] = *it;
		for (Edge *p = a[u]; p; p = p->next)
			Dfs(p->y);
		interval[u].second = pos;
	}

	int Ans[MAXN], next[MAXM], C[MAXM], hash[MAXN];
	inline void ins(int u) {for (;u<=pos;u+=u&-u) C[u]++;}
	inline int cal(int u) {int ret = 0; for(;u;u-=u&-u) ret += C[u]; return ret;}

	struct Query {
		int y, index;
		Query(int y, int index):y(y), index(index){}
	};
	vector<Query> ist[MAXM];

	inline void solve(void) {
		Input();
		Pre();
		Dfs(0);
		for (int i = 1; i <= m; i++) {
			int t = end[i] - POOL;
			ist[interval[t].first].push_back(Query(interval[t].second, i));
		}
		for (int i = pos; i >= 1; i--) next[i] = hash[list[i]], hash[list[i]] = i;
		for (int i = 1; i <= pos; i++) if (hash[list[i]] == i) {
			ins(i);
		}
		for (int i = 1; i <= pos; i++) {
			foreach(it, ist[i]) Ans[it->index] = cal(it->y) - cal(i - 1);
			if (next[i]) ins(next[i]);
		}
		for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
	}
}

int main(void) {
	Solve::solve();
	return 0;
}


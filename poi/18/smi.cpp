#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 100010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Edge {
	int y; Edge *next, *opt; bool flag;
	Edge(int y, Edge *next):y(y), next(next){flag = true;}
}*a[MAXN];

int n, m, inp[MAXN], cur, vis[MAXN];

vector<int> trace, tmp;
vector< vector<int> > Ans;
set<int> S;

inline void D(int u) {
	if (!--inp[u]) S.erase(u);
}

void Dfs(int u) {
	if (vis[u] == cur) {
		tmp = vector<int>(1, u); int t;
		do {
			t = trace.back(); trace.pop_back();
			tmp.push_back(t);
			vis[t] = 0;
		} while (t != u);
		Ans.push_back(tmp);
	}
	trace.push_back(u);
	vis[u] = cur;
	for (Edge *&p = a[u]; p; p = p->next) if (p->flag) {
		p->flag = p->opt->flag = false;
		D(u); D(p->y);
		Dfs(p->y);
		if (!p || trace.back() != u) break;
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	n = ScanInt(), m = ScanInt();
	for (int i = 1; i <= m; i++) {
		int x = ScanInt(), y = ScanInt(), t1 = ScanInt(), t2 = ScanInt();
		if (t1 ^ t2) {
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y], a[y]->opt = a[x];
			inp[x]++, inp[y]++;
		}
	}
	for (int i = 1; i <= n; i++) if (inp[i] & 1) {
		puts("NIE");
		return 0;
	} else if (inp[i]) S.insert(i);
	while (!S.empty()) {
		int now = *S.begin();
		cur++; trace.resize(0);
		Dfs(now);
	}
	printf("%d\n", Ans.size());
	for (vector<vector<int> >::iterator it = Ans.begin(); it != Ans.end(); ++it) {
		printf("%d", it->size() - 1);
		for (vector<int>::iterator ot = it->begin(); ot != it->end(); ot++) printf(" %d", *ot);
		puts("");
	}
	return 0;
}


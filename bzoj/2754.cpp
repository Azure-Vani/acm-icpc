//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define OK fputs("OK!", stderr);

using namespace std;

namespace Solve {
	const int MAXN = 500010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int L, n, m;
	set<int> T_T;
	map<int, int> M_M;
	vector<int> a[MAXN], b[MAXN], c[MAXN];
	vector<int> List[MAXN];

	inline void Scan(vector<int> &a) {
		int t = ScanInt();
		a.pb(t);
		T_T.insert(t);
	}
	
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) {
			int L = ScanInt();
			for (int j = 1; j <= L; j++) Scan(a[i]);
			L = ScanInt();
			for (int j = 1; j <= L; j++) Scan(b[i]);
		}
		for (int i = 1; i <= m; i++) {
			int L = ScanInt();
			for (int j = 1; j <= L; j++) Scan(c[i]);
		}
		int tmp = 0;
		foreach(it, T_T) M_M[*it] = ++tmp;
		for (int i = 1; i <= n; i++) {foreach(it, a[i]) *it = M_M[*it];a[i].pb(tmp + i);}
		for (int i = 1; i <= n; i++) foreach(it, b[i]) a[i].pb(M_M[*it]);
		for (int i = 1; i <= m; i++) foreach(it, c[i]) *it = M_M[*it];
		L = tmp + n;
	}

	struct Node {
		map<int, Node*> ist; int num;
		Node *fail;
	}*root;

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*e[MAXN];
	inline void AddEdge(int x, int y) {
		e[x] = new Edge(y, e[x]);
	}

	int cnt = 1;
	int last[MAXN], Ans2[MAXN], Ans1[MAXN], value[MAXN];vector<int> num_end[MAXN];

	inline void Insert(vector<int>::iterator it, vector<int>::iterator end, int flag, int p) {
		Node *t = root;
		while (it != end) {
			if (t->ist.count(*it)) {
				t = t->ist[*it];
				if (flag == 1) List[t->num].pb(p);
			} else {
				Node *next = new Node();
				next->num = ++cnt;
				t->ist[*it] = next;
				t = next;
				if (flag == 1) List[t->num].pb(p);
			}
			++it;
		}
		if (flag == 2) num_end[t->num].pb(p);
	}
	
	Node* d[MAXN];

	inline void Makeup(void) {
		(root = new Node())->num = 1;
		for (int i = 1; i <= n; i++) 
			Insert(a[i].begin(), a[i].end(), 1, i);
		for (int i = 1; i <= m; i++) 
			Insert(c[i].begin(), c[i].end(), 2, i);
		int head = 1, tail = 0; d[0] = root;
		foreach(it, root->ist) d[++tail] = it->second, it->second->fail = root;
		while (head <= tail) {
			Node *now = d[head++];
			foreach(it, now->ist) {
				Node *t = now->fail;
				while (t != root && !t->ist.count(it->first)) t = t->fail;
				if (t->ist.count(it->first)) t = t->ist[it->first];
				it->second->fail = t;
				d[++tail] = it->second;
			}
		}
		for (int i = 1; i <= tail; i++) AddEdge(d[i]->fail->num, d[i]->num);
	}

	int Q[MAXN], sum[MAXN], deep[MAXN], belong[MAXN], father[MAXN], cover[MAXN];
	inline void Cut(void) {
		int head = 1, tail = 1; Q[1] = 1; deep[1] = 1;
		while (head <= tail) {
			int now = Q[head++];
			for (Edge *p = e[now]; p; p = p->next) {
				father[p->y] = now;
				deep[p->y] = deep[now] + 1;
				cover[p->y] = cover[now] + num_end[p->y].size();
				Q[++tail] = p->y;
			}
		}
		for (int i = tail; i >= 1; i--) sum[father[Q[i]]] += ++sum[Q[i]];
		for (int i = 1; i <= tail; i++) {
			int t = Q[i], Max = -1, son = 0;
			if (belong[t] == 0) belong[t] = t;
			for (Edge *p = e[t]; p; p = p->next) if (sum[p->y] > Max) {
				Max = sum[p->y];
				son = p->y;
			}
			if (son) belong[son] = belong[t];
		}
	}

	inline int LCA(int x, int y) {
		while (true) {
			if (deep[x] > deep[y]) swap(x, y);
			if (belong[x] == belong[y]) return x;
			if (deep[father[belong[x]]] < deep[father[belong[y]]]) swap(x, y);
			x = father[belong[x]];
		}
		return y;
	}

	inline void Dfs(int u) {
		foreach(it, List[u]) {
			int t = *it;
			int A = LCA(u, last[t]); 
			last[t] = u;
			Ans2[t] += cover[u] - cover[A];
			value[u]++; value[A]--;
		}
		for (Edge *p = e[u]; p; p = p->next) 
			Dfs(p->y);
	}

	inline void Cal(int u) {
		for (Edge *p = e[u]; p; p = p->next) {
			Cal(p->y);
			value[u] += value[p->y];
		}
		foreach(it, num_end[u]) Ans1[*it] += value[u];
	}
	inline void solve(void) {
		Input();
		Makeup();
		Cut();
		for (int i = 1; i <= cnt; i++) last[i] = 1;
		Dfs(1);
		Cal(1);
		for (int i = 1; i <= m; i++) printf("%d\n", Ans1[i]);
		for (int i = 1; i < n; i++) printf("%d ", Ans2[i]); printf("%d\n", Ans2[n]);
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

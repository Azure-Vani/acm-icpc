#include <cstdio>
#include <vector>
#include <algorithm>

#define mp make_pair

using namespace std;

const int MAXN = 205;
const int inf = 1000000000;

typedef pair<int, int> PII;

const PII Inf = mp(-inf, -inf);

struct Edge {
	int y; Edge *next, *opt; bool flag;
	Edge(int y, Edge *next, bool flag = true):y(y), next(next), flag(flag){}
}*a[MAXN], *father[MAXN];

inline void Update(PII& a, PII& b, PII c) {
	if (c > a) b = a, a = c; else if (c > b) b = c;
}

int n, value[MAXN], d[2], c[2], S, Q[MAXN], deep[MAXN], belong[MAXN];

int stack[MAXN], cur, top, vis[MAXN], oup[MAXN];

inline void Add(int &tmp, int u, bool s) {
	tmp += value[u]; oup[u] = s;
}

inline bool cmp(int x, int y) {return value[x] > value[y];}

void Dfs(int u, int f = 0) {
	stack[++top] = u;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag && p->y != f) Dfs(p->y, u), father[p->y] = p->opt;
}

vector<int> List;

int Set(int now, int len, int k, bool s = false) {
	List.clear(); cur++;
	int head = 1, tail = 0, tmp = 0;
	deep[now] = 0; Q[++tail] = now; vis[now] = cur; belong[now] = 0;
	if (len & 1) {
		int prev = father[now]->y;
		deep[prev] = 0;
		Q[++tail] = prev;
		vis[prev] = cur;
		father[now]->flag = false;
		father[now]->opt->flag = false; belong[now] = now; belong[prev] = prev;
	}
	int limit = len >> 1;
	while (head <= tail) {
		int now = Q[head++]; 
		if (deep[now] == limit) {
			List.push_back(now); 
			continue;
		}
		Add(tmp, now, s);
		for (Edge *p = a[now]; p; p = p->next) if (vis[p->y] != cur && p->flag){
			Q[++tail] = p->y;
			vis[p->y] = cur;
			deep[p->y] = deep[now] + 1;
			if (belong[now]) belong[p->y] = belong[now]; else belong[p->y] = p->y;
		}
	}
	sort(List.begin(), List.end(), cmp);
	vector<int>::iterator it = List.begin(); int cnt = 0, same = -1;
	while (it != List.end() && cnt < k - 1) {
		cnt++;
		Add(tmp, *it, s);
		if (same == -1) same = belong[*it]; else if (same != belong[*it]) same = -2;
		it++;
	}
	int another = 0;
	while (it != List.end() && belong[*it] == same) it++;
	if (it != List.end()) Add(tmp, *it, s), cnt++, another++;
	if (len & 1) {
		father[now]->flag = true;
		father[now]->opt->flag = true;
	}
	if (cnt < 2) return -inf;
	if (same != -2 && another == 0) return -inf;
	return tmp;
}

inline int Cal(int u, int len, int k, bool s = false) {
	if (k == 1 && len != 0) return -inf;
	top = 0; Dfs(u); PII ret = Inf;
	if (k == 1 || len == 0) {
		for (int i = 1; i <= top; i++) ret = max(ret, mp(value[stack[i]], i));
		oup[stack[ret.second]] = s;
		return ret.first;
	}
	for (int i = (len & 1) + 1; i <= top; i++) {
		int tmp = Set(stack[i], len, k, false);
		ret = max(mp(tmp, stack[i]), ret);
	}
	if (s) Set(ret.second, len, k, true);
	return ret.first;
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d%d%d", &n, d, c, d + 1, c + 1);
	for (int i = 1; i <= n; i++) scanf("%d", value + i), S += value[i];
	for (int i = 1; i <  n; i++) {
		int x, y; scanf("%d%d", &x, &y);
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
	}
	pair<PII, pair<PII, PII> > Ans;
	for (int i = 1; i <= n; i++) {
		PII a[2] = {Inf, Inf}, b[2] = {Inf, Inf};
		for (Edge *p = ::a[i]; p; p = p->next) {
			p->flag = p->opt->flag = false;
			int t1 = Cal(p->y, d[0], c[0]);
			int t2 = Cal(p->y, d[1], c[1]);
			p->flag = p->opt->flag = true;
			Update(a[0], a[1], mp(t1, p->y));
			Update(b[0], b[1], mp(t2, p->y));
		}
		if (a[0].second != b[0].second) {
			Ans = max(Ans, mp(mp(a[0].first + b[0].first, i), mp(a[0], b[0])));
		} else {
			Ans = max(Ans, mp(mp(a[0].first + b[1].first, i), mp(a[0], b[1])));
			Ans = max(Ans, mp(mp(a[1].first + b[0].first, i), mp(a[1], b[0])));
		}
	}
	int sep = Ans.first.second;
	for (Edge *p = a[sep]; p; p = p->next) {
		if (p->y == Ans.second.first.second) {
			p->flag = p->opt->flag = false;
			Cal(p->y, d[0], c[0], true);
			p->flag = p->opt->flag = true;
		}
		if (p->y == Ans.second.second.second) {
			p->flag = p->opt->flag = false;
			Cal(p->y, d[1], c[1], true);
			p->flag = p->opt->flag = true;
		}
	}
	if (Ans.first.first > 0) {
		printf("%d\n", S - Ans.first.first);
		for (int i = 1; i <= n; i++) if (!oup[i]) printf("%d ", i);
	}
	else puts("-1");
	return 0;
}


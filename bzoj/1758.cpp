#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const double eps = 1e-5;
	const int MAXN = 100020;
	const int inf = ~0U>>1;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y, z; Edge *next, *opt; bool flag;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){flag = true;}
	}*a[MAXN];
	int n, L, R;

	inline void Input(void) {
		n = ScanInt(), L = ScanInt(), R = ScanInt();
		REP(i, 1, n - 1) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]); a[y] = new Edge(x, z, a[y]);
			a[x]->opt = a[y]; a[y]->opt = a[x];
		}
	}

	int d[MAXN], sum[MAXN], father[MAXN], top;
	pair<int, int> stack[MAXN];
	double Ans = -1;

	inline bool cmp(pair<int,int>  x, pair<int, int> y) {
		return sum[x.first] < sum[y.first];
	}

	bool vis[MAXN];

	inline int CalSum(int u) {
		int head = 1, tail = 1, r = 0; vis[ d[1] = u ] = true;
		while (head <= tail) {
			int now = d[head++]; sum[now] = 0;
			for (Edge *p = a[now]; p; p = p->next) if (p->flag && !vis[p->y]) {
				r = max(r, p->z);
				d[++tail] = p->y;
				father[p->y] = now;
				vis[p->y] = true;
			}
		}
		for (int i = tail; i >= 1; i--) sum[father[d[i]]] += ++sum[d[i]], vis[d[i]] = false;
		return r;
	}

	double f[MAXN], dis[MAXN];
	int List[MAXN];

	inline int Cal(int u, int d, double sum, double delta) {
		if (d > R) return R;
		int ret = 0;
		dis[d] = max(dis[d], sum);
		for (Edge *p = a[u]; p; p = p->next) if (p->flag && father[u] != p->y) {
			int tmp = Cal(p->y, d + 1, sum + p->z - delta, delta);
			ret = max(ret, tmp);
		}
		return ret + 1;
	}

	inline double Gao(double a[], double b[], int n, int m) {
		int head = 1, tail = 0; double ret = -inf;
		for (int i = max(0, L - n); i <= min(R - n - 1, m); i++) {
			while (head <= tail && b[d[tail]] <= b[i]) tail--;
			d[++tail] = i;
		}
		for (int i = n; i >= 0; i--) {
			if (R - i >= 0 && R - i <= m) {
				while (head <= tail && b[d[tail]] <= b[R - i]) tail--;
				d[++tail] = R - i;
			}
			while (head <= tail && R - i - d[head] + 1 > R - L + 1) head++;
			if (head <= tail)
				ret = max(ret, a[i] + b[d[head]]);
		}
		return ret;
	}

	inline void Dfs(int u) {
		father[u] = 0;
		double l = max(Ans, 0.0), r = 0;
		int best = inf, w = -1;
		CalSum(u);
		for (int i = sum[u]; i >= 1; i--) {
			int tmp = sum[u] - sum[d[i]];
			for (Edge *p = a[d[i]]; p; p = p->next) if (p->flag && father[d[i]] != p->y) 
				tmp = max(tmp, sum[p->y]);
			if (tmp < best) best = tmp, w = d[i];
		}
		father[w] = 0; r = CalSum(w);
		top = 0;
		for (Edge *p = a[w]; p; p = p->next) if (p->flag) stack[top++] = make_pair(p->y, p->z);
		sort(stack, stack + top, cmp);
		while (r - l >= eps) {
			double mid = (l + r) / 2.0;
			bool ok = false;
			int Len = 0;
			for (int i = 1; i <= sum[w]; i++) f[i] = -inf;
			for (int i = 0; i < top && !ok; i++) {
				for (int j = 1; j <= sum[stack[i].first]; j++) dis[j] = -inf;
				int tmp = Cal(stack[i].first, 1, stack[i].second - mid, mid);

				/* mono queue */
				double Max = Gao(dis, f, tmp, Len);
				Len = max(Len, tmp);
				for (int i = 1; i <= Len; i++) f[i] = max(f[i], dis[i]);
				if (Max >= 0) ok = true;
			}
			if (ok)
				l = mid;
			else
				r = mid;
		}
		Ans = max(Ans, l);
		for (Edge *p = a[w]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			if (sum[p->y] > L) Dfs(p->y);
		}
	}

	inline void solve(void) {
		Input();
		Dfs(1);
		printf("%.3lf\n", Ans);
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

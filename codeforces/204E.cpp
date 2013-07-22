#include <cstdio>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXN = 100030;

int w[MAXN];

inline void Sort(int a[], int ret[], int n, int m = MAXN - 1) {
	for (int i = 0; i <= m; i++) w[i] = 0;
	for (int i = 0; i < n; i++) w[a[i]]++;
	for (int i = 1; i <= m; i++) w[i] += w[i - 1];
	for (int i = n - 1; i >= 0; i--) ret[w[a[i]]--] = i;
}

int wa[MAXN], wb[MAXN], tmp[MAXN];

inline void getSA(int ch[], int sa[], int n) {
	int *x = wa, *y = wb, m = MAXN - 1; sa[0] = n;
	for (int i = 0; i < n; i++) x[i] = ch[i];
	Sort(x, sa, n);
	for (int j = 1, p = 1; p < n; j <<= 1, m = p) {
		p = 0;
		for (int i = n - j; i < n; i++) y[p++] = i;
		for (int i = 1; i <= n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (int i = 0; i < n; i++) tmp[i] = x[y[i]];
		Sort(tmp, sa, n, m);
		for (int i = 1; i <= n; i++) sa[i] = y[sa[i]];
		swap(x, y); p = x[sa[1]] = 1;
		for (int i = 2; i <= n; i++) {
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p;
			else x[sa[i]] = ++p;
		}
	}
}

int rank[MAXN];

inline void getHeight(int ch[], int sa[], int height[], int n) {
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 0, t = 0; i < n; i++) {
		if (t > 0) t--;
		while (ch[i + t] == ch[sa[rank[i] - 1] + t]) t++;
		height[rank[i]] = t;
	}
}

int n, k, len, sa[MAXN], height[MAXN];
int ch[MAXN << 1]; char st[MAXN];

int belong[MAXN], vis[MAXN];

long long Ans[MAXN];

map<int, int> M;
map<int, int, greater<int> > G;

vector<int> list[MAXN];

int main(void) {
	//freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	int *p = ch;
	for (int i = 1; i <= n; i++) {
		scanf("%s", st); int tmp = strlen(st);
		for (int j = 0; j < tmp; j++) *p++ = st[j] - 'a' + 1; *p++ = 26 + i;
		len += tmp + 1;
		if (k == 1) Ans[i] += (long long) tmp * (tmp - 1) / 2 + tmp;
	}
	if (k != 1) {
		getSA(ch, sa, len);
		getHeight(ch, sa, height, len);
		len -= n;
		for (int i = 1, it = 0, now = 0; i <= len; i++) {
			while (it <= len && now < k) {
				it++;
				if (it <= len && !vis[belong[sa[it]]]) {
					now++;
					vis[belong[sa[it]]]++;
					M[height[it]]++;
				}
			}
			if (!--M[height[i]]) M.erase(M.find(height[i]));
			G[M.begin()->first]++;
			list[it].push_back(M.begin()->first);
			if (now >= k) {
				Ans[belong[sa[i]]] += G.begin()->first;
			} else break;
			for (vector<int>::iterator it = list[i].begin(); it != list[i].end(); ++it)
				if (!--G[*it]) G.erase(G.find(*it));
			vis[belong[sa[i]]]--;
			if (vis[belong[sa[i]]] == 0) now--;
		}
	}
	for (int i = 1; i <= n; i++) printf("%I64d ", Ans[i]); puts("");
	return 0;
}


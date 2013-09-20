#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <map>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200010;

// Suffix Array template
// string is 1-base, sa is 1-base
int w[MAXN];

inline void Sort(int a[], int ret[], int n, int m = MAXN - 1) {
	for (int i = 0; i <= m; i++) w[i] = 0;
	for (int i = 1; i <= n; i++) w[a[i]]++;
	for (int i = 1; i <= m; i++) w[i] += w[i - 1];
	for (int i = n; i >= 1; i--) ret[w[a[i]]--] = i;
}

int wa[MAXN], wb[MAXN], tmp[MAXN];

inline void getSA(int ch[], int sa[], int n) {
	int *x = wa, *y = wb;
	for (int i = 1; i <= n; i++) x[i] = ch[i];
	Sort(ch, sa, n);
	for (int j = 1, p = 1, m = MAXN - 1; p < n; m = p, j <<= 1) {
		p = 0;
		for (int i = n - j + 1; i <= n; i++) y[++p] = i;
		for (int i = 1; i <= n; i++) if (sa[i] > j) y[++p] = sa[i] - j;
		for (int i = 1; i <= n; i++) tmp[i] = x[y[i]];
		Sort(tmp, sa, n, m);
		for (int i = 1; i <= n; i++) sa[i] = y[sa[i]];
		swap(x, y); x[sa[1]] = p = 1;
		for (int i = 2; i <= n; i++) {
			if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) x[sa[i]] = p;
			else x[sa[i]] = ++p;
		}
	}
	sa[0] = n + 1; // for calculate height.
}

int rank[MAXN];

inline void getHeight(int ch[], int sa[], int height[], int n) {
	for (int i = 1; i <= n; i++) rank[sa[i]] = i;
	for (int i = 1, t = 0; i <= n; i++) {
		if (t > 0) t--;
		while (ch[i + t] == ch[sa[rank[i] - 1] + t]) t++;
		height[rank[i]] = t;
	}
}
// Template End


int nStr, k, n = 0;
int ch[MAXN]; char str[MAXN];
int sa[MAXN], type[MAXN], height[MAXN], Ans[MAXN];

int vis[MAXN], visited = 0;long long final[MAXN];
map<int, int> S, Q;

vector<int> ins[MAXN], del[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	scanf("%d%d", &nStr, &k);
	for (int i = 1; i <= nStr; i++) {
		scanf("%s", str); int tmp = strlen(str);
		for (int j = n + 1; j <= n + tmp; j++) ch[j] = str[j - n - 1] - 'a' + 1, type[j] = i;
		n += tmp + 1; ch[n] = i + 26;
		if (k == 1) final[i] += (long long)tmp * (tmp - 1) / 2 + (long long)tmp;
	}
	if (k > 1) {
		getSA(ch, sa, n);
		getHeight(ch, sa, height, n);
		n -= nStr;
		// BEGIN
		visited = 1;
		vis[type[sa[1]]] = 1;
		/*for (int i = 1; i <= n; i++) {
			printf("sa: %d, type: %d, height: %d\n", i, type[sa[i]], height[i]);
		}*/
		for (int i = 1, next = 1; i <= n; i++) {
			while (visited < k && next < n) {
				next++;
				if (!vis[type[sa[next]]]) visited++;
				vis[type[sa[next]]]++;
				S[height[next]]++;
			}
			if (visited < k) break;
			int tmp = S.begin()->first;
			ins[i].push_back(tmp);
			del[next].push_back(tmp);
			//printf("L = %d, R = %d, val = %d ", i, next, tmp); for (int k = i; k <= next; k++) printf("%d:%d ", k,type[sa[k]]); puts("");
			map<int, int>::iterator it = S.find(height[i + 1]); if (!--it->second) S.erase(it);
			if (!--vis[type[sa[i]]]) visited--;
		}

		memset(vis, 0, sizeof vis); S.clear();

		visited = 1;
		vis[type[sa[n]]] = 1;
		for (int i = n, next = n; i >= 1; i--) {
			while (visited < k && next > 1) {
				next--;
				if (!vis[type[sa[next]]]) visited++;
				vis[type[sa[next]]]++;
				S[height[next + 1]]++;
			}
			if (visited < k) break;
			int tmp = S.begin()->first;
			ins[next].push_back(tmp);
			del[i].push_back(tmp);
			map<int, int>::iterator it = S.find(height[i]); if (!--it->second) S.erase(it);
			if (!--vis[type[sa[i]]]) visited--;
		}

		for (int i = 1; i <= n; i++) {
			for (vector<int>::iterator it = ins[i].begin(); it != ins[i].end(); ++it) {
				Q[*it]++;
			}
			if (!Q.empty()) Ans[i] = Q.rbegin()->first;
			for (vector<int>::iterator it = del[i].begin(); it != del[i].end(); ++it) {
				map<int, int>::iterator ot = Q.find(*it);
				if (!--ot->second) Q.erase(ot);
			}
		}
		for (int i = 1; i <= n; i++) final[type[sa[i]]] += Ans[i];
		// END
	}
	for (int i = 1; i <= nStr; i++) printf(LL " ", final[i]); puts("");
	return 0;
}
#include <cstdio>
#include <algorithm>
#define mp make_pair

using namespace std;

const int MAXN = 200010;

pair<int, pair<int, int> > Ans;
int n, m, k, w[MAXN], c[MAXN];

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", w + i, c + i), w[i] += w[i - 1], c[i] += c[i - 1];
	for (int i = n - m + 1; i >= 1; i--) {
		if (w[i - 1] * k < w[i + m - 1] - w[i - 1]) break;
		int l = 1, r = i - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if ((w[i - 1] - w[mid - 1]) * k < w[i + m - 1] - w[i - 1]) r = mid - 1; else l = mid + 1;
		}
		Ans = max(Ans, mp(c[n] - c[i + m - 1] + c[r - 1], mp(r - 1, n - (i + m - 1))));
	}
	printf("%d %d\n", Ans.second.first + Ans.second.second, Ans.first);
	for (int i = 1; i <= Ans.second.second; i++) putchar('H');
	for (int i = 1; i <= Ans.second.first; i++) putchar('T');
	return 0;
}


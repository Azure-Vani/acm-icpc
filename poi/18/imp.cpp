#include <cstdio>
#include <vector>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 3010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

vector<int> a[MAXN];
vector<int> Ans;
int n, m, cnt[MAXN], del[MAXN];

bool cmp(int x, int y) {return cnt[x] < cnt[y];}

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x = ScanInt(), y = ScanInt();
		a[x].push_back(y); a[y].push_back(x);
	}
	for (int i = 1; i <= n; i++) a[i].push_back(i);
	int t = 0;
	for (int i = 1; i <= n; i++) {
		if ((int)a[i].size() >= n / 3 * 2) {
			t++;
			for (vector<int>::iterator it = a[i].begin(); it != a[i].end(); ++it) cnt[*it]++;
		}
	}
	for (int i = 1; i <= n; i++) if (!del[i] && cnt[i] >= n/3 * 2 + !!(t - n / 3 * 2)) Ans.push_back(i);
	sort(Ans.rbegin(), Ans.rend(), cmp);
	Ans.resize(n / 3);
	for (int i = 0; i < (int)Ans.size() - 1; i++) printf("%d ", Ans[i]); printf("%d\n", Ans[Ans.size() - 1]);
	return 0;
}


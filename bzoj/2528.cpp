#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define same(i, n) (cal(1, i) == cal(n - (i) + 1, n))
using namespace std;

typedef unsigned long long Int64;

const int MAXN = 200010;
const Int64 base = 13331;

char ch[MAXN]; Int64 sum[MAXN], pow[MAXN];
int n; vector<int> c; int Ans[MAXN];

inline Int64 cal(int l, int r) {
	return sum[r] - sum[l - 1] * pow[r - l + 1];
}

int main(void) {
//	freopen("in", "r", stdin);
	pow[0] = 1; for (int i = 1; i < MAXN; i++) pow[i] = pow[i - 1] * base;
	int kase; scanf("%d", &kase); while (kase--) {
		scanf("%s", ch + 1); n = strlen(ch + 1);
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] * base + ch[i];
		c.resize(0);
		for (int i = 1; i <= n; i++) if (same(i, n)) c.push_back(i);
		memset(Ans, 0,sizeof Ans); int last = 0;
		for (vector<int>::iterator it = c.begin(); it != c.end(); ++it) {
			int y = *it;
			if (last * 2 < y) {
				memcpy(Ans + y - last + 1, Ans + 1, sizeof(Ans[0]) * last);
				for (int i = 1; i <= y; i++) sum[i] = sum[i - 1] * base + Ans[i] + 1;
				for (int i = last + 1; i < y; i++) if (same(i, y)) Ans[last + 1] = 1;
			} else {
				int d = y - last;
				memcpy(Ans + last + 1, Ans + (last - d + 1), sizeof(Ans[0]) * d);
			}
			last = y;
		}
		for (int i = c[(int)c.size() - 1]; i >= 1; i--) putchar(48 + Ans[i]); puts("");
	}
	return 0;
}

